#include "sbnana/CAFAna/Core/Binning.h"
#include "sbnana/CAFAna/Core/LoadFromFile.h"

#include "TCanvas.h"
#include "TH1.h"
#include "TLegend.h"
#include "THStack.h"
#include "TFile.h"
#include "TGraph.h"
#include "TPaveText.h"

std::vector<CutInfo> make_cumulative_cuts(const std::vector<CutInfo> &cuts)
{
  std::vector<CutInfo> cumulative_cuts;
  SpillCut cumulativeCut = kNoSpillCut;

  for(unsigned i = 0; i < cuts.size(); ++i)
    {
      cumulativeCut = cumulativeCut && cuts[i].cut;
      CutInfo entry = {"Cumulative (" + cuts[i].name + ")", cumulativeCut, "Cumulative" + cuts[i].label};
      cumulative_cuts.push_back(entry);
    }

  cumulative_cuts.push_back(cumulative_cuts.back());
  cumulative_cuts.back().name = "Full Selection";
  cumulative_cuts.back().label = "Selection";  

  return cumulative_cuts;
}

std::vector<CutInfo> make_n_minus_one_cuts(const std::vector<CutInfo> &cuts)
{
  std::vector<CutInfo> n_minus_one_cuts;

  for(unsigned i = 1; i < cuts.size(); ++i)
    {
      SpillCut thisCut = kNoSpillCut;

      for(unsigned j = 1; j < cuts.size(); ++j)
	{
	  if(j != i)
	    thisCut = thisCut && cuts[j].cut;
	}

      CutInfo entry = {"N - 1 (" + cuts[i].name + ")", thisCut, "Nm1" + cuts[i].label};
      n_minus_one_cuts.push_back(entry);
    }
  return n_minus_one_cuts;
}

void fill_and_save_spectra(const std::string inputName, const std::vector<CutInfo> &cuts, const std::vector<TrueDef> &categories)
{
  SpectrumLoader loader(inputName);

  const Binning binsNuEn = Binning::Simple(25, 0, 5);

  const unsigned kNCategories = categories.size();
  const unsigned kNCuts = cuts.size();

  std::vector<std::vector<Spectrum*> > spectrums;

  for(unsigned i = 0; i < kNCuts; ++i)
    {
      spectrums.emplace_back(std::vector<Spectrum*>());
      
      for(unsigned j = 0; j < kNCategories; ++j)
        {
          spectrums[i].emplace_back(new Spectrum("True Interaction Energy (GeV)", binsNuEn, loader, kTrueNuEn, cuts[i].cut && kTrueFV && categories[j].cut));
        }
    }
  loader.Go();

  TFile fout("temp_spectra_save_file.root", "RECREATE");

  for(unsigned i = 0; i < kNCuts; ++i) 
    {
      for(unsigned j = 0; j < kNCategories; ++j)
	{
	  const std::string dirName = cuts[i].label + "_" + categories[j].label;
	  spectrums[i][j]->SaveTo(fout.mkdir(dirName.c_str()));
	}
    }
}

void plot_selection(const std::vector<CutInfo> &cuts, const std::vector<TrueDef> &categories, const double gPOT = 6.6e20)
{
  const std::string inFile = "temp_spectra_save_file.root";

  std::vector<TCanvas*> canvases;

  const unsigned kNCuts = cuts.size();
  const unsigned kNCategories = categories.size();

  Spectrum* totalSignalSpec = LoadFromFile<Spectrum>(inFile, "NoCuts_Signal").release();
  Spectrum* totalBackgroundSpec = LoadFromFile<Spectrum>(inFile, "NoCuts_Background").release();
  const double totalSignal = totalSignalSpec->Integral(gPOT);
  const double totalBackground = totalBackgroundSpec->Integral(gPOT);

  for(unsigned i = 0; i < kNCuts; ++i)
    {
      Spectrum* signalSpec = LoadFromFile<Spectrum>(inFile, cuts[i].label + "_Signal").release();
      Spectrum* backgroundSpec = LoadFromFile<Spectrum>(inFile, cuts[i].label + "_Background").release();
      const double signal = signalSpec->Integral(gPOT);
      const double background = backgroundSpec->Integral(gPOT);

      const double efficiency = 100. * signal / totalSignal;
      const double purity = 100. * signal / (signal + background);
      const double backrej = 100. * (1 - (background / totalBackground));

      TPaveText *pvt = new TPaveText(.6,.35,.8,.45, "NB NDC");
      pvt->SetTextAlign(12);
      pvt->AddText(Form("Efficiency: %.2f%%", efficiency));
      pvt->AddText(Form("Purity: %.2f%%", purity));
      pvt->AddText(Form("Backgroud Rej: %.2f%%", backrej));

      canvases.emplace_back(new TCanvas(Form("c%s", cuts[i].label.c_str()), Form("c%s", cuts[i].label.c_str())));
      TLegend *legend = new TLegend(.6,.55,.8,.8);
      THStack *hstack = new THStack(Form("hs%s", cuts[i].label.c_str()), Form("%s;True E_{#nu};Events (%g POT)", cuts[i].name.c_str(), gPOT));

      std::vector<TH1D*> hists;
  
      for(unsigned j = 0; j < kNCategories; ++j)
	{
	  if(categories[j].label == "Background")
	    continue;

	  const std::string dirName = cuts[i].label + "_" + categories[j].label;
	  Spectrum* spec = LoadFromFile<Spectrum>(inFile, dirName).release();

	  hists.emplace_back(spec->ToTH1(gPOT));
	  hists[j]->SetFillColor(categories[j].colour);
	  hstack->Add(hists[j]);
	  legend->AddEntry(hists[j], Form("%s (%'.0f)", categories[j].name.c_str(), spec->Integral(gPOT)), "f");
	}

      hstack->Draw("hist");
      legend->Draw();
      pvt->Draw();
    }
}

void plot_cumulative_selection_metrics(const std::vector<CutInfo> &cuts, const double gPOT = 6.6e20)
{
  const std::string inFile = "temp_spectra_save_file.root";

  const unsigned kNCuts = cuts.size();

  TH1F *efficiency = new TH1F("efficiency", ";;Fraction(%)", kNCuts-1, 0, kNCuts-1);
  TH1F *purity = new TH1F("purity", "", kNCuts-1, 0, kNCuts-1);
  TH1F *backrej = new TH1F("backrej", "", kNCuts-1, 0, kNCuts-1);

  Spectrum* totalSignalSpec = LoadFromFile<Spectrum>(inFile, cuts[0].label + "_Signal").release();
  Spectrum* totalBackgroundSpec = LoadFromFile<Spectrum>(inFile, cuts[0].label + "_Background").release();
  
  const double totalSignal = totalSignalSpec->Integral(gPOT);
  const double totalBackground = totalBackgroundSpec->Integral(gPOT);
  
  for(unsigned i = 0; i < kNCuts - 1; ++i)
    {
      Spectrum* signalSpec = LoadFromFile<Spectrum>(inFile, cuts[i].label + "_Signal").release();
      Spectrum* backgroundSpec = LoadFromFile<Spectrum>(inFile, cuts[i].label + "_Background").release();

      const double signal = signalSpec->Integral(gPOT);
      const double background = backgroundSpec->Integral(gPOT);

      efficiency->SetBinContent(i+1, signal / totalSignal);
      purity->SetBinContent(i+1, signal / (signal + background));
      backrej->SetBinContent(i+1, 1 - (background / totalBackground));
      std::string label = cuts[i].label.c_str();
      label.erase(0,10);
      efficiency->GetXaxis()->SetBinLabel(i+1, label.c_str());
    }

  TCanvas *cMetrics = new TCanvas("cMetrics","cMetrics");
  cMetrics->cd();
  cMetrics->SetBottomMargin(.3);
  cMetrics->SetTopMargin(.05);

  efficiency->GetXaxis()->LabelsOption("v");
  efficiency->GetXaxis()->SetLabelFont(62);
  efficiency->SetMaximum(1.1);
  efficiency->SetMinimum(0);

  efficiency->SetLineColor(kBlue);
  efficiency->SetMarkerColor(kBlue);
  efficiency->SetMarkerSize(2);
  efficiency->SetMarkerStyle(68);
  purity->SetLineColor(kMagenta);
  purity->SetMarkerColor(kMagenta);
  purity->SetMarkerSize(2);
  purity->SetMarkerStyle(68);
  backrej->SetLineColor(kRed);
  backrej->SetMarkerColor(kRed);
  backrej->SetMarkerSize(2);
  backrej->SetMarkerStyle(68);

  efficiency->Draw("p");
  purity->Draw("psame");
  backrej->Draw("psame");

  TLegend *l = new TLegend(.3,.2);
  l->SetFillColorAlpha(0,0);
  l->AddEntry(efficiency, "Efficiency", "p");
  l->AddEntry(purity, "Purity", "p");
  l->AddEntry(backrej, "Background Rej", "p");
  l->SetLineWidth(2);
  l->Draw();
}
