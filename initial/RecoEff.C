#include "sbnana/CAFAna/Core/Binning.h"
#include "sbnana/CAFAna/Core/Spectrum.h"
#include "sbnana/CAFAna/Core/SpectrumLoader.h"

using namespace ana;

#include "Binnings.C"
#include "sbnana/CAFAna/StandardRecord/Proxy/SRProxy.h"

#include "TCanvas.h"
#include "TH1.h"
#include "TLegend.h"
#include "TEfficiency.h"

int kPDG;
double kScaledPOT;

float VectorMag(const caf::Proxy<caf::SRVector3D> &vec)
{
  return std::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

void PlotRecoEff(const TString name, const Spectrum &sTrue, const Spectrum &sReco);

const SpillMultiVar kAllTrueEnergy([](const caf::SRSpillProxy* sp) -> std::vector<double> {
    std::vector<double> en;
    for(auto const& particle : sp->true_particles) {
      if(particle.pdg != kPDG || particle.interaction_id == -1 || 
	 particle.start_process != 0) continue;
      en.push_back(particle.genE);
    }
    return en;
  });

const SpillMultiVar kRecoObjTrueEnergy([](const caf::SRSpillProxy* sp) -> std::vector<double> {
    std::vector<double> en;
    std::set<int> used;

    for(auto const& slc : sp->slc) {
      if(slc.is_clear_cosmic) continue;
      if(kPDG == 22 || std::abs(kPDG) == 11) {
	for(auto const& shw : slc.reco.shw) {
	  if(!shw.pfp.parent_is_primary) continue;
	  auto const& particle = shw.truth.p;
	  if(particle.pdg != kPDG || particle.interaction_id == -1 || 
	     particle.start_process != 0) continue;
	  if(used.count(particle.G4ID)) continue;
	  used.insert(particle.G4ID);
	  en.push_back(particle.genE);
	}
      }
      else {
	for(auto const& trk : slc.reco.trk) {
	  if(!trk.pfp.parent_is_primary) continue;
	  auto const& particle = trk.truth.p;
	  if(particle.pdg != kPDG || particle.interaction_id == -1 || 
	     particle.start_process != 0) continue;
	  if(used.count(particle.G4ID)) continue;
	  used.insert(particle.G4ID);
	  en.push_back(particle.genE);
	}
      }
    }
    return en;
  });

const SpillMultiVar kAllTrueMomentum([](const caf::SRSpillProxy* sp) -> std::vector<double> {
    std::vector<double> mom;
    for(auto const& particle : sp->true_particles) {
      if(particle.pdg != kPDG || particle.interaction_id == -1 || 
	 particle.start_process != 0) continue;
      mom.push_back(VectorMag(particle.genp));
    }
    return mom;
  });

const SpillMultiVar kRecoObjTrueMomentum([](const caf::SRSpillProxy* sp) -> std::vector<double> {
    std::vector<double> mom;
    std::set<int> used;
    for(auto const& slc : sp->slc) {
      if(slc.is_clear_cosmic) continue;
      if(kPDG == 22 || std::abs(kPDG) == 11) {
	for(auto const& shw : slc.reco.shw) {
	  if(!shw.pfp.parent_is_primary) continue;
	  auto const& particle = shw.truth.p;
	  if(particle.pdg != kPDG || particle.interaction_id == -1 || 
	     particle.start_process != 0) continue;
	  mom.push_back(VectorMag(particle.genp));
	  if(used.count(particle.G4ID)) continue;
	  used.insert(particle.G4ID);
	}
      }
      else {
	for(auto const& trk : slc.reco.trk) {
	  if(!trk.pfp.parent_is_primary) continue;
	  auto const& particle = trk.truth.p;
	  if(particle.pdg != kPDG || particle.interaction_id == -1 || 
	     particle.start_process != 0) continue;
	  if(used.count(particle.G4ID)) continue;
	  used.insert(particle.G4ID);
	  
	  mom.push_back(VectorMag(particle.genp));
	}
      }
    }
    return mom;
  });

const SpillMultiVar kAllTrueThetaXY([](const caf::SRSpillProxy* sp) -> std::vector<double> {
    std::vector<double> theta_xy;
    for(auto const& particle : sp->true_particles) {
      if(particle.pdg != kPDG || particle.interaction_id == -1 || 
	 particle.start_process != 0) continue;
      const float theta = TMath::RadToDeg() * TMath::ATan(particle.genp.x/particle.genp.y);
      theta_xy.push_back(theta);
    }
    return theta_xy;
  });

const SpillMultiVar kRecoObjTrueThetaXY([](const caf::SRSpillProxy* sp) -> std::vector<double> {
    std::vector<double> theta_xy;
    std::set<int> used;

    for(auto const& slc : sp->slc) {
      if(slc.is_clear_cosmic) continue;
      if(kPDG == 22 || std::abs(kPDG) == 11) {
	for(auto const& shw : slc.reco.shw) {
	  if(!shw.pfp.parent_is_primary) continue;
	  auto const& particle = shw.truth.p;
	  if(particle.pdg != kPDG || particle.interaction_id == -1 || 
	     particle.start_process != 0) continue;
	  if(used.count(particle.G4ID)) continue;
	  used.insert(particle.G4ID);
	  const float theta = TMath::RadToDeg() * TMath::ATan(particle.genp.x/particle.genp.y);
	  theta_xy.push_back(theta);
	}
      }
      else {
	for(auto const& trk : slc.reco.trk) {
	  if(!trk.pfp.parent_is_primary) continue;
	  auto const& particle = trk.truth.p;
	  if(particle.pdg != kPDG || particle.interaction_id == -1 || 
	     particle.start_process != 0) continue;
	  if(used.count(particle.G4ID)) continue;
	  used.insert(particle.G4ID);
	  const float theta = TMath::RadToDeg() * TMath::ATan(particle.genp.x/particle.genp.y);
	  theta_xy.push_back(theta);
	}
      }
    }
    return theta_xy;
  });

const SpillMultiVar kAllTrueThetaYZ([](const caf::SRSpillProxy* sp) -> std::vector<double> {
    std::vector<double> theta_yz;
    for(auto const& particle : sp->true_particles) {
      if(particle.pdg != kPDG || particle.interaction_id == -1 || 
	 particle.start_process != 0) continue;
      const float theta = TMath::RadToDeg() * TMath::ATan(particle.genp.y/particle.genp.z);
      theta_yz.push_back(theta);
    }
    return theta_yz;
  });

const SpillMultiVar kRecoObjTrueThetaYZ([](const caf::SRSpillProxy* sp) -> std::vector<double> {
    std::vector<double> theta_yz;
    std::set<int> used;

    for(auto const& slc : sp->slc) {
      if(slc.is_clear_cosmic) continue;
      if(kPDG == 22 || std::abs(kPDG) == 11) {
	for(auto const& shw : slc.reco.shw) {
	  if(!shw.pfp.parent_is_primary) continue;
	  auto const& particle = shw.truth.p;
	  if(particle.pdg != kPDG || particle.interaction_id == -1 || 
	     particle.start_process != 0) continue;
	  if(used.count(particle.G4ID)) continue;
	  used.insert(particle.G4ID);
	  const float theta = TMath::RadToDeg() * TMath::ATan(particle.genp.y/particle.genp.z);
	  theta_yz.push_back(theta);
	}
      }
      else {
	for(auto const& trk : slc.reco.trk) {
	  if(!trk.pfp.parent_is_primary) continue;
	  auto const& particle = trk.truth.p;
	  if(particle.pdg != kPDG || particle.interaction_id == -1 || 
	     particle.start_process != 0) continue;
	  if(used.count(particle.G4ID)) continue;
	  used.insert(particle.G4ID);
	  const float theta = TMath::RadToDeg() * TMath::ATan(particle.genp.y/particle.genp.z);
	  theta_yz.push_back(theta);
	}
      }
    }
    return theta_yz;
  });

const SpillMultiVar kAllTrueThetaXZ([](const caf::SRSpillProxy* sp) -> std::vector<double> {
    std::vector<double> theta_xz;
    for(auto const& particle : sp->true_particles) {
      if(particle.pdg != kPDG || particle.interaction_id == -1 || 
	 particle.start_process != 0) continue;
      const float theta = TMath::RadToDeg() * TMath::ATan(particle.genp.x/particle.genp.z);
      theta_xz.push_back(theta);
    }
    return theta_xz;
  });

const SpillMultiVar kRecoObjTrueThetaXZ([](const caf::SRSpillProxy* sp) -> std::vector<double> {
    std::vector<double> theta_xz;
    std::set<int> used;

    for(auto const& slc : sp->slc) {
      if(slc.is_clear_cosmic) continue;
      if(kPDG == 22 || std::abs(kPDG) == 11) {
	for(auto const& shw : slc.reco.shw) {
	  if(!shw.pfp.parent_is_primary) continue;
	  auto const& particle = shw.truth.p;
	  if(particle.pdg != kPDG || particle.interaction_id == -1 || 
	     particle.start_process != 0) continue;
	  if(used.count(particle.G4ID)) continue;
	  used.insert(particle.G4ID);
	  const float theta = TMath::RadToDeg() * TMath::ATan(particle.genp.x/particle.genp.z);
	  theta_xz.push_back(theta);
	}
      }
      else {
	for(auto const& trk : slc.reco.trk) {
	  if(!trk.pfp.parent_is_primary) continue;
	  auto const& particle = trk.truth.p;
	  if(particle.pdg != kPDG || particle.interaction_id == -1 || 
	     particle.start_process != 0) continue;
	  if(used.count(particle.G4ID)) continue;
	  used.insert(particle.G4ID);
	  const float theta = TMath::RadToDeg() * TMath::ATan(particle.genp.x/particle.genp.z);
	  theta_xz.push_back(theta);
	}
      }
    }
    return theta_xz;
  });


void RunRecoEff(const std::string sample, const int pdg, const double pot=6.6e20)
{
  kPDG = pdg;
  kScaledPOT = pot;

  Binning binsTrueEn = Binning::Simple(1,0,1);
  Binning binsTrueMom = Binning::Simple(1,0,1);
  Binning binsAngleHalf = Binning::Simple(30,-90,90);

  switch (kPDG) {
  case 11:
    binsTrueEn = binsElecTrueEn;
    binsTrueMom = binsElecTrueMom;
    break;
  case 13:
    binsTrueEn = binsMuonTrueEn;
    binsTrueMom = binsMuonTrueMom;
    break;
  case 2212:
    binsTrueEn = binsProtonTrueEn;    
    binsTrueMom = binsProtonTrueMom;    
    break;
  }

  SpectrumLoader loader(sample);

  Spectrum sAllTrueEn("True Energy (GeV)", binsTrueEn, loader, kAllTrueEnergy, kNoSpillCut);
  Spectrum sRecoTrueEn("", binsTrueEn, loader, kRecoObjTrueEnergy, kNoSpillCut);

  Spectrum sAllTrueMom("True Momentum (GeV/c)", binsTrueMom, loader, kAllTrueMomentum, kNoSpillCut);
  Spectrum sRecoTrueMom("", binsTrueMom, loader, kRecoObjTrueMomentum, kNoSpillCut);
  Spectrum sAllTrueThetaXY("#theta_{xy}(#circ)", binsAngleHalf, loader, kAllTrueThetaXY, kNoSpillCut);
  Spectrum sRecoTrueThetaXY("", binsAngleHalf, loader, kRecoObjTrueThetaXY, kNoSpillCut);
  Spectrum sAllTrueThetaYZ("#theta_{yz}(#circ)", binsAngleHalf, loader, kAllTrueThetaYZ, kNoSpillCut);
  Spectrum sRecoTrueThetaYZ("", binsAngleHalf, loader, kRecoObjTrueThetaYZ, kNoSpillCut);
  Spectrum sAllTrueThetaXZ("#theta_{xz}(#circ)", binsAngleHalf, loader, kAllTrueThetaXZ, kNoSpillCut);
  Spectrum sRecoTrueThetaXZ("", binsAngleHalf, loader, kRecoObjTrueThetaXZ, kNoSpillCut);

  loader.Go();

  PlotRecoEff("energy", sAllTrueEn, sRecoTrueEn);
  PlotRecoEff("momentum", sAllTrueMom, sRecoTrueMom);
  PlotRecoEff("theta_xy", sAllTrueThetaXY, sRecoTrueThetaXY);
  PlotRecoEff("theta_yz", sAllTrueThetaYZ, sRecoTrueThetaYZ);
  PlotRecoEff("theta_xz", sAllTrueThetaXZ, sRecoTrueThetaXZ);
}



void PlotRecoEff(const TString name, const Spectrum &sTrue, const Spectrum &sReco)
{
  TString particleName;
  switch (kPDG) {
  case 11:
    particleName = "electron";
    break;
  case 13:
    particleName = "muon";
    break;
  case 2212:
    particleName = "proton";
    break;
  }

  TCanvas* c1 = new TCanvas("c1_" + name, "c1_" + name);
  TH1* hTrue = sTrue.ToTH1(kScaledPOT);
  TH1* hReco = sReco.ToTH1(kScaledPOT);
  TEfficiency *eff = new TEfficiency(*hReco, *hTrue);
  hTrue->Scale(1.f/hTrue->GetMaximum());
  hTrue->GetYaxis()->SetTitle("Reconstruction Efficiency");
  hTrue->SetFillStyle(3244);
  hTrue->SetFillColor(kGray);
  eff->SetMarkerColor(kRed+2);
  eff->SetLineColor(kRed+2);
  eff->SetLineWidth(3);
  hTrue->Draw("hist");
  eff->Draw("same");
  c1->Print(particleName + "_reconstruction_efficiency_" + name + ".png");
}

  
