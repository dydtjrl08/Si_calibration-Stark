void tree_read(){

    TFile *input = mew TFile("data4.root","read");

    TTree *tree = (TTree *)input -> Get("tree");

    double x,y;

    tree -> SetBranchAddress("x",&x,"x/D");
    tree -> SetBranchAddress("y",&y,"y/D");
    
    int entries = tree -> GetEntries();

    for(int i = 0, i < entries; i++){

        tree -> GetEntry(i);
        cout << x << y << endl;

    }

    input -> Close();
}   