void ch3_5(){


	TF1 *f1 = new TF1("f1","gaus(0)",-3,3);	
	f1 -> SetParameters(100,0,1);
	f1 -> Draw("e");

	TLegend *legend = new TLegend(0.7,0.7,0.9,0.9);
	legend -> AddEntry(f1,"hist","l");
	
	f1 -> SetStats(0);	
	
	legend -> Draw();
	
	
	

}
