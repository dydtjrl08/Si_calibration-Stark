#include "TCut.h"
#include "TTree.h"
#include "TFile.h"
#include "TCanvas.h"

void cut_example() {
    // ROOT 파일과 TTree 열기
    TFile *file = TFile::Open("data4.root");
    TTree *tree = (TTree*)file->Get("tree");

    // TCut 객체 생성
    TCut cut1 = "x > 0"; // x가 0보다 큰 데이터
    TCut cut2 = "y < 10"; // y가 10보다 작은 데이터
    TCut combinedCut = cut1 && cut2; // x > 0 AND y < 10 조건 결합

    // 캔버스 생성
    TCanvas *c1 = new TCanvas("c1", "TCut Example", 800, 600);

    // 조건에 맞는 데이터 그리기
    tree->Draw("y:x", combinedCut);

    // 캔버스 저장
    c1->SaveAs("cut_example.png");

    // 파일 닫기
    file->Close();
}
