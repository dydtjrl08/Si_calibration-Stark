void constant(){



	TFile *file = new TFile("constant.root","READ");
	TTree *tree = (TTree *)file -> Get("t1");
	

	Double_t a;		
	Double_t b;		
	Short_t detector;
	Short_t channel;

	
	tree -> SetBranchAddress("a",&a);
	tree -> SetBranchAddress("b",&b);
	tree -> SetBranchAddress("detector",&detector);
	tree -> SetBranchAddress("channel",&channel);

	Int_t nentries = (Int_t)tree -> GetEntries();

	for(Int_t i = 0; i < nentries; i++){

		tree-> GetEntry(i);
		cout << a << " " <<double(b) << " " << detector << " " << channel << endl;
	}	


	cout << "finish" << endl;




}
