
// Create histograms with several methods!


void ch3_2(){

	TH1 *hist1 = new TH1D("hist","Title of hist1",100,0,10);

	hist1 -> Fill(3);
	hist1 -> Fill(5);
//	hist1 -> Draw();

	/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
	TH2 *d2 = new TH2D("hist2","2D histogram",100,0,10,100,0,10);
	
	d2 -> Fill(3,2);
	d2 -> Fill(5,1);
	TH1D *d1 = d2 -> ProjectionX();
//	d1 -> Draw();


	TH1D *hist3 = new TH1D("hist3","Title",100,0,10);
	
	TH1D *hist4 = (TH1D *)hist3 -> Clone();
	
//	hist4 -> Draw();

}





