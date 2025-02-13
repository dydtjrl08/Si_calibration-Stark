double user_equation(Double_t *x,Double_t *par){

			double x0 = x[0];
			double amplitude = par[0];
			double mean = par[1];
			double sigma = par[2];
			
			
			double mean_2 = mean *(5.443 / 5.486); //MeV
			double sigma_2 = sigma * (mean_2 / mean); 
			double amplitude_2 = amplitude * sigma / 6.65625 / sigma_2;


			
			
			
			double exponent = - ( ( x0 - mean ) * (x0 - mean)) / ( 2 * sigma * sigma); 
			double exponent_2 = - ( ( x0 - mean_2 ) * (x0 - mean_2)) / ( 2 * sigma_2 * sigma_2); 
			
			
			double value_1 = amplitude * std::exp(exponent);
			double value_2 = amplitude_2 * std::exp(exponent_2);		
			
			double value = value_1 + value_2;	

			return value;
}



void Convert2APParameters(double *par, double &mean1, double &sigma1, double &amplitude1, double &mean2, double &sigma2, double &amplitude2){
	
	amplitude1 = par[0];
	mean1 = par[1];
	sigma1 = par[2];
	mean2 = mean1 * (5.443 / 5.486);
	sigma2 = (mean2 * sigma1) / mean1;
	amplitude2 = amplitude1 * sigma1 / 6.65625/ sigma2;

}







void data_fit_function(){
	
	gStyle -> SetTitleSize(0.09,"t");	
	
	
	
	
	
	
	
	
	for(int i = 2; i <=4 ; ++i){
		
		double x1 = 1450;
		double x2 = 1600;
		if(i ==3 || i == 4){
			x1 = 2800;
			x2 = 3200;
		}
		




		auto cvs1 = new TCanvas(Form("analysis_alpha_det%d_1", i),"cvs1",1200,700);
		cvs1 -> Divide(4,4);
		auto cvs2 = new TCanvas(Form("analysis_alpha_det%d_2", i),"cvs2",1200,700);
		cvs2 -> Divide(4,4);	



		for(int j = 1; j <= 32; ++j){
			
			if(i==3 && (j == 22 || j == 23)){
				x1 = 2500;
				x2 = 3500;
			}
			TVirtualPad *pad;
			
			TString hist_name = Form("hist_det_%d_dch_%d",i,j);
			TH1D *hist = new TH1D(hist_name," ",50,x1,x2);
			
			fstream file;
			file.open(Form("det_%d_dch%d.txt", i,j),ios::in);
			
			double value;
			while(1){

				file >> value;
				
				hist -> Fill(value);	
				
				if(file.eof()) break;

			}
			if(j <= 16){
				pad = cvs1 -> cd(j);
			}
			else{
				pad = cvs2 -> cd(j-16);
			}
			

			hist -> GetXaxis() -> SetLabelSize(0.065);
			hist -> GetYaxis() -> SetLabelSize(0.065);

			pad -> SetMargin(0.1,0.05,0.1,0.1);
	//		auto hist2 = (TH1D *) hist -> Clone(hist_name);
			
				
			
			auto amplitude = hist -> GetBinContent( hist -> GetMaximumBin());	
			auto mean = hist -> GetBinCenter( hist -> GetMaximumBin());	
			auto sigma = hist -> GetStdDev();	
			

			double energy_resolution = sigma / mean;
						
			double par[] = {amplitude, mean, sigma};
		//	double x[] = {};
			
		//	cout << user_equation(x,par) << endl;	
			TF1 *fit = new TF1("fit",user_equation,x1,x2,3);
			fit -> SetParameters(par);
			fit -> SetRange(mean - 0.5*sigma, mean * 3*sigma);	
		
			hist -> Draw();
			hist -> Fit(fit,"RQO");

		
			
			auto parameters = fit -> GetParameters();
			cout << "amplitude1 is " << parameters[0] << endl;
			double mean1,sigma1,amplitude1,mean2,sigma2,amplitude2;

			Convert2APParameters(parameters, mean1, sigma1, amplitude1, mean2, sigma2, amplitude2);
			cout <<"mean1 is " <<  mean1 <<" and mean2 is "<< mean2 << endl;
			auto fit_peak1 = new TF1("fit_peak1","gaus(0)",x1,x2);
			auto fit_peak2 = new TF1("fit_peak2","gaus(0)",x1,x2);
			fit_peak1 -> SetParameters(amplitude1,mean1,sigma1);
			fit_peak2 -> SetParameters(amplitude2,mean2,sigma2);

				

			fit_peak1 -> SetLineColor(kBlue);
			fit_peak2 -> SetLineColor(kYellow);
			
//			fit_peak1 -> Draw("samel");
//			fit_peak2 -> Draw("samel");
			
//			hist -> Fit(fit_peak1," samel");
//			hist -> Fit(fit_peak2," samel");
			Double_t param[6];
			
			
			fit_peak1 -> Draw("samel");
			fit_peak2 -> Draw("samel");

				
			fit_peak1 -> GetParameters(&param[0]);
			fit_peak2 -> GetParameters(&param[3]);
			
//			auto Total = new TF1("Total","gaus(0) + gaus(3)",x1,x2);
//			Total -> SetLineColor(kBlack);
//			Total -> SetParameters(param);
//			hist -> Fit(Total,"R+ samel");
	//		Total -> Draw("samel");
			file.close();


		//	hist -> Fit(fit2, "R+");
		//	gStyle->SetOptStat(1111);
//			cvs1 -> Update();
//			cvs2 -> Update();			
			
		}

		cvs1 -> cd();
		cvs1 -> SaveAs(Form("figures_det16_%d.png",i));
		cvs2 -> cd();
		cvs2 -> SaveAs(Form("figures_det32_%d.png",i));





	}




}
