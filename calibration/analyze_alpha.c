void analyze_alpha(){
	gStyle -> SetTitleSize(0.09,"t");


	ofstream fcal("data_0726/calibration_copied.txt");


	auto file = new TFile("data_0726/RUN511.ch.root","read");
	
	auto tree = (TTree *) file -> Get("channels");
	
	Short_t adc;
	Short_t det;
	Short_t dch;

	tree -> SetBranchAddress("adc",&adc);
	
	tree -> SetBranchAddress("det",&det);
	tree -> SetBranchAddress("dch",&dch);
	
	int entry = tree -> GetEntries();
	TH1F *hist = new TH1F(Form("hist_det == %d && dch == %d",2, 10),"Histogram",50,1200,1280);

	double ratio = 0.128;
	int alpha_2nd = 0;

	TString s = "det == 2 && dch == 10";

	int entry_det2_dch16 = tree -> GetEntries(s);
        
//	hist -> SetRange(1200,1420);
	auto amplitude = hist -> GetBinContent(hist -> GetMaximumBin());

	auto sigma_alpha1 = hist -> GetStdDev();
	

	TH1F *hist2 = new TH1F(Form("hist_det == %d && dch == %d and high alpha",2,10),"Hist",50,1400,1600);
//	hist2 -> SetRange(1420,1800);
	auto sigma_alpha2 = hist2 -> GetStdDev();

	int entry_high = 0;

	for(int i = 0; i < entry; ++i){
		tree -> GetEntry(i);
		if(det == 2 && dch == 10 && adc >= 1200 && adc <= 1400){
			hist -> Fill(adc);
			alpha_2nd++;	
		}
		else if(det == 2 && dch == 10 && adc > 1400 && adc < 1600){
			hist2 -> Fill(adc);
			entry_high++;
		}
	//	if(ratio <= alpha_2nd/(double)entry_det2_dch16  ) break;
	

	}
        cout << "The ratio is " << Form("0.128 : %f", alpha_2nd/(double)entry_det2_dch16) << endl;	
	
	
	TCanvas *c1 = new TCanvas();
	
	TCanvas *c2 = new TCanvas();
	
	





	auto fit1 = new TF1("fit1","gaus",1200,1250);
	auto fit2 = new TF1("fit2","gaus",1500,1600);
	
	

	auto mean1 = hist -> GetBinCenter(hist -> GetMaximumBin());
	auto mean2 = hist2 -> GetBinCenter(hist2 -> GetMaximumBin());
	auto amplitude1 = hist -> GetBinContent(hist -> GetMaximumBin());
	auto amplitude2 = hist2 -> GetBinContent(hist2 -> GetMaximumBin());
	double ratio_real = mean1 / mean2 ;

	auto sigma1 = hist -> GetStdDev();
	auto sigma2 = hist2 -> GetStdDev();
	cout << "sigma :" << " " << sigma1 << endl;

	cout <<Form("ratio of mean : %f", mean1 /(double) mean2) << endl;
        cout <<  amplitude1 /(double) amplitude2 << endl;
	
	cout << Form("Gev ratio : %f", ratio_real) << endl;;
	cout << Form("Gev ratio : %f", 5.443 / 5.486) << endl;
	
	fit1 -> SetRange(mean1 - sigma1, mean1 + 3*sigma1);
	fit2 -> SetRange(mean2 - sigma2, mean2 + 3*sigma2);
	
	fit1 -> SetParameters(amplitude1, mean1, sigma1);
	fit2 -> SetParameters(amplitude2, mean2, sigma2);

	c1 -> cd();
	hist -> Draw();
	hist -> Fit(fit1,"RQ");
	
	c2 -> cd();
	hist2 -> Draw();

	hist2 -> Fit(fit2,"RQ");

	

	double integral1 = hist -> Integral(0,50);

	double integral2 = hist2 -> Integral(0, 50);
	
	cout <<Form("[GeV] small alpha scheme Ratio is %f",0.128/1) << endl;
	cout << Form("Comparison ||||||||||||||||| ") << endl;
	cout << integral1 / (integral2 + integral1) << endl;
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



}


