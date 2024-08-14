void prac(){


	auto c1 = new TCanvas("c1","Candle Decay", 800, 600);
	c1 -> Divide(2,1);
	auto rng = new TRandom();
	auto h1 = new TH2I("h1","Decay",1000,0,1000,20,0,20);

	float myRand;
	for(int i = 0; i < 19; i++){
		for(int j =0 ; j < 1e6; j++){
			myRand = rng -> Gaus(350+i*8,20+2*i);
			h1 -> Fill(myRand,i);


		}




	}

	h1 -> SetBarWidth(2);
	h1 -> SetFillStyle(0);
	h1 -> SetFillColor(kGray);
	h1 -> SetLineColor(kBlue);
	h1 -> GetYaxis() -> SetTitle("time");
	h1 -> GetXaxis() -> SetTitle("probability density");

	c1 -> cd(1);
	h1 -> Draw("violiny(112000000)");
	c1 -> cd(2);
	auto h2 = (TH2I*)h1 -> Clone("h2");
	h2 -> SetBarWidth(0.8);
	h2 -> DrawCopy("candley2");


	gROOT -> GetListOfCanvases() -> Draw();
}
