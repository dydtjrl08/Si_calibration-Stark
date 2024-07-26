void tut9(){
	
	TH1F *hist = new TH1F("hist", "Histogram", 1e3, 0, 10);

	TRandom2 *rand = new TRandom2();



	for(int i =0;i < 1e5; i ++){
		double r = rand -> Rndm()*9;
			
		hist -> Fill(r);

	}

	hist -> Draw();

	TF1 *fit = mew TF1("fit", "gaus",4, 6);

	hist -> Draw();
	hist -> Fit("fit","R");



}





	
