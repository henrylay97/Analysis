// Make a plot with cuts
#include "sbnana/CAFAna/Core/Binning.h"
#include "sbnana/CAFAna/Core/Spectrum.h"
#include "sbnana/CAFAna/Core/SpectrumLoader.h"

using namespace ana;

#include "sbnana/CAFAna/StandardRecord/Proxy/SRProxy.h"
#include "sbnana/SBNAna/Vars/NueVars.h"

#include "TCanvas.h"
#include "TH1.h"
#include "TLegend.h"

void PlotShowerVars(const std::string inputName = "official_MC2021Bv1_prodoverlay_corsika_cosmics_proton_genie_nu_spill_gsimple-configh-v1_tpc_reco2_flat_caf_sbnd")
{
  SpectrumLoader loader(inputName);

  const Binning binsShwEn = Binning::Simple(20, 0, 0.4);
  const Binning binsShwdEdx = Binning::Simple(20, 0, 5);
  const Binning binsShwCnvGap = Binning::Simple(20, 0, 25);
  const Binning binsShwOpenAng = Binning::Simple(20, 0, 90);
  const Binning binsShwPDG = Binning::Simple(5, 9.5, 14.5);
  
  const HistAxis axLargestShwEn("Largest Shower Energy (GeV)", binsShwEn, kRecoShower_BestEnergy);
  const HistAxis axLargestShwdEdx("Largest Shower dEdx (MeV/cm)", binsShwdEdx, kRecoShower_BestdEdx);
  const HistAxis axLargestShwCnvGap("Largest Shower Conversion Gap (cm)", binsShwCnvGap, kRecoShower_ConversionGap);
  const HistAxis axLargestShwOpenAng("Largest Shower Opening Angle (#circ)", binsShwOpenAng, kRecoShower_OpenAngle);
  const HistAxis axLargestShwTruePDG("Largest Shower True PDG", binsShwPDG, kRecoShower_TruePdg);

  Spectrum sLargestShwEn(loader, axLargestShwEn, kNoCut);
  Spectrum sLargestShwdEdx(loader, axLargestShwdEdx, kNoCut);
  Spectrum sLargestShwCnvGap(loader, axLargestShwCnvGap, kNoCut);
  Spectrum sLargestShwOpenAng(loader, axLargestShwOpenAng, kNoCut);
  Spectrum sLargestShwTruePDG(loader, axLargestShwTruePDG, kNoCut);

  loader.Go();

  TCanvas* cLargestShwEn = new TCanvas("cLargestShwEn", "cLargestShwEn");
  TH1* hLargestShwEn = sLargestShwEn.ToTH1(6.6e20);
  hLargestShwEn->Draw("hist");
  //  cLargestShwEn->Print("largestShwEn.png");

  TCanvas* cLargestShwdEdx = new TCanvas("cLargestShwdEdx", "cLargestShwdEdx");
  TH1* hLargestShwdEdx = sLargestShwdEdx.ToTH1(6.6e20);
  hLargestShwdEdx->Draw("hist");
  //  cLargestShwdEdx->Print("largestShwdEdx.png");

  TCanvas* cLargestShwCnvGap = new TCanvas("cLargestShwCnvGap", "cLargestShwCnvGap");
  TH1* hLargestShwCnvGap = sLargestShwCnvGap.ToTH1(6.6e20);
  hLargestShwCnvGap->Draw("hist");
  //  cLargestShwCnvGap->Print("largestShwCnvGap.png");

  TCanvas* cLargestShwOpenAng = new TCanvas("cLargestShwOpenAng", "cLargestShwOpenAng");
  TH1* hLargestShwOpenAng = sLargestShwOpenAng.ToTH1(6.6e20);
  hLargestShwOpenAng->Draw("hist");
  //  cLargestShwOpenAng->Print("largestShwOpenAng.png");

  TCanvas* cLargestShwTruePDG = new TCanvas("cLargestShwTruePDG", "cLargestShwTruePDG");
  TH1* hLargestShwTruePDG = sLargestShwTruePDG.ToTH1(6.6e20);
  hLargestShwTruePDG->Draw("hist");
  //  cLargestShwTruePDG->Print("largestShwTruePDG.png");
}
