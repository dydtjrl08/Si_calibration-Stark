void a(){
    Short_t adc,det,dch;

        TFile *file = new TFile("data/RUN511.ch.root","read");
        TTree *tree = (TTree*) file -> Get("channels");




        

        //TCanvas *c1 = new TCanvas(); // 32행 3열 캔버스 만들기
        //TCanvas *c1 = new TCanvas("cvs","cvs",2000,2000);

        //c1 -> Divide(3,12);
        tree -> SetBranchAddress("adc",&adc);
        tree -> SetBranchAddress("det",&det); // 디텍터는 3개다.
        tree -> SetBranchAddress("dch",&dch); // 채널이다. 채널의 개수 : 32개


        int entry = tree -> GetEntries(); // 데이터의 entry 총 개수


        TH1D *Hist_adc[32]; // 배열로 히스토그램 하나의 det의 32개 채널 선언


 /*       for(int k = 1; k < 33; k++){
    
            Hist_adc[k-1] = new TH1D(Form("hist%i_%i",3,k),Form("Histo%i_%i",3,k),50,1450,1600); // 여기 있는 2는 detetor의 번호를 의미. 3,4로 바꿔서 돌려라.

        }
*/


        int entry_max = 0;



        while(1){
            tree -> GetEntry(entry_max);  
            entry_max ++; // 읽은 엔트리 세기
            
            if(entry_max > entry) break; // 전부 조회했으면 roop에서 나오기

            
            if(det == 2){
                Hist_adc[dch-1] -> Fill(adc);        


            }   // 2번 디텍터에 빈 채우기
             


        } // 모든 엔트리를 읽었으면 이 괄호를 빠져나온다.
        

        fstream File;

        File.open("result_2.txt",ios::out);

        for(int i = 0; i < 32 ; i++){
            //c1->cd(i+1);
            auto fit = new TF1("fit","gaus(0)",1450,1600);
            //fit->Reset("ICESM");
            //Hist_adc[i] -> Fit(fit,"RQ");
            //Hist_adc[i] ->Draw();
           

            auto amplitude = fit -> GetParameter(0);
            auto mean = fit -> GetParameter(1);
            auto sigma = fit -> GetParameter(2);
            File << amplitude <<" "<< mean <<" "<< sigma << endl;

        }


        
    File.close();
        

               
}
    