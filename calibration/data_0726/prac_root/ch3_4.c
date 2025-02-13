// how to draw in pad



void ch3_4(){

	TCanvas *c1 = new TCanvas("c1","hist superimpose",800,1200);
	c1-> Divide(1,2);

	
	TH1D *hist = new TH1D("hist", "HIt",100,0,10);
	
	hist -> Fill(3);
	hist -> Fill(6);
	TH1D *hist2 = (TH1D *)hist -> Clone("hist2");
	c1-> cd(1);
	hist -> Draw();
	hist -> Fill(3);
	hist -> SetLineStyle(2);
	hist -> Fill(5);
	hist2 -> SetLineWidth(3);
	hist2 -> SetLineColor(kRed);
//	c1 -> Update();	
	hist2 -> GetXaxis() -> SetTitle("adc");
	hist2 -> GetYaxis() -> SetTitle("MeV");
	hist2 -> Draw("L SAME");

	TLegend *legend = new TLegend(0.7,0.3,0.9,0.5);
	legend -> AddEntry(hist,"raw");
	legend -> AddEntry(hist2,"renew");
	legend -> Draw();
	
	
}
