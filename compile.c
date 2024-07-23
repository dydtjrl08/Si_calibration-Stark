#include "TStopwatch.h"
#include "TRandom2.h"

#include <iostream>


using namespace std;

void compile(){


    TStopwatch t;


    TRandom2 *r = new TRandom2();


    double x = 0;
    TH1F *hist = new TH1F("hist","Histogram",100,0,10);

    for(int i =0; i < 1e2; i++){

        x += r -> Rndm();
        hist -> Fill(x);

    }


    cout << x << endl;

    t.Print();

    hist -> Draw("life");
}