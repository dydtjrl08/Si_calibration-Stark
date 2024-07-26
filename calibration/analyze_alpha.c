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
	TH1F *hist = new TH1F(Form("hist_det == %d && dch == %d",2, 16),"Histogram",1000,1000,1600);

	double ratio = 0.128;
	int alpha_2nd = 0;

	TString s = "det == 2 && dch == 16";

	int entry_det2_dch16 = tree -> GetEntries(s);
        
	for(int i = 0; i < entry; ++i){
		tree -> GetEntry(i);
		if(det == 2 && dch == 16 && adc >= 1200 && adc <= 1420){
			hist -> Fill(adc);
			alpha_2nd++;	
		}
		if(ratio <= alpha_2nd/(double)entry_det2_dch16) break;
	

	}
        cout << "The ratio is " << Form("0.128 : %f", alpha_2nd/(double)entry_det2_dch16) << endl;	
	hist -> Draw();


	tree -> Refresh();
	if( tree -> GetEntries(s)== entry_det2_dch16) cout << "good" << endl;

	/*for (int det : {2, 3, 4})
	{
		double x1 = 1450;
		double x2 = 1600;
	//	if(det == 3 || det ==4 ){
	//		x1 = 2800;
	//		x2 = 3200;
	//	}	
		
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
		
			
			
			
			TString namehist = Form("hist_d%d__%d", det, dch);
			*/ //TCut cut = Form("adc >= %d && det == %d && dch == %d",1500, det,dch);
			//auto hist = new TH1D(namehist, cut, 100, x1, x2);
			
				
		
			//tree -> Draw(TString("adc>>")+namehist, cut, "");
			//if (hist -> GetEntries() == 0)
			//	continue;

			//cout << det << " " << dch << " " << endl;
			//fcal << det << " " << dch << " " << endl;
		

	




}


