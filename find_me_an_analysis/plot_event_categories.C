#include "sbnana/CAFAna/Core/Binning.h"
#include "sbnana/CAFAna/Core/Spectrum.h"
#include "sbnana/CAFAna/Core/SpectrumLoader.h"

using namespace ana;

#include "sbnana/CAFAna/StandardRecord/Proxy/SRProxy.h"
#include "sbnana/SBNAna/Cuts/VolumeDefinitions.h"
#include "TrueEventCategories.h"

#include "TCanvas.h"
#include "TH1.h"
#include "TLegend.h"
#include "THStack.h"

const SpillVar kTrueNuEn([](const caf::SRSpillProxy* sp) -> float {
    float en(-5.f);
    for(auto const& nu : sp->mc.nu) {
      if(nu.E > en)
	en = nu.E;
    }
    return en;
  });

const SpillCut kFV([](const caf::SRSpillProxy* sp) {
    return PtInVolAbsX(sp->mc.nu[0].position, fvnd);
  });

//void plot_event_categories(const std::string inputName = "defname: official_MC2021Bv1_prodoverlay_corsika_cosmics_proton_genie_nu_spill_gsimple-configh-v1_tpc_reco2_flat_caf_sbnd")
void plot_event_categories(const std::string inputName = "defname: test100_official_test100_MC2021Bv1_prodoverlay_corsika_cosmics_proton_genie_nu_spill_gsimple-configh-v1_tpc_reco2_caf_sbnd")
{
  setlocale(LC_NUMERIC, "");
  SpectrumLoader loader(inputName);

  const Binning binsNuEn = Binning::Simple(20, 0, 5);
  const double kPOT = 1e20;

  const int kNTypes = categories.size();
  const int kNTypesNC = nc_categories.size();
  const int kNTypesCC = cc_categories.size();

  std::vector<Spectrum*> spectrums;
  std::vector<Spectrum*> spectrums_nc;
  std::vector<Spectrum*> spectrums_cc_numu;
  std::vector<Spectrum*> spectrums_cc_nue;

  for(int i = 0; i < kNTypes; ++i)
    {
      spectrums.emplace_back(new Spectrum("True Interaction Energy (GeV)", binsNuEn, loader, kTrueNuEn, kFV && categories[i].cut));
    }

  for(int i = 0; i < kNTypesNC; ++i)
    {
      spectrums_nc.emplace_back(new Spectrum("True Interaction Energy (GeV)", binsNuEn, loader, kTrueNuEn, kFV && nc_categories[i].cut));
    }

  for(int i = 0; i < kNTypesCC; ++i)
    {
      spectrums_cc_numu.emplace_back(new Spectrum("True Interaction Energy (GeV)", binsNuEn, loader, kTrueNuEn, kFV && kCCNuMu && cc_categories[i].cut));
      spectrums_cc_nue.emplace_back(new Spectrum("True Interaction Energy (GeV)", binsNuEn, loader, kTrueNuEn, kFV && kCCNuE && cc_categories[i].cut));
    }

  loader.Go();

  TCanvas* cAllTypes = new TCanvas("cAllTypes", "cAllTypes");
  TLegend *lAllTypes = new TLegend(.6,.55,.8,.8);
  THStack *hsAllTypes = new THStack("hsAllTypes",Form("All Events;True E_{#nu};Events (%g POT)", kPOT));

  TH1D* hists[kNTypes];
  
  for(int i = 0; i < kNTypes; ++i)
    {
      hists[i] = spectrums[i]->ToTH1(kPOT);
      hists[i]->SetFillColor(categories[i].colour);
      hsAllTypes->Add(hists[i]);
      lAllTypes->AddEntry(hists[i], Form("%s (%'.0f)", categories[i].name.c_str(), (kPOT / spectrums[i]->POT()) * hists[i]->GetEntries()), "f");
    }

  hsAllTypes->Draw("hist");
  lAllTypes->Draw();
  cAllTypes->SaveAs("./plots/true_event_categories_energy.png");
  cAllTypes->SaveAs("./plots/true_event_categories_energy.pdf");

  TCanvas* cNC = new TCanvas("cNC", "cNC");
  TLegend *lNC = new TLegend(.55,.5,.8,.8);
  THStack *hsNC = new THStack("hsNC",Form("NC Events;True E_{#nu};Events (%g POT)", kPOT));

  TH1D* hists_nc[kNTypesNC];
  
  for(int i = 0; i < kNTypesNC; ++i)
    {
      hists_nc[i] = spectrums_nc[i]->ToTH1(kPOT);
      hists_nc[i]->SetFillColor(nc_categories[i].colour);
      hsNC->Add(hists_nc[i]);
      lNC->AddEntry(hists_nc[i], Form("%s (%'.0f)", nc_categories[i].name.c_str(), (kPOT / spectrums_nc[i]->POT()) * hists_nc[i]->GetEntries()), "f");
    }

  hsNC->Draw("hist");
  lNC->Draw();
  cNC->SaveAs("./plots/true_event_categories_energy_nc.png");
  cNC->SaveAs("./plots/true_event_categories_energy_nc.pdf");

  TCanvas* cCCNuMu = new TCanvas("cCCNuMu", "cCCNuMu");
  TLegend *lCCNuMu = new TLegend(.55,.5,.8,.8);
  THStack *hsCCNuMu = new THStack("hsCCNuMu",Form("CC #nu_{#mu} Events;True E_{#nu};Events (%g POT)", kPOT));

  TH1D* hists_cc_numu[kNTypesCC];
  
  for(int i = 0; i < kNTypesCC; ++i)
    {
      hists_cc_numu[i] = spectrums_cc_numu[i]->ToTH1(kPOT);
      hists_cc_numu[i]->SetFillColor(cc_categories[i].colour);
      hsCCNuMu->Add(hists_cc_numu[i]);
      lCCNuMu->AddEntry(hists_cc_numu[i], Form("%s (%'.0f)", cc_categories[i].name.c_str(), (kPOT / spectrums_cc_numu[i]->POT()) * hists_cc_numu[i]->GetEntries()), "f");
    }

  hsCCNuMu->Draw("hist");
  lCCNuMu->Draw();
  cCCNuMu->SaveAs("./plots/true_event_categories_energy_cc_numu.png");
  cCCNuMu->SaveAs("./plots/true_event_categories_energy_cc_numu.pdf");

  TCanvas* cCCNuE = new TCanvas("cCCNuE", "cCCNuE");
  TLegend *lCCNuE = new TLegend(.55,.6,.8,.8);
  THStack *hsCCNuE = new THStack("hsCCNuE",Form("CC #nu_{e} Events;True E_{#nu};Events (%g POT)", kPOT));

  TH1D* hists_cc_nue[kNTypesCC];
  
  for(int i = 0; i < kNTypesCC; ++i)
    {
      hists_cc_nue[i] = spectrums_cc_nue[i]->ToTH1(kPOT);
      hists_cc_nue[i]->SetFillColor(cc_categories[i].colour);
      hsCCNuE->Add(hists_cc_nue[i]);
      lCCNuE->AddEntry(hists_cc_nue[i], Form("%s (%'.0f)", cc_categories[i].name.c_str(), (kPOT / spectrums_cc_nue[i]->POT()) * hists_cc_nue[i]->GetEntries()), "f");
    }

  hsCCNuE->Draw("hist");
  lCCNuE->Draw();
  cCCNuE->SaveAs("./plots/true_event_categories_energy_cc_nue.png");
  cCCNuE->SaveAs("./plots/true_event_categories_energy_cc_nue.pdf");
}
