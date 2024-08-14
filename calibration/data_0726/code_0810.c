void code_0810(){

	


	TH2D *hist = new TH2D("hist","title",100,0,10,100,0,10);
	

	TH2D *hist2 = (TH2D *)hist -> Clone();
	
	hist -> Fill(3,2);

	TH1D *h1 = hist -> ProjectionX();
	h1 -> Draw();

}

