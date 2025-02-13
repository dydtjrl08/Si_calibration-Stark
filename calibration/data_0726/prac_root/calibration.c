





double Henergy = 5.486; //[MeV]
double Lenergy = 5.443; //[MeV]

void calibration(){

	TFile *file = new TFile("RUN511.ch.root","READ");
	TTree *tree = (TTree *)file -> Get("channels");	
	
	fstream read;
	read.open("ax_b.txt",ios::in);
	for(auto det : {2,3,4}){
		
		double x1 = 1450;	
		double x2 = 1600;	
		if(det == 3 || det ==4 ){
			x1 = 2800;
			x2 = 3200;
		}



		TCanvas *c1 = new TCanvas(Form("det == %d dch1",det),"c1",1200,700);	
		c1 -> Divide(4,4);
		TCanvas *c2 = new TCanvas(Form("det == %d dch16",det),"c2",1200,700);	
		c2 -> Divide(4,4);


		for(auto dch = 1; dch <=32; dch++){
			
			double param[4];
			for(int i = 0; i < 4 ; i++){
				read >> param[i];
			}	
			
			double a = param[2]; 
			double b = param[3]; 
			if(det ==3 && (dch ==22 || dch == 23)){
					x1 = 2500;
					x2 = 3500;
					}
		
		
			if(dch <=16) c1 -> cd(dch);	
			else c2 -> cd(dch - 16);
	
		
			TCut cut_det = Form("det == %d", det);	
			TCut cut_dch = Form("dch == %d", dch);	
			
			TCut cut = cut_det && cut_dch;


		// y = ax + b
				
			
			TString namehist = Form("hist_det%d_dch%d",det,dch);
		
			
			TH1D *hist = new TH1D(namehist,cut,50,x1,x2);			
			hist -> SetStats(0);
				
			tree -> Draw(TString("adc>>")+namehist,cut,""); 
			
			double mean1 = hist -> GetBinCenter(hist -> GetMaximumBin());
			double mean2 = mean1 * 5.443 /5.486;
			if(det == 3 && (dch == 16 || dch >23)){
				continue;
			}
			else{	
				TH2D *hist2 = new TH2D(Form("hist_of_2d_%d_%d",det,dch),namehist,50,x1-100,x2,50,5.3,5.6);
				hist2 -> SetStats(0);
				hist2 -> Draw();	
				TMarker *marker1 = new TMarker(mean1, Henergy,20);
				marker1 -> SetMarkerColor(kRed);	
				marker1 -> Draw();

				TMarker *marker2 = new TMarker(mean2, Lenergy,20);
		
				marker2 -> SetMarkerColor(kBlue);	
				marker2 -> Draw();
			
				TLine *line = new TLine(mean1,5.486,mean2,5.443);
				line -> SetLineColor(kRed);
				line -> SetLineWidth(2);
				line -> Draw();

				TLegend *leg = new TLegend(0.6,0.1,0.8,0.3);
				leg -> AddEntry(marker1,"High alpha Energy");
				leg -> AddEntry(marker2,"Low alpha Energy");
				leg -> Draw();
			
			}
		}
	}

	read.close();
}
