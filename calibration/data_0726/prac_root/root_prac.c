





double Henergy = 5.486; //[MeV]
double Lenergy = 5.443; //[MeV]

void ax_b(){

	
	TFile *file = new TFile("fit_params.root","READ");
	
	fstream write;
	write.open("ax_b.txt",ios::out);
	for(auto det : {2,3,4}){
		
		TCanvas *c1 = new TCanvas(Form("det == %d dch1",det),"c1",1200,700);	
		c1 -> Divide(4,4);
		TCanvas *c2 = new TCanvas(Form("det == %d dch16",det),"c2",1200,700);	
		c2 -> Divide(4,4);


		for(auto dch = 1; dch <=32; dch++){
	
			if(dch <=16) c1 -> cd(dch);	
			else c2 -> cd(dch - 16);
	
	
			TF1 *fit1 = (TF1 *)file -> Get(Form("fit_peak1_det == %d dch == %d",det,dch));
			TF1 *fit2 = (TF1 *)file -> Get(Form("fit_peak2_det == %d dch == %d",det,dch));
		
			double mean1 = fit1 -> GetParameter(1);
			double sigma1 = fit1 -> GetParameter(2);
			double mean2 = fit2 -> GetParameter(1);
			double sigma2 = fit2 -> GetParameter(2);
		// y = ax + b
			TMatrixD A(2,2);
			A(0,0) = mean1; A(0,1) = 1;
			A(1,0) = mean2; A(1,1) = 1;
			
			TVectorD b(2);
			b(0) = Henergy; 
			b(1) = Lenergy; 
			cout << A(0,0) << " " << A(1,0) << endl;	
			double detA = A.Determinant();

			if(detA == 0){
			       	cout << "It has not the trivial solution" << endl;
				
			}
			TMatrixD A1(A);
			A1(0,0) = b(0);
			A1(1,0) = b(1);
			double detA1 = A1.Determinant();

			TMatrixD A2(A);
			A2(0,1) = b(0);
			A2(1,1) = b(1);
			double detA2 = A2.Determinant();
			// y = ax + b
			double a = detA1 / detA;
			double c = detA2 / detA;
			
			TString namehist = Form("hist_det%dcdch%d",det,dch);
		
			
			TH2D *hist = new TH2D(namehist,"2D",100,mean2 - 100,Lenergy,100,mean1 + 100,Henergy);			
			
			hist -> Fill(mean1,Henergy);	
			hist -> Fill(mean2,Lenergy);	
			hist -> SetStats(0);	
			hist -> Draw();
			
			TMarker *marker1 = new TMarker(mean1, Henergy,20);
			marker1 -> SetMarkerColor(kRed);	
			marker1 -> Draw();

			TMarker *marker2 = new TMarker(mean2, Lenergy,20);
		
			marker2 -> SetMarkerColor(kBlue);	
			marker2 -> Draw();
			
			TLegend *leg = new TLegend(0.6,0.3,0.8,0.5);
			leg -> AddEntry(marker1,"High alpha Energy");
			leg -> AddEntry(marker2,"Low alpha Energy");
			leg -> Draw();
			
			if(det == 3 && (dch == 16 || dch > 23))
				
				write << det <<" " << dch <<" " <<  -999 <<" " << -999 << endl;
			else
				write << det <<" " << dch <<" " <<  a <<" " << c << endl;
			
		}
	}

	write.close();
}
