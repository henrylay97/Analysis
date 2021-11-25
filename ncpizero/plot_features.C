#include "sbnana/CAFAna/Core/Binning.h"
#include "sbnana/CAFAna/Core/Spectrum.h"
#include "sbnana/CAFAna/Core/SpectrumLoader.h"
#include "sbnana/CAFAna/StandardRecord/Proxy/SRProxy.h"
#include "sbnana/SBNAna/Cuts/VolumeDefinitions.h"
#include "sbnana/CAFAna/Core/Binning.h"
#include "sbnana/CAFAna/Core/LoadFromFile.h"

using namespace ana;

#include "Structs.h"
#include "GenericCuts.h"
#include "TrueEventCategories.h"
#include "NCPiZeroRecoVars.h"

#include "TCanvas.h"
#include "TH1.h"
#include "TLegend.h"
#include "THStack.h"

void fill_and_save_spectra(const std::string inputName, const std::vector<Plot> &plots, const std::vector<TrueDef> &categories)
{
  SpectrumLoader loader(inputName);

  const unsigned kNPlots = plots.size();
  const unsigned kNCategories = categories.size();

  std::vector<std::vector<Spectrum*> > spectrums;

  for(unsigned i = 0; i < kNPlots; ++i)
    {
      spectrums.emplace_back(std::vector<Spectrum*>());

      for(unsigned j = 0; j < kNCategories; ++j)
        {
          spectrums[i].emplace_back(new Spectrum(plots[i].name, plots[i].binning, loader, plots[i].variable, kTrueFV && categories[j].cut));
        }
    }
  loader.Go();

  TFile fout("temp_spectra_save_file.root", "RECREATE");

  for(unsigned i = 0; i < kNPlots; ++i)
    {
      for(unsigned j = 0; j < kNCategories; ++j)
        {
          const std::string dirName = plots[i].label + "_" + categories[j].label;
          spectrums[i][j]->SaveTo(fout.mkdir(dirName.c_str()));
	}
    }
}

void plotter(const std::vector<Plot> &plots, const std::vector<TrueDef> &categories, const double gPOT = 6.6e20, const bool save = false, std::string extraDir = "")
{
  const std::string inFile = "temp_spectra_save_file.root";

  std::vector<TCanvas*> canvases;

  const unsigned kNPlots = plots.size();
  const unsigned kNCategories = categories.size();

  for(unsigned i = 0; i < kNPlots; ++i)
    {
      canvases.emplace_back(new TCanvas(Form("c%s", plots[i].label.c_str()), Form("c%s", plots[i].label.c_str())));
      THStack *hstack = new THStack(Form("hs%s", plots[i].label.c_str()), plots[i].axes_labels.c_str());

      std::vector<TH1D*> hists;
      for(unsigned j = 0; j < kNCategories; ++j)
	{
	  const std::string dirName = plots[i].label + "_" + categories[j].label;
	  Spectrum* spec = LoadFromFile<Spectrum>(inFile, dirName).release();

	  hists.emplace_back(spec->ToTH1(gPOT));
	  hists[j]->SetLineColor(categories[j].colour);
	  hists[j]->SetLineWidth(4);
	  hists[j]->Scale(1./hists[j]->Integral());
	  hstack->Add(hists[j]);
	}

      hstack->Draw("histnostack");
      TLegend *legend = new TLegend(.65,.7,.85,.85);
      for(unsigned j = 0; j < kNCategories; ++j)
	legend->AddEntry(hists[j], categories[j].name.c_str(), "l");
      legend->Draw();

      if(save)
	{
	  std::string dir = "./plots/";
	  if(extraDir != "") dir += (extraDir + "/");

	  canvases[i]->Print((dir + plots[i].label + ".pdf").c_str());
	  canvases[i]->Print((dir + plots[i].label + ".png").c_str());
	}
    }
}

void plot_features(const std::string inputName = "defname: test100_official_test100_MC2021Bv1_prodoverlay_corsika_cosmics_proton_genie_nu_spill_gsimple-configh-v1_tpc_reco2_caf_sbnd")
{
  setlocale(LC_NUMERIC, "");
  const double gPOT = 1e20;

  fill_and_save_spectra(inputName, event_plots, ncpizero_categories);
  plotter(event_plots, ncpizero_categories, gPOT, true, "standard");
}

