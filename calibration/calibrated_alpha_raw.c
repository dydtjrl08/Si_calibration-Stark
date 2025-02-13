double user_equation(double *x, double *par){
	        double x0 = x[0];
	        double amplitude = par[0];
		double mean = par[1]; 
		double sigma = par[2];

	        if(x0 < mean - sigma) return 0;
        	double exponent = -( (x0 - mean) * (x0 - mean) ) / (2 * sigma * sigma) ;
		double value = amplitude * std::exp(exponent);

		return value;

}




void one_gauss(){
	
         double par[] = {100,50,20};                                                                                              
	 double x[] = {50};
	 
	 
	 TH1D * hist = new TH1D("hist","",200,0,100);
	 for(int i = 0; i < 10000; ++i){
		 double value = gRandom -> Gaus(50,10);
		 hist -> Fill(value);
		 }
	 hist -> Draw();

	 cout << user_equation(x,par) << endl;
	                                      
	 TF1 *f1 = new TF1("f1",user_equation,0,100,3);
	 f1 -> SetParameters(100,50,20);
	 f1 -> SetNpx(1000);
	 f1 -> SetParNames("Amplitude","Mean","Sigma");
	 hist -> Fit(f1);	 
}


void calibrated_alpha_raw()
{
    gStyle -> SetTitleSize(0.09,"t"); // set title size on the top of the histograms

    int i, j;
    double mean, sigma;
    double conversion_factor[5][33] = {0};
    //ifstream fcal("data/calibration_file.txt");
    //while (fcal >> i >> j >> mean >> sigma)
    //    conversion_factor[i][j] = 5.486/mean;
    //
    auto file = new TFile("data/RUN511.ch.root","read");
    auto tree = (TTree*) file -> Get("channels");
    //first order : main source	
    for (auto det : {2,3,4})
    {
        double x1 = 5.1;
        double x2 = 5.7;

        auto cvs1 = new TCanvas(Form("calibrated_alpha_det%d_1",det),"cvs1",1200,700);
        cvs1 -> Divide(4,4);
        auto cvs2 = new TCanvas(Form("calibrated_alpha_det%d_2",det),"cvs2",1200,700);
        cvs2 -> Divide(4,4);

        for (auto dch=1; dch<=32; ++dch)
        {
            TVirtualPad* pad;
            if (dch<=16)
                pad = cvs1 -> cd(dch);
            else
                pad = cvs2 -> cd(dch-16);
            pad -> SetMargin(0.1,0.05,0.1,0.1);

            TString nameHist = Form("hist_d%dc%d",det,dch);
	    if(
            TCut cut = Form("det==%d && dch==%d",det,dch);
            auto hist = new TH1D(nameHist,cut,50,x1,x2);
            hist -> GetXaxis() -> SetLabelSize(0.065);
            hist -> GetYaxis() -> SetLabelSize(0.065);
		
            
            TString selection = Form("adc*%f>>%s",conversion_factor[det][dch],nameHist.Data());
            cout << nameHist.Data() << " " << selection << endl;
            tree -> Draw(selection,cut);

            if (hist->GetEntries()==0) // skip fitting if data do not exist
                continue;

            auto amplitude = hist -> GetBinContent(hist -> GetMaximumBin()); // get initial amplitude from histogram statistics
            auto mean = hist -> GetBinCenter(hist -> GetMaximumBin()); // get initial mean from histogram statistics
            auto sigma = hist -> GetStdDev(); // get initial stddev from histogram statistics
	    
	    //2nd local maximum finding!
	   // int secondMaxBin;
	   // int secondMaxContent;
	    
	   /* for(int i =1; i <= hist -> GetNbinsX(); ++i){
		
		double binContent = hist -> GetBinContent(i);
		if(binContent > secondMaxContent){
			secondMaxContent = binContent;
			secondMaxBin = i;
		if(binContent > hist -> GetBinContent(i+1)){
		break;
		}
	    }
	    }*/
		
	   // auto amplitude2 = secondMaxContent;
	   // auto mean2 = hist -> GetBinCenter(secondMaxBin);
	
            TF1 *fit = new TF1("fit","gaus(0)+gaus(3)",x1,x2);
           // fit -> SetParameters(amplitude, mean, sigma); // set initial parameter
           // fit -> SetRange(mean - 0.5*sigma, mean + 3*sigma); // set initial range
	    fit -> SetParLimits(0,amplitude-100,amplitude+100);
	    fit -> SetParLimits(1,mean-0.1,mean+0.1);
	    fit -> SetParLimits(2,0,1);
	      
	    fit -> SetParLimits(3,50,200);
	    fit -> SetParLimits(4,5.2,5.4);
	    fit -> SetParLimits(5,0,1);
            hist -> Fit(fit);
            cout << mean << endl;	


	   // auto fit2 = new TF1("fit2","gaus(0)",x1,x2);
	   // fit2 -> SetParameters(
           /* if (1) { // set range from the previous fit and perform fit
                amplitude = fit -> GetParameter(0);
                mean = fit -> GetParameter(1);
                sigma = fit -> GetParameter(2);
                cout << mean << endl;
                if (dch==1||dch==32)
                    fit -> SetRange(mean - 0.5*sigma, mean + 3*sigma);
                else
                    fit -> SetRange(mean - sigma, mean + 3*sigma);
                hist -> Fit(fit,"RQ");
            }*/
		
            amplitude = fit -> GetParameter(0);
            mean = fit -> GetParameter(1);
            sigma = fit -> GetParameter(2);
        	

	    //TFile outFile("fit_max.root","recreate");
	    //hist -> Write();		    
	    	
	   // fit -> Write();
	   // outFile.Close();


        }

       // cvs1 -> cd(); cvs1 -> SaveAs(Form("figures_calib/%s.pdf",cvs1->GetName()));
       // cvs2 -> cd(); cvs2 -> SaveAs(Form("figures_calib/%s.pdf",cvs2->GetName()));
    }
}
