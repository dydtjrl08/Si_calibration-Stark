




void regression(){
	double derivative_1;
	double derivative_2;
	double constant;


	

	for(int i = 2; i < 5; i++){
		
		


		double x1 = 1450;
		double x2 = 1600;
		if(i == 3 || i ==4){
			x1 = 2800;
			x2 = 3200;
		}
			
		TCanvas *c1 = new TCanvas(Form("alpha_det%d_1",i),"c1",1200,700);
/*		c1 -> Divide(4,4);
		TCanvas *c2 = new TCanvas(Form("alpha_det%d_2",i),"c2",1200,700);
		c1 -> Divide(4,4);
*/
		for(int j = 1; j < 33 ; j++){
			
			if(i ==3 && (j ==22 || j == 23)){
					x1 = 2500;
					x2 = 3500;
			}
			
		/*	TVirtualPad *pad;
			if(j <=16)
				pad = c1 -> cd(j);
			else
				pad = c2 -> cd(j - 16);
			pad -> SetMargin(0.1,0.05,0.1,0.1);
*/
			TString namehist = Form("det_%d_dch%d",i,j);
					
// allocating amp1 m1 s1 amp2 m2 s2 
			
			fstream file;
			file.open(Form("parameter_of_det%d_dch%d.txt",i,j),ios::in); // 각 디텍터,채널 번호마다 6개의 파라미터를 저장하였고, 이것을 par 배열에 저장한다.

			double par[6];
			for(int k = 0;  k < 6 ; k++){
				file >> par[k];

			
			}
			
			file.close();
			derivative_1 = 5.486/ par[1]; // high_energy linear constant 
			derivative_2 =  5.443/ par[4]; // low_energy linear constant
			
			
			fstream file_data;	
			
			file_data.open(namehist+TString(".txt"),ios::in);
			TH2D *hist = new TH2D(namehist,namehist,1000,x1,x2,1000,5.0,6.0);	
			
		        cout << derivative_1 << endl;		
			// energy는 adc를 calibration한 값. 5.4 ~ 5.7 [MeV] 사이로 나올 것이다.
			// par[0] = 특정 디텍터, 채널에서의 Relatively_High_energy Alpha ADC의 Maximum Amplitude (5.486[MeV])
			// par[1] = ~ ~ Mean Energy
			// par[2] = ~ ~ std
			// par[3] = ~ Relatively_Low_energy Alpha ADC의 Maximum Amplitude (5.443[MeV])
			// par[4],par[5]는 각각 mean,std of 5.443[MeV]
			Double_t adc;
			Double_t energy;
			while(1){
				file_data >> adc;
				if(file_data.eof()) break; 	
				if((adc > par[1]-par[2]) && adc < (par[1]+ 3*par[2])){ // range를 (mean - sigma, mean + 3*sigma)로 잡았다.  	
					energy = derivative_1 * adc; // relatively high alpha로 인식하고, adc값에 high_energy_calibation 상수를 곱한다.
					
					hist -> Fill(adc, energy); 
				}			
				else if((adc > par[4] - par[5]) && (adc < (par[4]+par[5]))){ // low Alpha는 범위를 더 좁게 잡았다.
					energy = derivative_2 * adc;

					hist -> Fill(adc, energy);
					}
				
			
			}
			hist -> GetXaxis() -> SetTitle("adc");
			hist -> GetYaxis() -> SetTitle("energy [MeV]");
			c1 -> cd();
			hist -> Draw();   // 2d histogram's option is default by the circle shape.
			double low_alpha_x = par[4];		
			double low_alpha_y = 5.443;		
			double high_alpha_x = par[1];		
			double high_alpha_y = 5.486;		
			
			
			TMarker *marker1 = new TMarker(low_alpha_x, low_alpha_y, 2);
			marker1 -> SetMarkerStyle(20);
			marker1 -> SetMarkerSize(2);
			marker1 -> SetMarkerColor(kRed);
			marker1 -> Draw("same");

			
			TMarker *marker2 = new TMarker(high_alpha_x, high_alpha_y, 2);
			marker2 -> SetMarkerStyle(20);
			marker2 -> SetMarkerSize(2);
			marker2 -> SetMarkerColor(kRed);
			marker2 -> Draw("same");

			TLine *line = new TLine(low_alpha_x,low_alpha_y,high_alpha_x,high_alpha_y);
			line -> SetLineColor(kBlack);
			line -> SetLineWidth(5);
			line -> Draw("same");

			c1 -> SaveAs(Form("figures_2D/figure2d_%d_%d.pdf",i,j));
		}

	}




}






