

void cpp_pointer(){



//	TFile
//	(TTree *)file -> Get("channels"); 
	// TFile is parante, TTree is son. TObject Is parants of TH1, so we can transform TObject to TH1.

 //   TH1F *hist2  = (TH1F *)hist -> Clone("hist2");

//    int a= 5;
//    int b = 3;
//    double c = (double)a/b;

	


    TF1 *f1 = new TF1();

    int a = 3;
    int* b = &a;
    *b = 4;
     

}
