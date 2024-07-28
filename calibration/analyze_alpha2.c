void analyze_alpha2(){
	
	fstream file;
	file.open("data_0726/calibration_copied.txt",ios::out);


	Short_t adc;
	Short_t det;
	Short_t dch;


	TFile *file = new TFile("data_0726/RUN511.ch.root","read");

	TTree *tree = (TTree *)file -> Get("Channels");
	
	tree -> SetBranchAddress("adc",&adc);	
	tree -> SetBranchAddress("det",&det);	
	tree -> SetBranchAddress("dch",&dch);	

	int i = 0;
	int stack = 0;
	while(1){
		
		


}
