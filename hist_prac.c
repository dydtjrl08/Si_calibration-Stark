double user_equation(double *x, double *par){
	double x0 = x[0];
	double amplitude = par[0];
	double mean = par[1];
	double sigma = par[2];

	if(x0 < mean - sigma) return 0;

	double exponent = -(x0 - mean)*(x0 - mean) / (2 * sigma * sigma);

	double value = amplitude * std::exp(exponent);

	return value;

}


void hist_prac(){

	TCanvas *c1 = new TCanvas("c1","Canvas",800,600);
	TH1F *hist = new TH1F("hist","Histogram",10,0,10);
	
	TRandom *rand = new TRandom2();
	rand -> SetSeed(30);
	for(int i = 0 ; i < 1e4; i++){
		double value = rand -> Gaus(5,1);
		hist -> Fill(value);


	}	

	hist -> GetXaxis() -> SetTitle("X axis");
	hist -> GetYaxis() -> SetTitle("Y axis");
	
	double amplitude = hist -> GetBinContent(hist -> GetMaximumBin());
	double mean = hist -> GetBinCenter(hist -> GetMaximumBin());
	double sigma = hist -> GetStdDev();




	TH1F *hist2;

	hist2 =(TH1F *) hist -> Clone("hist2");
	hist2 -> SetAxisRange(0,2);
	double amplitude2 = hist2 -> GetBinContent(hist2 -> GetMaximumBin());
	double mean2 = hist2 -> GetBinCenter(hist2 -> GetMaximumBin());
	double sigma2 = hist2 -> GetStdDev();

/* ------------------ set histogram -------------- */

	
	
//	c1 -> DivideSquae(2);
	

	double par[] = {amplitude,mean,sigma};
	
	double par2[] = {amplitude2, mean2, sigma2};

	TF1 *fit = new TF1("fit",user_equation,0,10,3);
	fit -> SetParameters(par);
	
	hist -> Draw();
	hist -> Fit("fit");
	c1 -> Update();	
//	hist -> SetLineColor(30);	
	
	
	TF1 *fit2 = new TF1("fit2",user_equation,0,2,3);
	fit2 -> SetParameters(par2);
	fit2 -> SetLineColor(kBlue);
	hist2 -> Draw("same");
	hist2 -> Fit("fit2");
	

}
