double fAlphaEnergy1 = 5.486;// MeV (85.2 %)
double fAlphaEnergy2 = 5.443;// MeV (12.8 %)
double fAEBR = 6.65625; ///< alpha energy branching ratio = 85.2 / 12.8 = 6.65625;
double FxTwoAlpha(Double_t *xy, Double_t *par);
void Convert2APParameters(double* par, double &mean1, double &sigma1, double &amplitude1, double &mean2, double &sigma2, double &amplitude2);

void analyze_two_alpha()
{
    gStyle -> SetTitleSize(0.09,"t"); // set title size on the top of the histograms

    ofstream fcal("calibration_file.txt");

    auto file = new TFile("RUN511.ch.root","read");
    auto tree = (TTree*) file -> Get("channels");

    for (auto det : {2})
    //for (auto det : {2,3,4})
    {
        // set expected adc ranges
        double x1 = 1450;
        double x2 = 1600;
        if (det==3 || det==4) {
            x1 = 2800;
            x2 = 3200;
        }

        auto cvs1 = new TCanvas(Form("analysis_alpha_det%d_1",det),"cvs1",1200,700);
        cvs1 -> Divide(4,4);
        auto cvs2 = new TCanvas(Form("analysis_alpha_det%d_2",det),"cvs2",1200,700);
        cvs2 -> Divide(4,4);

        for (auto dch=1; dch<=32; ++dch)
        {
            // set expected adc ranges
            if (det==3 && (dch==22 || dch==23)) {
                x1 = 2500;
                x2 = 3500;
            }
            TVirtualPad* pad;
            if (dch<=16)
                pad = cvs1 -> cd(dch);
            else
                pad = cvs2 -> cd(dch-16);
            pad -> SetMargin(0.1,0.05,0.1,0.1);

            TString nameHist = Form("hist_d%dc%d",det,dch);
            TCut cut = Form("det==%d && dch==%d",det,dch);
            auto hist = new TH1D(nameHist,cut,50,x1,x2);
            hist -> GetXaxis() -> SetLabelSize(0.065);
            hist -> GetYaxis() -> SetLabelSize(0.065);

            tree -> Draw(TString("adc>>")+nameHist,cut,"");
            if (hist->GetEntries()==0) // skip fitting if data do not exist
                continue;

            auto amplitude = hist -> GetBinContent(hist -> GetMaximumBin()); // get initial amplitude from histogram statistics
            auto mean = hist -> GetBinCenter(hist -> GetMaximumBin()); // get initial mean from histogram statistics
            auto sigma = hist -> GetStdDev(); // get initial stddev from histogram statistics
            double adcOffset = 0;
            double energyResolution = sigma/mean;

            auto fit = new TF1("fit",FxTwoAlpha,x1,x2,4);
            fit -> SetParameters(adcOffset,energyResolution,mean,amplitude); // set initial parameter
            fit -> SetParLimits(0,0,0); // set initial parameter
            fit -> SetRange(mean - 0.5*sigma, mean + 3*sigma); // set initial range
            hist -> Fit(fit,"RQ");

            //if (1) { // set range from the previous fit and perform fit
            //    amplitude = fit -> GetParameter(0);
            //    mean = fit -> GetParameter(1);
            //    sigma = fit -> GetParameter(2);
            //    if (dch==1||dch==32)
            //        fit -> SetRange(mean - 0.5*sigma, mean + 3*sigma);
            //    else
            //        fit -> SetRange(mean - sigma, mean + 3*sigma);
            //    hist -> Fit(fit,"RQ");
            //}

            auto parameters = fit -> GetParameters();
            double mean1, sigma1, amplitude1, mean2, sigma2, amplitude2;
            Convert2APParameters(parameters, mean1, sigma1, amplitude1, mean2, sigma2, amplitude2);

            auto fit_peak1 = new TF1("fit_peak1","gaus(0)",x1,x2);
            auto fit_peak2 = new TF1("fit_peak2","gaus(0)",x1,x2);
            fit_peak1 -> SetParameters(amplitude1, mean1, sigma1);
            fit_peak2 -> SetParameters(amplitude2, mean2, sigma2);
            fit_peak1 -> Draw("samel");
            fit_peak2 -> Draw("samel");

            cout << det << " " << dch << " " << mean1 << " " << sigma1 << endl;
            fcal << det << " " << dch << " " << mean1 << " " << sigma1 << endl;
        }

//        cvs1 -> cd(); cvs1 -> SaveAs(Form("figures/%s.pdf",cvs1->GetName()));
//        cvs1 -> cd(); cvs2 -> SaveAs(Form("figures/%s.pdf",cvs2->GetName()));
    }
}


double FxTwoAlpha(Double_t *xy, Double_t *par)
{
    double x = xy[0];

    double ADCOffset = par[0];
    double energyResolution = par[1];

    double mean1 = par[2]; // ADC mean of 5.486 MeV peak
    double meanP1 = mean1 - ADCOffset; // pure ADC without ADC-offset
    double sigma1 = energyResolution * meanP1;
    double amplitude1 = par[3];

    double ADCEnergyRatio = meanP1 / fAlphaEnergy1;

    double mean2 = fAlphaEnergy2 * ADCEnergyRatio + ADCOffset;
    double meanP2 = mean2 - ADCOffset; // pure ADC without ADC-offset
    double sigma2 = energyResolution * meanP2;
    double amplitude2 = amplitude1 * sigma1 / fAEBR / sigma2;

    double value1 = amplitude1*exp(-0.5*((x-mean1)*(x-mean1)/sigma1/sigma1));
    double value2 = amplitude2*exp(-0.5*((x-mean2)*(x-mean2)/sigma2/sigma2));
    double value  = value1 + value2;

    return value;
}

void Convert2APParameters(double* par, double &mean1, double &sigma1, double &amplitude1, double &mean2, double &sigma2, double &amplitude2)
{
    double ADCOffset = par[0];
    double energyResolution = par[1];

    mean1 = par[2]; // ADC mean of 5.486 MeV peak
    double meanP1 = mean1 - ADCOffset; // pure ADC without ADC-offset
    sigma1 = energyResolution * meanP1;
    amplitude1 = par[3];

    double ADCEnergyRatio = meanP1 / fAlphaEnergy1;

    mean2 = fAlphaEnergy2 * ADCEnergyRatio + ADCOffset;
    double meanP2 = mean2 - ADCOffset; // pure ADC without ADC-offset
    sigma2 = energyResolution * meanP2;
    amplitude2 = amplitude1 * sigma1 / 6.65625 / sigma2; // 85.2 / 12.8 = 6.65625;
}
