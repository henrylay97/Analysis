#include "sbnana/CAFAna/Core/Binning.h"
#include "sbnana/CAFAna/Core/LoadFromFile.h"

#include "TCanvas.h"
#include "TH1.h"
#include "TLegend.h"
#include "THStack.h"
#include "TFile.h"

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

  cumulative_cuts.back().name = "Full Selection";
  cumulative_cuts.back().label = "Selection";  

  return cumulative_cuts;
}

std::vector<CutInfo> make_n_minus_one_cuts(const std::vector<CutInfo> &cuts)
{
  std::vector<CutInfo> n_minus_one_cuts;

  for(unsigned i = 0; i < cuts.size(); ++i)
    {
      SpillCut thisCut = kNoSpillCut;

      for(unsigned j = 0; j < cuts.size(); ++j)
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

  for(unsigned i = 0; i < kNCuts; ++i)
    {
      canvases.emplace_back(new TCanvas(Form("c%s", cuts[i].label.c_str()), Form("c%s", cuts[i].label.c_str())));
      TLegend *legend = new TLegend(.6,.55,.8,.8);
      THStack *hstack = new THStack(Form("hs%s", cuts[i].label.c_str()), Form("%s;True E_{#nu};Events (%g POT)", cuts[i].name.c_str(), gPOT));

      std::vector<TH1D*> hists;
  
      for(unsigned j = 0; j < kNCategories; ++j)
	{
	  const std::string dirName = cuts[i].label + "_" + categories[j].label;
	  Spectrum* spec = LoadFromFile<Spectrum>(inFile, dirName).release();

	  hists.emplace_back(spec->ToTH1(gPOT));
	  hists[j]->SetFillColor(categories[j].colour);
	  hstack->Add(hists[j]);
	  legend->AddEntry(hists[j], Form("%s (%'.0f)", categories[j].name.c_str(), spec->Integral(gPOT)), "f");
	}

      hstack->Draw("hist");
      legend->Draw();
    }
}
