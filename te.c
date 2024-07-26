void te(){
    fstream file;

    file.open("data/calibration_file.txt",ios::in);

    gStyle -> SetTitleSize(0.09,"t"); 
    

    auto file = new TFile("data/RUN511.ch.root","read");
    
    auto tree = (TTree *) file -> Get("channels");


    

    TCanvas *c1 = new TCanvas("c1","Canvas",200,200);


}