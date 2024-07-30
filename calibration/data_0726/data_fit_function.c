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
	TCanvas *c1 = new TCanvas();
	c1 -> Divide(4,4);
	TCanvas *c2 = new TCanvas();
	c2 -> Divide(4,4);
	for(int i = 2; i < 3 ; i++){

		for(int j = 1; j < 33; j++){
			TH1D *hist = new TH1D(Form("hist_det_%d_dch_%d",i,j)," ",1000,1200,1700);
			
			fstream file;
			file.open(Form("det_%d_dch%d.txt", i,j),ios::in);
			
			double value;

			while(1){


				file >> value;
				hist -> Fill(value);
					
				if(file.eof()) break;

			}
			if(j <= 16){
				c1 -> cd(j);
			}
			else{
				c2 -> cd(j-16);
			}
			hist -> Draw();
		
			auto amplitude = hist -> GetBinContent( hist -> GetMaximumBin());	
			auto mean = hist -> GetBinCenter( hist -> GetMaximumBin());	
			auto sigma = hist -> GetStdDev();	
				
			double par[] = {amplitude, mean, sigma};
		//	double x[] = {};
			
		//	cout << user_equation(x,par) << endl;	
			TF1 *fit = new TF1("fit",user_equation, mean - sigma, mean +sigma,3);
			fit -> SetParameters(amplitude, mean, sigma );
			
			hist -> Fit(fit,"R");
			
			double mean2 = mean *(5.443 / 5.486);
			double amplitude2 = amplitude * (12.8 / 85.2);
			double sigma2 = sigma * (5.443 / 5.486);
			
			

			TF1 *fit2 = new TF1("fit2",user_equation,mean2 - sigma2, mean2 + sigma2,3);
		        	
			fit2 -> SetParameters(amplitude2, mean2, sigma2);
			

			fit2 -> SetLineColor(kMagenta+2);
    

			hist -> Fit(fit2, "R+");
//			c1 -> Update();
//			c2 -> Update();			
			file.close();
			
		}







	}




}
