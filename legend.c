void legend(){
	

	TFile *file = new TFile("t.root","recreate");

	

	TH1F *hist = new TH1F("hist","Histogram",100,-10,10);

	

	TRandom2 *rand = new TRandom2();
	
	

	double r;
	double s;
	for(int i = 0 ; i < 7*1e3; ++i){

		r = rand -> Gaus(-2,1);
		
		hist -> Fill(r);
		
	}



	for(int i = 0; i <5*1e2; ++i){
		s = rand -> Gaus(3,1.5);

		hist -> Fill(s);
	}
	

	TF1 *fit = new TF1("fit","gaus(0)+gaus(3)", -10, 10);
	fit -> SetParLimits(0,2500,3000);
	fit -> SetParLimits(1,-4,-1);
	fit -> SetParLimits(2,0.5,1.5);
	
	fit -> SetParLimits(3,200,250);
	fit -> SetParLimits(4,2.5,3.5);
	fit -> SetParLimits(5,1,2);
	
	
	
	
	
	

	hist -> Draw();
	hist -> Fit(fit,"R");
	
	file -> Write();











}	
