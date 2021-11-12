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

  std::vector<Spectrum*> spectrums;

  for(int i = 0; i < kNTypes; ++i)
    {
      spectrums.emplace_back(new Spectrum("True Interaction Energy (GeV)", binsNuEn, loader, kTrueNuEn, kFV && categories[i].cut));
    }

  loader.Go();

  TCanvas* c1 = new TCanvas("c1", "c1");
  TLegend *l1 = new TLegend(.6,.55,.8,.8);
  THStack *hs = new THStack("hs",Form(";True E_{#nu};Events (%g POT)", kPOT));

  TH1D* hists[kNTypes];
  
  for(int i = 0; i < kNTypes; ++i)
    {
      hists[i] = spectrums[i]->ToTH1(kPOT);
      hists[i]->SetFillColor(categories[i].colour);
      hs->Add(hists[i]);
      l1->AddEntry(hists[i], Form("%s (%'.0f)", categories[i].name.c_str(), (kPOT / spectrums[i]->POT()) * hists[i]->GetEntries()), "f");
    }

  hs->Draw("hist");
  l1->Draw();
  c1->SaveAs("./plots/true_event_categories_energy.png");
  c1->SaveAs("./plots/true_event_categories_energy.pdf");
}
