
Double_t HighAlpha = 5.486; // [MeV]
Double_t LowAlpha = 5.443; // [MeV]
Double_t FxTwoAlpha(Double_t *xp, Double_t *par);
void Convert2APParameters(double *par, double &mean1, double &sigma1, double &amplitude1, double &mean2, double &sigma2, double &amplitude2);

void calibration_of_parameters(){


	TFile *file = new TFile("RUN511.ch.root","read");
	TTree *tree = (TTree *)file -> Get("channels");
	

		
	TFile *file1 = new TFile("fit_params.root","RECREATE");

	tree -> Print();	
	for(auto det : {2,3,4}){
			
			double x1 = 1450;
			double x2 = 1600;
			if (det ==3 || det == 4){
				x1 = 2800;
				x2 = 3200;
			}
		
			TCanvas *c1 = new TCanvas(Form("Fitting_of_det%d_1", det),Form("det== %d",det),1200,700);	
			c1 -> Divide(4,4);
			
			TCanvas *c2 = new TCanvas(Form("Fitting_of_det%d_2", det),Form("det== %d_2",det),1200,700);	
			c2 -> Divide(4,4);

			for(auto dch = 1; dch <=32; dch++){
				

				if (det == 3 && (dch == 22|| dch == 23)){
					x1 = 2500;
					x2 = 3500;
				}


				if(dch <=16) c1 -> cd(dch);
				else c2 -> cd(dch-16);
				
				TCut cut_det = Form("det == %d",det);
				TCut cut_dch = Form("dch == %d",dch);	
					
				TCut cut = cut_det && cut_dch;	
				
				TString name_of_hist = Form("hist_d%d_%d", det, dch);
				TH1D *hist = new TH1D(name_of_hist, cut, 50, x1, x2);
				hist -> GetXaxis() -> SetLabelSize(0.065);	
				hist -> GetYaxis() -> SetLabelSize(0.065);	
				tree -> Draw(TString("adc>>")+name_of_hist,cut,"");								
		
			//	TH1D *hist = (TH1D *)gPad -> GetPrimitive("htemp");	
				
				auto amplitude = hist -> GetBinContent(hist -> GetMaximumBin());	
				auto mean = hist -> GetBinCenter(hist -> GetMaximumBin());
				auto sigma = hist -> GetStdDev();
				double adcOffset = 0;
				double energyResolution = sigma / mean;

				TF1 *fit = new TF1("fit",FxTwoAlpha,x1 ,x2, 4);

				fit -> SetParameters(adcOffset,energyResolution,mean,amplitude);
				fit -> SetParLimits(0,0,0);
				fit -> SetRange(mean - 0.5*sigma, mean+ 3*sigma);
				hist -> Fit(fit,"RQN");

			
				auto parameters = fit -> GetParameters();
				double mean1,sigma1,amplitude1,mean2,sigma2,amplitude2;
				Convert2APParameters(parameters,mean1,sigma1,amplitude1,mean2,sigma2,amplitude2);
				
				auto fit_peak1 = new TF1("fit_peak1","gaus(0)",x1,x2);
				auto fit_peak2 = new TF1("fit_peak2","gaus(0)",x1,x2);
				fit_peak1 -> SetParameters(amplitude1, mean1, sigma1);
				fit_peak2 -> SetParameters(amplitude2, mean2, sigma2);
				fit_peak1 -> SetLineColor(kRed);
				fit_peak2 -> SetLineColor(kYellow);
				fit_peak1 -> Draw("samel");
				fit_peak2 -> Draw("samel");
				if(det == 3 && (dch ==16 || dch > 23)){
					cout << Form("empty entries : %d", dch);
					fit_peak1 -> SetParameters(-999,-999,-999);	
					fit_peak2 -> SetParameters(-999,-999,-999);	
				}
				fit_peak1 -> Write(Form("fit_peak1_det == %d dch == %d",det,dch));
				fit_peak2 -> Write(Form("fit_peak2_det == %d dch == %d",det,dch));
			
				TLegend *legend = new TLegend(0.1,0.6,0.3,0.8);
				legend -> AddEntry(fit_peak1,"High_Alpha","l");
				legend -> AddEntry(fit_peak2,"Low_Alpha","l");
				legend -> Draw("same");

			}	
/*		c1 -> cd();
		c1 -> SaveAs(Form("figures_det%d_1.pdf",det));
		c2 -> cd();
		c2 -> SaveAs(Form("figures_det%d_2.pdf",det));
*/	}


	file1->Close();	
}


Double_t FxTwoAlpha(Double_t *xp, Double_t *par){
	double x = xp[0];

	double ADCOffset = par[0];
	double energyResolution = par[1];	
	double mean1 = par[2];
	double meanP1 = mean1 - ADCOffset;
	double sigma1 = energyResolution * meanP1;
	double amplitude1 = par[3];
	double ADCEnergyRatio = meanP1 / HighAlpha;
	
	double mean2 = LowAlpha * ADCEnergyRatio + ADCOffset;
	double meanP2 = mean2 - ADCOffset;
	double sigma2 = energyResolution * meanP2;
	double amplitude2 = amplitude1 * sigma1 / 6.65625 / sigma2;

	double value1 = amplitude1*exp(-0.5*((x-mean1)*(x-mean1)/sigma1/sigma1));
	double value2 = amplitude2*exp(-0.5*((x-mean2)*(x-mean2)/sigma2/sigma2));
	double value = value1 + value2;
	return value;
}

void Convert2APParameters(double *par, double &mean1, double &sigma1, double &amplitude1, double &mean2, double &sigma2, double &amplitude2){
	double ADCOffset = par[0];
	double energyResolution = par[1];

	mean1 = par[2];
	double meanP1 = mean1 - ADCOffset;
	sigma1 = energyResolution * meanP1;
	amplitude1 = par[3];

	double ADCEnergyRatio = meanP1 / HighAlpha ;

	mean2 = LowAlpha * ADCEnergyRatio + ADCOffset;
	double meanP2 = mean2 - ADCOffset;
	sigma2 = energyResolution * meanP2;
	amplitude2 = amplitude1 * sigma1 / 6.65625 / sigma2;
}


