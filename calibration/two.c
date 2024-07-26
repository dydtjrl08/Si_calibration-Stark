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




void two(){
	
	TH1D * hist = new TH1D("hist","",200,0,100);	
	for(int i = 0; i < 10000; ++i){
		double value = gRandom -> Gaus(50,10);
		hist -> Fill(value);
	
	}
	
	hist -> Draw();
	
	
	double x[] = {50};
	double par[] = {100,50,20};	
		
	cout << user_equation(x,par) << endl;

	TF1 *f1 = new TF1("f1",user_equation,0,100,3);
	f1 -> SetParameters(100,50,10);
	f1 -> SetParNames("Amplitude","Mean","Sigma");
	
	
	f1 -> SetNpx(1000); // set the number of points used to draw the function.
	hist -> Fit(f1);
}
