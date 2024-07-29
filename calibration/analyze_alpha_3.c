double user_exponent(double *x, double *par){
	                double x0 = x[0];
	                double amplitude = par[0];
			double mean = par[1];
                        double sigma = par[2];

	                if(x0 < mean - sigma) return 0;
			double exponent = -( (x0 - mean) * (x0 - mean) ) / (2 * sigma * sigma) ;
		        double value = amplitude * std::exp(exponent);
			
                        return value;
  
}







void analyze_alpha_3(){
	gStyle -> SetTitleSize(0.09,"t");

	int i, j;
	double mean, sigma;
	
	auto file = new TFile("data_0726/RUN511.ch.root","read");
	
	auto tree = (TTree *) file -> Get("channels");
	
	Short_t adc;
	tree -> SetBranchAddress("adc",&adc);
	for(auto det : {2, 3, 4})
	{
		
		
			auto cvs1 = new TCanvas(Form("raw_adc_det%d_1",int(det)),"cvs1",1200,700);
			cvs1-> Divide(4,4);			
			auto cvs2 = new TCanvas(Form("raw_adc_det%d_2",int(det)),"cvs2",1200,700);			
			cvs2 -> Divide(4,4);
		
			for(auto dch =1 ; dch <=32 ; ++dch){
				TVirtualPad* pad;		
				if(dch <=16)
					pad = cvs1 -> cd(dch);
				else
					pad = cvs2 -> cd(dch - 16);

				pad -> SetMargin(0.1,0.05,0.1,0.1);
					
				TString nameHist = Form("hist_d%dc%d", det, dch);	
				
				TCut cut = Form("det == %d && dch == %d",det, dch);
				
				auto hist = new TH1D(nameHist,cut,1000,0,2000);
				
			//	TString selection = Form("adc*f>>%s",1.0,nameHist.Data());		
				
		// there should be fixed from tree to hist		tree -> Draw("adc",cut);				
				
					
				auto mean = hist -> GetBinCenter(hist -> GetMaximumBin());
				auto amplitude = hist -> GetBinContent(hist -> GetMaximumBin());

				auto sigma = hist -> GetStdDev();
			 	cout << double(mean) << endl;	
				double x[] = {1000};
				double par[] = {amplitude,mean,sigma};
				cout << user_exponent(x,par) << endl;

				TF1 *fit = new TF1("fit",user_exponent,0,4000,3);
				
				fit -> SetParameters(amplitude,mean,sigma);
				hist -> Fit(fit,"RQ");
			}			

			//double integral1 = hist -> Integral(0,500);
	
//			cout <<Form("[GeV] small alpha scheme Ratio is %f",0.128/1) << endl;
//			cout << Form("Comparison ||||||||||||||||| ") << endl;
		
			
		}
	}

			
			//	tree -> Refresh();
//	if( tree -> GetEntries(s)== entry_det2_dch16) cout << "good" << endl;

	/*for (int det : {2, 3, 4})
	{
		double x1 = 1450;
		double x2 = 1600;
		if(det == 3 || det ==4 ){
			x1 = 2800;
			x2 = 3200;
		}	
		
		auto cvs1 = new TCanvas(Form("analysis_alpha_det%d_1",det),"cvs1",1200,700);
	        cvs1 -> Divide(4,4);
		auto cvs2 = new TCanvas(Form("analysis_alpha_det%d_2",det),"cvs2",1200,700);
		cvs2 -> Divide(4,4);

		for(int dch = 1; dch <=32; ++dch){
			
			if(det==3 && (dch == 22 || dch == 23)) {
				x1 = 2500;
				x2 = 3500;
			}

		
			TVirtualPad* pad;
			if(dch <= 16)
				pad = cvs1 -> cd(dch);
			else
				pad = cvs2 -> cd(dch - 16);
			pad -> SetMargin(0.1,0.05,0.1,0.1);
		
			
			
			
			TString namehist_85 = Form("hist_d%d__%d_alpha5.486MeV", det, dch);
			TString namehist_12 = Form("hist_d%d__%d_alpha5.443MeV", det, dch);
			
			TCut cut = Form("adc >= %d && det == %d && dch == %d",1500, det,dch);
			auto hist = new TH1D(namehist_85, cut, 100, x1, x2);
			
				
		
			tree -> Draw(TString("adc>>")+namehist, cut, "");
			if (hist -> GetEntries() == 0)
				continue;

			cout << det << " " << dch << " " << endl;
			fcal << det << " " << dch << " " << endl;
		

	
*/






