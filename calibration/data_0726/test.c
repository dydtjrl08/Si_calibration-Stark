void test(){

	TCanvas *c1 = new TCanvas();
	

	for(int i = 2; i < 3; i++){
		
		for(int j = 1; j < 2; j++){
			fstream file;
			file.open(Form("det_%d_dch%d.txt",i,j),ios::out);
			TFile *input = new TFile("RUN511.ch.root","read");
			
			TTree *tree = (TTree *)input -> Get("channels");

			TH2F *hist = new TH2F("hist","Histogram",160,-1,1,100,-1,1);
			


			tree -> Scan();

			
			


			}



		}	
	}

