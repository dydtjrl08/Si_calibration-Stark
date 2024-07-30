void pa(){
	const int a{3};
	cout << a << endl;

	TH1F *hist = new TH1F("hist","Histogram",100,0,100);
	hist -> Fill(3);
	hist -> Fill(3);
	hist -> Fill(3);
	hist -> Fill(3);
	hist -> Fill(3);

	
	Double_t width = 600;
	Double_t height = 600;


	TCanvas *c1 = new TCanvas("c","c", width, height);
	c1 -> Divide(4,4,
	
}
