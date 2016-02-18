#ifndef __CINT__
#endif

#include <iostream>
#include <sstream>
#include <fstream>
#include "TPaveLabel.h"

//#include "polRho.h"
#include <TH2.h>
#include <TCanvas.h>

#include "TROOT.h"
#include "TSystem.h"
#include "TFile.h"
#include "TChain.h"
#include "TLegend.h"
#include "TLorentzVector.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TRandom.h"
#include "TProfile.h"
#include "TStyle.h"



using namespace std;


void plotROC_eta2to3(int scenario, const char* input1, const char* input2, const char* output){
  cout << "input files: " << input1 << " and " << input2 << endl;

  vector<string> legendNames = {"ak4PFJetsCHS new PU Id", "ak4PFJetsCHS old PU Id", "ak4PFJets new PU Id", "ak4PFJets old PU Id","ak4PFJetsCHS new binning", "ak4PFJetsCHS old binning", "ak4PFJetsCHS new PU Id, new binning"};

  ifstream file_new;
  string linestring_new;
  vector<double> pt_new;
  vector<double> eta_new;
  vector<double> mvaOut_new;
  vector<int> matchJet_new;
  vector<int> matchPuJet_new;
  file_new.open(input1);
  if(file_new.good()){
    while(!file_new.eof()){
      getline(file_new,linestring_new);
      if(linestring_new.find(" ")!=string::npos){
	int pos1 = linestring_new.find(" ");
	pt_new.push_back(atof(linestring_new.substr(0,pos1).c_str()));
	int pos2 = linestring_new.substr(pos1+1).find(" ");
	mvaOut_new.push_back(atof(linestring_new.substr(pos1+1,pos2).c_str()));
	int pos3 = linestring_new.substr(pos1+pos2+1).find(": ");
	matchJet_new.push_back(atof(linestring_new.substr(pos1+pos2+pos3+5, 1).c_str()));
	int pos4 = linestring_new.substr(pos1+pos2+pos3+3).find(": ");
	matchPuJet_new.push_back(atof(linestring_new.substr(pos1+pos2+pos3+pos4+7,1).c_str()));
	int pos5 = linestring_new.substr(pos1+pos2+pos3+pos4+7).find("\n");
	eta_new.push_back(atof(linestring_new.substr(pos1+pos2+pos3+pos4+9, pos1+pos2+pos3+pos4+pos5+9).c_str()));
      }
    }
  }
  else{
    cout << input1 << " does not exist" << endl;
    exit(0);
  }

  /*for(int i=0; i<pt_new.size(); i++){                                                               
    cout << pt_new.at(i) << " " << mvaOut_new.at(i) << " " << matchJet_new.at(i) << " " << matchPuJet_new.at(i) << " " << eta_new.at(i) << endl;                                                           
    }*/


  ifstream file_old;
  string linestring_old;
  vector<double> pt_old;
  vector<double> eta_old;
  vector<double> mvaOut_old;
  vector<int> matchJet_old;
  vector<int> matchPuJet_old;
  file_old.open(input2);
  if(file_old.good()){
    while(!file_old.eof()){
      getline(file_old,linestring_old);
      if(linestring_old.find(" ")!=string::npos){
	int pos1 = linestring_old.find(" ");
	pt_old.push_back(atof(linestring_old.substr(0,pos1).c_str()));
	int pos2 = linestring_old.substr(pos1+1).find(" ");
	mvaOut_old.push_back(atof(linestring_old.substr(pos1+1,pos2).c_str()));
	int pos3 = linestring_old.substr(pos1+pos2+1).find(": ");
	matchJet_old.push_back(atof(linestring_old.substr(pos1+pos2+pos3+5, 1).c_str()));
	int pos4 = linestring_old.substr(pos1+pos2+pos3+3).find(": ");
	matchPuJet_old.push_back(atof(linestring_old.substr(pos1+pos2+pos3+pos4+7,1).c_str()));
	int pos5 = linestring_old.substr(pos1+pos2+pos3+pos4+9).find("\n");
	eta_old.push_back(atof(linestring_old.substr(pos1+pos2+pos3+pos4+9, pos1+pos2+pos3+pos4+pos5+9).c_str()));
      }
    }
  }
  else{
    cout << input2 << " does not exist" << endl;
    exit(0);
  }


  /*for(int i=0; i<pt_new.size(); i++){
    cout << pt_new.at(i) << " " << mvaOut_new.at(i) << " " << matchJet_new.at(i) << " " << matchPuJet_new.at(i) << " " << eta_new.at(i) << endl;
  }*/

  vector<double> pt2030_new;
  vector<double> mvaOut2030_new;
  vector<double> matchJet2030_new;
  vector<double> matchPuJet2030_new;

  for(int i=0; i<pt_new.size(); i++){
    if(pt_new.at(i) > 20 && pt_new.at(i) < 30 && abs(eta_new.at(i)) > 2. && abs(eta_new.at(i)) < 3. && mvaOut_new.at(i) != -2){
      pt2030_new.push_back(pt_new.at(i));
      mvaOut2030_new.push_back(mvaOut_new.at(i));
      matchJet2030_new.push_back(matchJet_new.at(i));
      matchPuJet2030_new.push_back(matchPuJet_new.at(i));
    }
  }

  vector<double> pt3050_new;
  vector<double> mvaOut3050_new;
  vector<double> matchJet3050_new;
  vector<double> matchPuJet3050_new;

  for(int i=0; i<pt_new.size(); i++){
    if(pt_new.at(i) > 30 && pt_new.at(i) < 50 && abs(eta_new.at(i)) > 2. && abs(eta_new.at(i)) < 3. && mvaOut_new.at(i) != -2){
      pt3050_new.push_back(pt_new.at(i));
      mvaOut3050_new.push_back(mvaOut_new.at(i));
      matchJet3050_new.push_back(matchJet_new.at(i));
      matchPuJet3050_new.push_back(matchPuJet_new.at(i));
    }
  }


  vector<double> pt2030_old;
  vector<double> mvaOut2030_old;
  vector<double> matchJet2030_old;
  vector<double> matchPuJet2030_old;

  for(int i=0; i<pt_old.size(); i++){
    if(pt_old.at(i) > 20 && pt_old.at(i) < 30 && abs(eta_old.at(i)) > 2. && abs(eta_old.at(i)) < 3. && mvaOut_old.at(i) != -2){
      pt2030_old.push_back(pt_old.at(i));
      mvaOut2030_old.push_back(mvaOut_old.at(i));
      matchJet2030_old.push_back(matchJet_old.at(i));
      matchPuJet2030_old.push_back(matchPuJet_old.at(i));
    }
  }

  vector<double> pt3050_old;
  vector<double> mvaOut3050_old;
  vector<double> matchJet3050_old;
  vector<double> matchPuJet3050_old;

  for(int i=0; i<pt_old.size(); i++){
    if(pt_old.at(i) > 30 && pt_old.at(i) < 50 && abs(eta_old.at(i)) > 2. && abs(eta_old.at(i)) < 3. && mvaOut_old.at(i) != -2){
      pt3050_old.push_back(pt_old.at(i));
      mvaOut3050_old.push_back(mvaOut_old.at(i));
      matchJet3050_old.push_back(matchJet_old.at(i));
      matchPuJet3050_old.push_back(matchPuJet_old.at(i));
    }
  }

  vector<double> signalEfficiency2030_new;
  vector<double> bkgFakeRate2030_new;

  for(int WP=0; WP<=20; WP++){
    int NUM_EFF = 0;
    int DENOM_EFF = 0;
    int NUM_FR = 0;
    int DENOM_FR = 0;
    for(int i=0; i<pt2030_new.size(); i++){
      if(mvaOut2030_new.at(i) >= -1.+0.1*WP  && matchJet2030_new.at(i) == 1)NUM_EFF++; 
      if(matchJet2030_new.at(i) == 1 )DENOM_EFF++;
      if(mvaOut2030_new.at(i) >= -1.+0.1*WP && matchPuJet2030_new.at(i) == 0)NUM_FR++; 
      if(matchPuJet2030_new.at(i) == 0 )DENOM_FR++;
    }
  signalEfficiency2030_new.push_back((double)NUM_EFF/(double)DENOM_EFF);
  bkgFakeRate2030_new.push_back((double)NUM_FR/(double)DENOM_FR);
  }

  vector<double> signalEfficiency3050_new;
  vector<double> bkgFakeRate3050_new;

  for(int WP=0; WP<=20; WP++){
    int NUM_EFF = 0;
    int DENOM_EFF = 0;
    int NUM_FR = 0;
    int DENOM_FR = 0;
    for(int i=0; i<pt3050_new.size(); i++){
      if(mvaOut3050_new.at(i) >= -1.+0.1*WP  && matchJet3050_new.at(i) == 1)NUM_EFF++; 
      if(matchJet3050_new.at(i) == 1 )DENOM_EFF++;
      if(mvaOut3050_new.at(i) >= -1+0.1*WP && matchPuJet3050_new.at(i) == 0)NUM_FR++; 
      if(matchPuJet3050_new.at(i) == 0 )DENOM_FR++;
    }
    signalEfficiency3050_new.push_back((double)NUM_EFF/(double)DENOM_EFF);
    bkgFakeRate3050_new.push_back((double)NUM_FR/(double)DENOM_FR);
  }

  vector<double> signalEfficiency2030_old;
  vector<double> bkgFakeRate2030_old;

  for(int WP=0; WP<=20; WP++){
    int NUM_EFF = 0;
    int DENOM_EFF = 0;
    int NUM_FR = 0;
    int DENOM_FR = 0;
    for(int i=0; i<pt2030_old.size(); i++){
      if(mvaOut2030_old.at(i) >= -1.+0.1*WP  && matchJet2030_old.at(i) == 1)NUM_EFF++; 
      if(matchJet2030_old.at(i) == 1 )DENOM_EFF++;
      if(mvaOut2030_old.at(i) > -1.+0.1*WP && matchPuJet2030_old.at(i) == 0)NUM_FR++; 
      if(matchPuJet2030_old.at(i) == 0 )DENOM_FR++;
    }
  signalEfficiency2030_old.push_back((double)NUM_EFF/(double)DENOM_EFF);
  bkgFakeRate2030_old.push_back((double)NUM_FR/(double)DENOM_FR);
  }

  vector<double> signalEfficiency3050_old;
  vector<double> bkgFakeRate3050_old;

  for(int WP=0; WP<=20; WP++){
    int NUM_EFF = 0;
    int DENOM_EFF = 0;
    int NUM_FR = 0;
    int DENOM_FR = 0;
    for(int i=0; i<pt3050_old.size(); i++){
      if(mvaOut3050_old.at(i) >= -1.+0.1*WP  && matchJet3050_old.at(i) == 1)NUM_EFF++; 
      if(matchJet3050_old.at(i) == 1 )DENOM_EFF++;
      if(mvaOut3050_old.at(i) > -1.+0.1*WP && matchPuJet3050_old.at(i) == 0)NUM_FR++; 
      if(matchPuJet3050_old.at(i) == 0 )DENOM_FR++;
    }
  signalEfficiency3050_old.push_back((double)NUM_EFF/(double)DENOM_EFF);
  bkgFakeRate3050_old.push_back((double)NUM_FR/(double)DENOM_FR);
  }

  cout << "new 20<pt<30:" << endl;
  for(int i=0; i<signalEfficiency2030_new.size(); i++){
    cout << signalEfficiency2030_new.at(i) << " " << bkgFakeRate2030_new.at(i) << " " << signalEfficiency2030_new.at(i)/bkgFakeRate2030_new.at(i) << endl;
  }
  
  cout << endl;

  cout << "old 20<pt<30:" << endl;
  for(int i=0; i<signalEfficiency2030_old.size(); i++){
    cout << signalEfficiency2030_old.at(i) << " " << bkgFakeRate2030_old.at(i) << " " << signalEfficiency2030_old.at(i)/bkgFakeRate2030_old.at(i) << endl;
  }

  cout << endl;

  cout << "new 30<pt<50:" << endl;
  for(int i=0; i<signalEfficiency3050_new.size(); i++){
    cout << signalEfficiency3050_new.at(i) << " " << bkgFakeRate3050_new.at(i) << " " << signalEfficiency3050_new.at(i)/bkgFakeRate3050_new.at(i) << endl;
  }
  
  cout << endl;

  cout << "old 30<pt<50:" << endl;
  for(int i=0; i<signalEfficiency3050_old.size(); i++){
    cout << signalEfficiency3050_old.at(i) << " " << bkgFakeRate3050_old.at(i) << " " << signalEfficiency3050_old.at(i)/bkgFakeRate3050_old.at(i) << endl;
  }

  TCanvas *c1 = new TCanvas("c1", "eta2to3", 200,10,700,500);
  c1->cd();
  c1->SetFillColor(0);
  
  c1->SetLogy(1);
  //c1->SetLogx(1);
  gStyle->SetOptStat(0);
  
  // Draw a frame to define the range
  TH1F *hr = c1->DrawFrame(0.75,0.2,1.,1.2);
  //hr->SetTitle("2<|#eta|<3, 20<p_T<30GeV");
  hr->SetXTitle("Signal Efficiency");
  hr->SetYTitle("Background Fake Rate");
  c1->GetFrame()->SetFillColor(0);
  c1->GetFrame()->SetBorderSize(12);
  int size_new = signalEfficiency2030_new.size();
  int size_old = signalEfficiency2030_old.size();
  Double_t xnew[size_new], ynew[size_new];
  Double_t xold[size_old], yold[size_old];
  for(int i=0; i<size_new; i++){
    xnew[i] = signalEfficiency2030_new.at(i);
    ynew[i] = bkgFakeRate2030_new.at(i);
    cout << "new: " << xnew[i] << " " << ynew[i] << endl;
  }
  for(int i=0; i<size_old; i++){
    xold[i] = signalEfficiency2030_old.at(i);
    yold[i] = bkgFakeRate2030_old.at(i);
    cout << "old: " << xold[i] << " " << yold[i] << endl;
  }
  gr1 = new TGraph(size_new,xnew,ynew);
  gr1->SetLineColor(2);
  gr1->SetLineWidth(5);
  //gr1->SetMarkerSize(1.);
  //gr1->SetMarkerStyle(21);
  gr1->Draw("L");
  c1->Update();
  gr2 = new TGraph(size_old,xold,yold);
  gr2->SetLineColor(4);
  gr2->SetLineWidth(5);
  //gr2->SetMarkerSize(1.);
  //gr2->SetMarkerStyle(21);
  gr2->Draw("L");

  leg = new TLegend(0.15,0.75,0.5,0.88);
  stringstream legendTitle_new;
  stringstream legendTitle_old;
  if(scenario==0){
    legendTitle_new << legendNames.at(0);
    legendTitle_old << legendNames.at(1);
  }
  else if(scenario==1){
    legendTitle_new << legendNames.at(2);
    legendTitle_old << legendNames.at(3);
  }
  else if(scenario==2){
    legendTitle_new << legendNames.at(4);
    legendTitle_old << legendNames.at(5);
  }
  else if(scenario==3){
    legendTitle_new << legendNames.at(6);
    legendTitle_old << legendNames.at(1);
  }
  else if(scenario==4){
    legendTitle_new << legendNames.at(6);
    legendTitle_old << legendNames.at(0);
  }
  leg->AddEntry(gr1,legendTitle_new.str().c_str(),"l");
  leg->AddEntry(gr2,legendTitle_old.str().c_str(),"l");
  leg->SetBorderSize(0);
  leg->SetFillColor(kWhite);
  leg->Draw();
  legendTitle_new.str(string());
  legendTitle_old.str(string());

  TLatex title;
  title.SetNDC();
  title.SetTextSize(0.04);
  title.SetTextAlign(11);
  title.DrawLatex(0.15,0.7,"0<|#eta|<2, 20<p_T<30GeV");

  TLatex latex;
  latex.SetNDC();
  latex.SetTextSize(0.04);
  latex.SetTextAlign(11);

  latex.DrawLatex(0.13,0.908,"#font[22]{CMS} #font[12]{Preliminary}");

  stringstream outstream_eps;
  stringstream outstream_svg;
  outstream_eps << output << "_ROC_pt20to30_eta2to3.eps";
  outstream_svg << output << "_ROC_pt20to30_eta2to3.svg";

  c1->SaveAs(outstream_eps.str().c_str());
  c1->SaveAs(outstream_svg.str().c_str());
  c1->Close();

  outstream_eps.str(string());
  outstream_svg.str(string());



  TCanvas *c2 = new TCanvas("c2", "eta2to3", 200,10,700,500);
  c2->cd();
  c2->SetFillColor(0);

  c2->SetLogy(1);
  //c1->SetLogx(1);                                                                                   
  TH1F *hr2 = c2->DrawFrame(0.75,0.2,1.,1.2);
  //hr2->SetTitle("2<|#eta|<3, 30<p_T<50GeV");
  hr2->SetXTitle("Signal Efficiency");
  hr2->SetYTitle("Background Fake Rate");
  c2->GetFrame()->SetFillColor(0);
  c2->GetFrame()->SetBorderSize(12);
  int size_new2 = signalEfficiency3050_new.size();
  int size_old2 = signalEfficiency3050_old.size();
  Double_t xnew2[size_new], ynew2[size_new];
  Double_t xold2[size_old], yold2[size_old];
  for(int i=0; i<size_new2; i++){
    xnew2[i] = signalEfficiency3050_new.at(i);
    ynew2[i] = bkgFakeRate3050_new.at(i);
    cout << "new: " << xnew2[i] << " " << ynew2[i] << endl;
  }
  for(int i=0; i<size_old2; i++){
    xold2[i] = signalEfficiency3050_old.at(i);
    yold2[i] = bkgFakeRate3050_old.at(i);
    cout << "old: " << xold2[i] << " " << yold2[i] << endl;
  }
  gr3 = new TGraph(size_new2,xnew2,ynew2);
  gr3->SetLineColor(2);
  gr3->SetLineWidth(5);
  gr3->Draw("L");
  c2->Update();
  gr4 = new TGraph(size_old2,xold2,yold2);
  gr4->SetLineColor(4);
  gr4->SetLineWidth(5);
  //gr4->SetMarkerSize(1.);
  //gr4->SetMarkerStyle(21);
  gr4->Draw("L");

  leg2 = new TLegend(0.15,0.75,0.5,0.88);
  if(scenario==0){
    legendTitle_new << legendNames.at(0);
    legendTitle_old << legendNames.at(1);
  }
  else if(scenario==1){
    legendTitle_new << legendNames.at(2);
    legendTitle_old << legendNames.at(3);
  }
  else if(scenario==2){
    legendTitle_new << legendNames.at(4);
    legendTitle_old << legendNames.at(5);
  }
  else if(scenario==3){
    legendTitle_new << legendNames.at(6);
    legendTitle_old << legendNames.at(1);
  }
  else if(scenario==4){
    legendTitle_new << legendNames.at(6);
    legendTitle_old << legendNames.at(0);
  }
  leg2->AddEntry(gr3,legendTitle_new.str().c_str(),"l");
  leg2->AddEntry(gr4,legendTitle_old.str().c_str(),"l");
  leg2->SetBorderSize(0);
  leg2->Draw();

  TLatex title1;
  title1.SetNDC();
  title1.SetTextSize(0.04);
  title1.SetTextAlign(11);
  title1.DrawLatex(0.15,0.7,"0<|#eta|<2, 30<p_T<50GeV");

  TLatex latex1;
  latex1.SetNDC();
  latex1.SetTextSize(0.04);
  latex1.SetTextAlign(11);

  latex1.DrawLatex(0.13,0.908,"#font[22]{CMS} #font[12]{Preliminary}");

  outstream_eps << output << "_ROC_pt30to50_eta2to3.eps";
  outstream_svg << output << "_ROC_pt30to50_eta2to3.svg";

  c2->SaveAs(outstream_eps.str().c_str());
  c2->SaveAs(outstream_svg.str().c_str());

  c2->Close();

  ROOT->ProcessLine(".q");

}

