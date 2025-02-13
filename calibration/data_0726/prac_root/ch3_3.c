// config bin width 

void ch3_3(){

	const Int_t NBINS = 5;
	Double_t edges[NBINS +1] = {0.0,0.2,0.3,0.6,0.8,1.0};

	TH1 *h1 = new TH1D("hist","config bin width",NBINS,edges);
	
	h1 -> Fill(3);
	Double_t s = h1 -> GetBinContent(5);	
	h1 -> Draw();
	cout << s << endl;



}
