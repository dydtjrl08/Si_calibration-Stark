double user_exponent(double *x, double *par){
	        double x0 = x[0];
	        double amplitude = par[0];
		double mean = par[1]; 
		double sigma = par[2];

	        if(x0 < mean - sigma) return 0;
        	double exponent = -( (x0 - mean) * (x0 - mean) ) / (2 * sigma * sigma) ;
		double value = amplitude * std::exp(exponent);

		return value;

}




void one_gauss(){
	
         double par[] = {100,50,20};                                                                                              
	 double x[] = {50};
	 
	 
	 TH1D * hist = new TH1D("hist","",200,0,100);
	 for(int i = 0; i < 10000; ++i){
		 double value = gRandom -> Gaus(50,10);
		 hist -> Fill(value);
		 }
	 hist -> Draw();

	 cout << user_exponent(x,par) << endl;
	                                      
	 TF1 *f1 = new TF1("f1",user_exponent,0,100,3);
	 f1 -> SetParameters(100,50,20);
	 f1 -> SetNpx(1000);
	 f1 -> SetParNames("Amplitude","Mean","Sigma");
	 hist -> Fit(f1);	 

}

void practice()
{
    gStyle -> SetTitleSize(0.09,"t"); // set title size on the top of the histograms

    int i, j;
    double mean, sigma;
    double conversion_factor[5][33] = {0};
    
    fstream output;
    output.open("data_0726/practice.txt",ios::out);

   // while (fcal >> i >> j >> mean >> sigma)
   //     conversion_factor[i][j] = 5.486/mean;
    
    auto file = new TFile("data_0726/RUN511.ch.root","read");
    auto tree = (TTree*) file -> Get("channels");
    
    TString a =  Form("hello %d",3);
    TCut s = Form("det == %d && dch == %d  ", det, dch);		
    cout << a << endl;
    tree -> 
    
    
    //first order : main source	
   // cout << &det << endl;
   // short_t det;
   // short_t dch;
   // short_t adc;

   // tree -> GetBranchAddress("det",&det);	
   // tree -> GetBranchAddress("dch",&dch);	
   // tree -> GetBranchAddress("adc",&adc);	



		
            

	    
}












		
	      
	   // fit -> SetParLimits(3,50,200);
	   // fit -> SetParLimits(4,5.2,5.4);
	   // fit -> SetParLimits(5,0,1);
          //  hist -> Fit(fit);
           // cout << mean << endl;	


	   // auto fit2 = new TF1("fit2","gaus(0)",x1,x2);
	   // fit2 -> SetParameters(
           /* if (1) { // set range from the previous fit and perform fit
                amplitude = fit -> GetParameter(0);
                mean = fit -> GetParameter(1);
                sigma = fit -> GetParameter(2);
                cout << mean << endl;
                if (dch==1||dch==32)
                    fit -> SetRange(mean - 0.5*sigma, mean + 3*sigma);
                else
                    fit -> SetRange(mean - sigma, mean + 3*sigma);
                hist -> Fit(fit,"RQ");
            }*/
		
           // amplitude = fit -> GetParameter(0);
           // mean = fit -> GetParameter(1);
           // sigma = fit -> GetParameter(2);
        	

	    //TFile outFile("fit_max.root","recreate");
	    //hist -> Write();		    
	    	
	   // fit -> Write();
	   // outFile.Close();


       // }

       // cvs1 -> cd(); cvs1 -> SaveAs(Form("figures_calib/%s.pdf",cvs1->GetName()));
       // cvs2 -> cd(); cvs2 -> SaveAs(Form("figures_calib/%s.pdf",cvs2->GetName()));
//}
//}
