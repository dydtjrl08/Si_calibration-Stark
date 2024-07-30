void data_make_function(){

	
	

	for(int i = 2; i < 5; i++){
		
		for(int j = 1; j < 33; j++){
			fstream file;
			file.open(Form("det_%d_dch%d.txt",i,j),ios::out);
			TFile *input = new TFile("RUN511.ch.root","read");
			
			TTree *tree = (TTree *)input -> Get("channels");

			Short_t adc;
			Short_t det;
			Short_t dch;
			
			tree -> SetBranchAddress("adc",&adc);		
			tree -> SetBranchAddress("det",&det);		
			tree -> SetBranchAddress("dch",&dch);


			int entries = tree -> GetEntries();

			
			for(int k = 0; k < entries; k++){
				tree -> GetEntry(k);
				
				if(det == i && dch == j)
					file << adc << endl;
				
				}		
			cout << Form("det %d and dch %d is okay.",i,j);
			file.close();
			}

	}	














}
