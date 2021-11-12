// Make a plot with cuts
#include "sbnana/CAFAna/Core/Binning.h"
#include "sbnana/CAFAna/Core/Spectrum.h"
#include "sbnana/CAFAna/Core/SpectrumLoader.h"

using namespace ana;

#include "sbnana/CAFAna/StandardRecord/Proxy/SRProxy.h"
#include "sbnana/SBNAna/Vars/NueVars.h"
#include "sbnana/SBNAna/Cuts/TruthCuts.h"
#include "sbnana/SBNAna/Cuts/VolumeDefinitions.h"

#include "TCanvas.h"
#include "TH1.h"
#include "TLegend.h"

const SpillVar kTrueNuEn([](const caf::SRSpillProxy* sp) -> float {
    float en(-5.f);
    for(auto const& nu : sp->mc.nu) {
      if(nu.E > en)
	en = nu.E;
    }
    return en;
  });

const SpillCut kTruthDef([](const caf::SRSpillProxy* sp) {
    if(!kIsNueSpill(sp)) return false;
    if(sp->mc.nu[0].isnc) return false;
    return PtInVolAbsX(sp->mc.nu[0].position, fvnd);
  });

const SpillCut kHasNuSlc([](const caf::SRSpillProxy* sp) {
    bool hasNu(false);
    for(auto const& slc : sp->slc){
      if(!slc.is_clear_cosmic) hasNu = true;
    }
    return hasNu;
  });

const SpillVar kBestSliceID([](const caf::SRSpillProxy* sp) -> unsigned {
    unsigned index(999999);
    float nu_score(-5.f);
    for(int i = 0; i < sp->nslc; ++i){
      auto const &slc = sp->slc[i];
      if(slc.nu_score > nu_score){
	index = i;
	nu_score = slc.nu_score;
      }
    }
    return index;
  });

const SpillCut kHas1Shw([](const caf::SRSpillProxy* sp) {
    return sp->slc[kBestSliceID(sp)].reco.nshw == 1;
  });


void NuEn(const std::string inputName = "official_MC2021Bv1_prodoverlay_corsika_cosmics_proton_genie_nu_spill_gsimple-configh-v1_tpc_reco2_flat_caf_sbnd")
{
  SpectrumLoader loader(inputName);

  const Binning binsNuEn = Binning::Simple(20, 0, 5);

  Spectrum sNuEn("True Interaction Energy (GeV)", binsNuEn, loader, kTrueNuEn, kNoSpillCut);
  Spectrum sNuEnSig("True Interaction Energy (GeV)", binsNuEn, loader, kTrueNuEn, kTruthDef);

  Spectrum sNuEnHasNuSlc("True Interaction Energy (GeV)", binsNuEn, loader, kTrueNuEn, kHasNuSlc);
  Spectrum sNuEnHas1Shw("True Interaction Energy (GeV)", binsNuEn, loader, kTrueNuEn, kHas1Shw);

  loader.Go();


  TCanvas* c1 = new TCanvas("c1", "c1");
  TH1* hNuEn = sNuEn.ToTH1(6.6e20);
  TH1* hNuEnSig = sNuEnSig.ToTH1(6.6e20);
  hNuEn->Draw("hist");
  hNuEnSig->SetLineColor(kRed);
  hNuEnSig->SetFillColor(kRed);
  hNuEnSig->SetFillStyle(3244);
  hNuEnSig->Draw("histsame");
  TLegend *l1 = new TLegend(.6,.7,.85,.8);
  l1->AddEntry(hNuEn, "All Spills","l");
  l1->AddEntry(hNuEnSig, "Signal (CC#nu_{e} FV)");
  l1->Draw();
  //  c1->Print("nuEn.png");

  TCanvas* c2 = new TCanvas("c2", "c2");
  TH1* hNuEnHasNuSlc = sNuEnHasNuSlc.ToTH1(6.6e20);
  TH1* hNuEnHas1Shw = sNuEnHas1Shw.ToTH1(6.6e20);
  hNuEn->Draw("hist");
  hNuEnHasNuSlc->SetLineColor(kBlue+1);
  hNuEnHasNuSlc->Draw("histsame");
  hNuEnHas1Shw->SetLineColor(kOrange);
  hNuEnHas1Shw->Draw("histsame");
  TLegend *l2 = new TLegend(.55,.7,.85,.8);
  l2->AddEntry(hNuEn, "All Spills","l");
  l2->AddEntry(hNuEnHasNuSlc, "Has a neutrino slice");
  l2->AddEntry(hNuEnHas1Shw, "Best slice has 1 reco shower");
  l2->Draw();

}
