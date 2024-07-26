void write(){

	
	TFile *file = new TFile("tut20.root","recreate");

	TTree *tree = new TTree("tree","tree");

	double x,y;


	tree -> Branch("x", &x, "x/D");
	tree -> Branch("y", &y, "y/D");

	TRandom2 *r = new TRandom2();

	for(int i = 0; i< 1e6 ; i++){
		x = 1 + r -> Rndm() * 9;
		y = x*2;
		tree -> Fill();

	}
	
	file-> Write();
	
	file -> Close();


}


void cut()
{	
	TCut cut1 = "x < 5";


	TFile *input = new TFile("tut20.root","read");
	
	TTree *tree = (TTree *)input -> Get("tree");

	
	tree -> Draw("y",cut1);	

}


void test_data(){

	write();
	
	TCut cut1 = "x < 5";
	TCut cut2 = "x > 6";
	TFile *input = new TFile("tut20.root","read");

	TTree *tree = (TTree *)input -> Get("tree");

	tree -> Draw("y",cut1&&cut2);

}	





