void test(){
	
	TRandom *rndm = new TRandom2();	
	rndm -> SetSeed(2);
	double rand = 0;
	
	TFile *file = new TFile("test.root","recreate");

	cout << rndm -> GetSeed() << endl;
	TCanvas *c1 = new TCanvas("c1","Canvas",800,600);
	TH1D *hist = new TH1D("hist","Histogram",1000,0,10);
	
	hist ->GetXaxis() ->  SetTitle("X");
	hist -> GetYaxis() -> SetTitle("Y");

	for(int i = 0; i < 1e4 ; i++){
		rand = rndm -> Gaus(5,2);
		hist -> Fill(rand);
		

	}
	

//	hist -> Draw();
	TH1D *h1 = (TH1D*)gDirectory -> Get("hist");
	h1 -> Draw();	
	file -> Write();
	

	

	TAxis *xaxis = hist -> GetXaxis();
	Double_t binCenter = xaxis -> GetLast();
	cout << binCenter << endl;
	









}
