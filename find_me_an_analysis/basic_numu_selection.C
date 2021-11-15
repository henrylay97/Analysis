#include "sbnana/CAFAna/Core/Binning.h"
#include "sbnana/CAFAna/Core/Spectrum.h"
#include "sbnana/CAFAna/Core/SpectrumLoader.h"

using namespace ana;

#include "sbnana/CAFAna/StandardRecord/Proxy/SRProxy.h"
#include "sbnana/SBNAna/Cuts/VolumeDefinitions.h"

#include "TrueEventCategories.h"
#include "TrueNuVars.h"
#include "GenericCuts.h"
#include "CCNuMuCuts.h"

#include "TCanvas.h"
#include "TH1.h"
#include "TLegend.h"
#include "THStack.h"

void basic_numu_selection(const std::string inputName = "defname: test100_official_test100_MC2021Bv1_prodoverlay_corsika_cosmics_proton_genie_nu_spill_gsimple-configh-v1_tpc_reco2_caf_sbnd with limit 20")
{
  setlocale(LC_NUMERIC, "");
  SpectrumLoader loader(inputName);

  const Binning binsNuEn = Binning::Simple(25, 0, 5);
  const double kPOT = 1e20;

  std::vector<TrueDef> sig_back_categories = ccnumu_sig_back_categories;

  const int kNCategories = sig_back_categories.size();

  std::vector<Spectrum*> spectrums_no_cuts;
  std::vector<Spectrum*> spectrums_selection;

  const SpillCut kSelected = kRecoFV && kHasNuSlc && kHasAtLeastOneTrk && kLongestTrkLength;

  for(int i = 0; i < kNCategories; ++i)
    {
      spectrums_no_cuts.emplace_back(new Spectrum("True Interaction Energy (GeV)", binsNuEn, loader, kTrueNuEn, kTrueFV && sig_back_categories[i].cut));
      spectrums_selection.emplace_back(new Spectrum("True Interaction Energy (GeV)", binsNuEn, loader, kTrueNuEn, kSelected && kTrueFV && sig_back_categories[i].cut));
    }

  loader.Go();

  TCanvas* cNoCuts = new TCanvas("cNoCuts", "cNoCuts");
  TLegend *lNoCuts = new TLegend(.6,.55,.8,.8);
  THStack *hsNoCuts = new THStack("hsNoCuts",Form("No Cuts;True E_{#nu};Events (%g POT)", kPOT));

  TH1D* hists_no_cuts[kNCategories];
  
  for(int i = 0; i < kNCategories; ++i)
    {
      hists_no_cuts[i] = spectrums_no_cuts[i]->ToTH1(kPOT);
      hists_no_cuts[i]->SetFillColor(sig_back_categories[i].colour);
      hsNoCuts->Add(hists_no_cuts[i]);
      lNoCuts->AddEntry(hists_no_cuts[i], Form("%s (%'.0f)", sig_back_categories[i].name.c_str(), (kPOT / spectrums_no_cuts[i]->POT()) * hists_no_cuts[i]->GetEntries()), "f");
    }

  hsNoCuts->Draw("hist");
  lNoCuts->Draw();

  TCanvas* cSelection = new TCanvas("cSelection", "cSelection");
  TLegend *lSelection = new TLegend(.6,.55,.8,.8);
  THStack *hsSelection = new THStack("hsSelection",Form("Selection;True E_{#nu};Events (%g POT)", kPOT));

  TH1D* hists_selection[kNCategories];
  
  for(int i = 0; i < kNCategories; ++i)
    {
      hists_selection[i] = spectrums_selection[i]->ToTH1(kPOT);
      hists_selection[i]->SetFillColor(sig_back_categories[i].colour);
      hsSelection->Add(hists_selection[i]);
      lSelection->AddEntry(hists_selection[i], Form("%s (%'.0f)", sig_back_categories[i].name.c_str(), (kPOT / spectrums_selection[i]->POT()) * hists_selection[i]->GetEntries()), "f");
    }

  hsSelection->Draw("hist");
  lSelection->Draw();
}
