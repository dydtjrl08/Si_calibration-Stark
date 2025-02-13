void tree_write(){


    fstream file;
    file.open("data2.txt",ios::in);

    TFile *output = new TFile("data4.root","recreate");

    TTree *tree = new TTree("tree","tree");


    double x,y;

    tree -> Branch("x",&x,"x/D");
    tree -> Branch("y",&y,"y/D");


    while(1){


        file >> x >> y;
        if(file.eof()) break;

        tree -> Fill();

    }

    output -> Write();

    output -> Close();





    file.close();
    
}