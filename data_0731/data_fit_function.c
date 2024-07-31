
double AlphaEnergy1 = 5.486; // MeV (85.2%)
double AlphaEnergy2 = 5.443; // MeV (12.8%)
double AEBR = 6.65625; // 85.2 / 12.8



double user_equation(double *x,double *par){

			double x0 = x[0];
			double amplitude = par[0];
			double mean = par[1];
			double sigma = par[2];

			if(x0 < mean - sigma) return 0;
			double exponent = - ( ( x0 - mean ) * (x0 - mean)) / ( 2 * sigma * sigma); 
			double value = amplitude * std::exp(exponent);

			return value;
}



void data_fit_function(){
	for(int i = 2; i < 5 ; i++){
		
		double x1 = 1450;
		double x2 = 1600;

		

			
		if(i == 3 || i==4){
			x1 = 2800;
			x2 = 3200;
		}
			
		TCanvas *c1 = new TCanvas(Form("analysis_alpha_det%d_1",i),"canvas1",1200,700);
		c1 -> Divide(4,4);
			
		TCanvas *c2 = new TCanvas(Form("analysis_alpha_det%d_2",i),"canvas2",1200,700);
		c2 -> Divide(4,4);
		
		
		
		for(int j = 1; j < 33; j++){
		
			
			if(i == 3 && (j == 22 || j == 23)){
				x1 = 2500;
				x2 = 3500;

			}
			TVirtualPad* pad;
			if(j<=16)
				pad = c1 -> cd(j);
			else
				pad = c2 -> cd(j-16);
			pad -> SetMargin(0.1,0.05,0.1,0.1);
			
			fstream file;
			file.open(Form("det_%d_dch%d.txt", i,j),ios::in);
			
			TH1D *hist = new TH1D(Form("hist_d%dc%d",i,j)," ",100,x1,x2);
			
			
			double value;

			while(1){

			
				file >> value;
				hist -> Fill(value);
					
				if(file.eof()) break;

			}
			hist -> Draw();
		
			auto amplitude = hist -> GetBinContent( hist -> GetMaximumBin());	
			auto mean = hist -> GetBinCenter( hist -> GetMaximumBin());	
			auto sigma = hist -> GetStdDev();	
				
			double par[] = {amplitude, mean, sigma};
		//	double x[] = {};
			
		//	cout << user_equation(x,par) << endl;	
			TF1 *fit = new TF1("fit",user_equation,x1,x2,3);
			fit -> SetParameters(par);
			
			hist -> Fit("fit","RNQ");
			
			double mean2 = mean *(5.443 / 5.486);
			double amplitude2 = amplitude * (12.8 / 85.2);
			double sigma2 = sigma * (5.443 / 5.486);
			
			double par2[] = {amplitude2, mean2, sigma2};
			
			TF1 *fit2 = new TF1("fit2","gaus(0)",x1,x2,3);
		        fit2 -> SetLineColor(kBlue);	
			fit2 -> SetParameters(par2);
			

    
		//	fit2 -> SetLineColor(kBlue);

			hist -> Fit(fit2,"RNQ");
//			c1 -> Update();
//			c2 -> Update();
			



			amplitude = fit -> GetParameter(0);
			mean = fit -> GetParameter(1);
			sigma = fit -> GetParameter(2);
			
			amplitude2 = fit2 -> GetParameter(0);
			mean2 = fit2 -> GetParameter(1);
			sigma2 = fit2 -> GetParameter(2);
			
			double par_1[] = {amplitude,mean,sigma};
			double par_2[] = {amplitude2,mean2,sigma2};
			
			fit -> SetRange(mean - sigma, mean + 3*sigma);
			fit2 -> SetRange(mean2 -3* sigma2, mean2+sigma2);

	//		fit -> SetParameters(par_1);
	//		fit2 -> SetParameters(par_2);


			hist -> Fit(fit,"RQ+");
			hist -> Fit(fit2,"RQ+");

			
			c1-> Update();
			c2-> Update();
			file.close();
			
		}







	}




}
