
Double_t HighAlpha = 5.486; // [MeV]
Double_t LowAlpha = 5.443; // [MeV]
Double_t FxTwoAlpha(Double_t *xp, Double_t *par);
void Convert2APParameters(double *par, double &mean1, double &sigma1, double &amplitude1, double &mean2, double &sigma2, double &amplitude2);

void two_peak_240811(){


	TFile *file = new TFile("RUN511.ch.root","read");
	TTree *tree = (TTree *)file -> Get("channels");
	
	TFile *write = new TFile("constant.root","RECREATE");	
	TTree *t1 = new TTree("t1","constants");
	
	Double_t a,b;
	Short_t detector,channel;
	t1 -> Branch("a",&a,"a/D");
	t1 -> Branch("b",&b,"b/D");

	t1 -> Branch("detector",&detector,"detector/S");
	t1 -> Branch("channel",&channel,"channel/S");
//	tree -> Print();	
	for(auto det : {2,3,4}){
			
			double x1 = 1450;
			double x2 = 1600;
			if (det ==3 || det == 4){
				x1 = 2800;
				x2 = 3200;
			}
		
			TCanvas *c1 = new TCanvas(Form("Fitting_of_det%d_1", det),Form("det== %d",det),1200,700);	
			c1 -> Divide(4,4);
			
			TCanvas *c2 = new TCanvas(Form("Fitting_of_det%d_2", det),Form("det== %d_2",det),1200,700);	
			c2 -> Divide(4,4);

			for(auto dch = 1; dch <=32; dch++){
				

				if (det == 3 && (dch == 22|| dch == 23)){
					x1 = 2500;
					x2 = 3500;
				}


				if(dch <=16) c1 -> cd(dch);
				else c2 -> cd(dch-16);
				
				TCut cut_det = Form("det == %d",det);
				TCut cut_dch = Form("dch == %d",dch);	
					
				TCut cut = cut_det && cut_dch;	
				
				TString name_of_hist = Form("hist_d%d_%d", det, dch);
				TH1D *hist = new TH1D(name_of_hist, cut, 50, x1, x2);
				hist -> GetXaxis() -> SetLabelSize(0.065);	
				hist -> GetYaxis() -> SetLabelSize(0.065);	
				tree -> Draw(TString("adc>>")+name_of_hist,cut,"");								
				if(hist -> GetEntries() == 0)
					continue;	
			//	TH1D *hist = (TH1D *)gPad -> GetPrimitive("htemp");	
				
				double amplitude = hist -> GetBinContent(hist -> GetMaximumBin());	
				double mean = hist -> GetBinCenter(hist -> GetMaximumBin());
				double sigma = hist -> GetStdDev();
				double adcOffset = 0;
				double energyResolution = sigma / mean;
		
				TF1 *fit = new TF1("fit",FxTwoAlpha,x1 ,x2, 3);
				
				fit -> SetParameter(0,energyResolution);
				fit -> SetParameter(1,mean);
				fit -> SetParameter(2,amplitude);
//				fit -> SetParameters(adcOffset,energyResolution,mean,amplitude);
			
				fit -> SetRange(mean - sigma, mean+ 3*sigma);
				if(det ==2){
					if(dch ==1)
						fit -> SetRange(1515, mean+ 3 * sigma);						
					else if(dch == 16)
						fit -> SetRange(1545, mean+3 *sigma);
					else if(dch == 17)
						fit -> SetRange(1535, mean+3 *sigma);
					else if(dch == 18)
						fit -> SetRange(1540, mean+3 *sigma);
					else if(dch == 21)
						fit -> SetRange(1520, mean+3 *sigma);
					else if(dch == 24){

						fit -> SetRange(1565, mean+3 *sigma);
						fit -> SetParLimits(2, 820, 870); 
						fit -> SetParLimits(1, 1569, mean+3*sigma);
					}

					else if(dch == 25)
						fit -> SetRange(1555, mean+3 *sigma);

					else if(dch == 30)
						fit -> SetRange(1530, mean+3 *sigma);

					else if(dch == 31)
						fit -> SetRange(1535, mean+3 *sigma);
					else if(dch == 32)
						fit -> SetRange(1530, mean+3 *sigma);
				}

				if(det == 3){
					if(dch == 22){
						fit -> SetRange(2750, mean+ 3*sigma);
					}
					else if(dch == 23){
						fit -> SetRange(2750, mean + 3*sigma);
					}
				}

				if(det ==2 && dch == 24){
					hist -> Fit(fit, "RN");
				}
				else{
					hist -> Fit(fit,"RQN");
				}
				gStyle -> SetOptStat("i");
				fit -> SetLineColor(kBlue);
				fit -> SetRange(x1,x2);
				fit -> Draw("SAME");
				auto parameters = fit -> GetParameters();
				double mean1,sigma1,amplitude1,mean2,sigma2,amplitude2;
				Convert2APParameters(parameters,mean1,sigma1,amplitude1,mean2,sigma2,amplitude2);
				
				auto fit_peak1 = new TF1("fit_peak1","gaus(0)",x1,x2);
				auto fit_peak2 = new TF1("fit_peak2","gaus(0)",x1,x2);
				fit_peak1 -> SetParameters(amplitude1, mean1, sigma1);
				fit_peak2 -> SetParameters(amplitude2, mean2, sigma2);
//				fit_peak1 -> SetRange(mean1 - 0.5*sigma1, mean1 + 3 *sigma1);
				fit_peak1 -> SetLineColor(kRed);
				fit_peak2 -> SetLineColor(kGreen+2);
				fit_peak1 -> Draw("samel");
				fit_peak2 -> Draw("samel");
				TLegend *legend = new TLegend(0.1,0.6,0.3,0.8);
				legend -> AddEntry(fit_peak1,"High_Alpha","l");
				legend -> AddEntry(fit_peak2,"Low_Alpha","l");
				legend -> Draw();
				
				TMatrixD A(2,2);
				A(0,0) = mean1; A(0,1) = 1.0;
				A(1,0) = mean2; A(1,1) = 1.0;

				TVectorD y(2);
				y(0) = HighAlpha;
				y(1) = LowAlpha;
				Double_t DetA = A.Determinant();
				if(DetA == 0 ){ 
					a = -999.;
					b = -999.;
					cout << Form("det = %d dch = %d doesn't have the solution",det,dch) << endl;
					detector = (Short_t)det;
					channel = (Short_t)dch;
					t1 -> Fill();
				}
				else{
					TMatrixD A1(A);
					A1(0,0)	= y(0);
					A1(1,0) = y(1);
					double DetA1 = (Double_t)A1.Determinant();
				
					TMatrixD A2(A);
					A2(0,1)	= y(0);
					A2(1,1) = y(1);
					double DetA2 =(Double_t) A2.Determinant();
					
					a = (Double_t)DetA1 / DetA;
					b = (Double_t)DetA2 / DetA;
					detector = (Short_t)det;
					channel = (Short_t)dch;
					t1 -> Fill();
					cout << "b is " << b << endl;
				}
			//	cout << det << " "<< dch << " " << mean1 << " " << sigma1 << " " << mean2 << " " << sigma2 << endl;
		//		cout << mean1 / mean2 << " " << 5.486 / 5.443 << endl;
		
			}	
		c1 -> cd();
		c1 -> SaveAs(Form("figures_det%d_1.jpg",det));
		c2 -> cd();
		c2 -> SaveAs(Form("figures_det%d_2.jpg",det));
	}

	t1 -> Write();
	t1 -> Print();
	write -> Close();

}


double FxTwoAlpha(Double_t *xp, Double_t *par){
	double x = xp[0];
	double ADCOffset = 0;
	double energyResolution = par[0];	
	double mean1 = par[1];
	double meanP1 = mean1 - ADCOffset;
	double sigma1 = energyResolution * meanP1;
	double amplitude1 = par[2];
	double ADCEnergyRatio = meanP1 / HighAlpha;
	
	double mean2 = LowAlpha * ADCEnergyRatio + ADCOffset;
	double meanP2 = mean2 - ADCOffset;
	double sigma2 = energyResolution * meanP2;
	double amplitude2 = amplitude1 * sigma1 / 6.65625 / sigma2;

	double value1 = amplitude1*exp(-0.5*((x-mean1)*(x-mean1)/sigma1/sigma1));
	double value2 = amplitude2*exp(-0.5*((x-mean2)*(x-mean2)/sigma2/sigma2));
	double value = value1 + value2;
	return value;
}

void Convert2APParameters(double *par, double &mean1, double &sigma1, double &amplitude1, double &mean2, double &sigma2, double &amplitude2){
	double ADCOffset = 0;
	double energyResolution = par[0];

	mean1 = par[1];
	double meanP1 = mean1 - ADCOffset;
	sigma1 = energyResolution * meanP1;
	amplitude1 = par[2];

	double ADCEnergyRatio = meanP1 / HighAlpha ;

	mean2 = LowAlpha * ADCEnergyRatio + ADCOffset;
	double meanP2 = mean2 - ADCOffset;
	sigma2 = energyResolution * meanP2;
	amplitude2 = amplitude1 * sigma1 / 6.65625 / sigma2;
}


