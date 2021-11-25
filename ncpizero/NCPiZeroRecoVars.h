#include "TVector3.h"

const SpillVar kNTracks([](const caf::SRSpillProxy* sp) -> unsigned {
    if(!kHasNuSlc(sp))
      return 0;
    
    return sp->slc[kBestSliceID(sp)].reco.ntrk;
  });

const SpillVar kNShowers([](const caf::SRSpillProxy* sp) -> unsigned {
    if(!kHasNuSlc(sp))
      return 0;

    return sp->slc[kBestSliceID(sp)].reco.nshw;
  });

const SpillVar kLongestTrackLength([](const caf::SRSpillProxy* sp) -> double {
    if(!kHasNuSlc(sp))
      return 0;

    double trklength(-999999);
    
    for(auto const &trk : sp->slc[kBestSliceID(sp)].reco.trk)
      {
	if(trk.len > trklength) trklength = trk.len;
      }

    return trklength;
  });

const SpillVar kLeadingShowerEnergy([](const caf::SRSpillProxy* sp) -> double {
    if(!kHasNuSlc(sp))
      return 0;

    const unsigned lead_index = kLeadingShwID(sp);
    if(lead_index == 999999)
      return -999999;

    else return sp->slc[kBestSliceID(sp)].reco.shw[lead_index].bestplane_energy;
  });

const SpillVar kLeadingShowerdEdx([](const caf::SRSpillProxy* sp) -> double {
    if(!kHasNuSlc(sp))
      return 0;

    const unsigned lead_index = kLeadingShwID(sp);
    if(lead_index == 999999)
      return -999999;

    else return sp->slc[kBestSliceID(sp)].reco.shw[lead_index].bestplane_dEdx;
  });

const SpillVar kLeadingShowerConvGap([](const caf::SRSpillProxy* sp) -> double {
    if(!kHasNuSlc(sp))
      return 0;

    const unsigned lead_index = kLeadingShwID(sp);
    if(lead_index == 999999)
      return -999999;

    else return sp->slc[kBestSliceID(sp)].reco.shw[lead_index].conversion_gap;
  });

const SpillVar kLeadingShowerDensity([](const caf::SRSpillProxy* sp) -> double {
    if(!kHasNuSlc(sp))
      return 0;

    const unsigned lead_index = kLeadingShwID(sp);
    if(lead_index == 999999)
      return -999999;

    else return sp->slc[kBestSliceID(sp)].reco.shw[lead_index].density;
  });

const SpillVar kLeadingShowerLength([](const caf::SRSpillProxy* sp) -> double {
    if(!kHasNuSlc(sp))
      return 0;

    const unsigned lead_index = kLeadingShwID(sp);
    if(lead_index == 999999)
      return -999999;

    else return sp->slc[kBestSliceID(sp)].reco.shw[lead_index].len;
  });

const SpillVar kLeadingShowerOpeningAngle([](const caf::SRSpillProxy* sp) -> double {
    if(!kHasNuSlc(sp))
      return 0;

    const unsigned lead_index = kLeadingShwID(sp);
    if(lead_index == 999999)
      return -999999;

    else return TMath::RadToDeg() * sp->slc[kBestSliceID(sp)].reco.shw[lead_index].open_angle;
  });

const SpillVar kLeadingShowerCosmicDist([](const caf::SRSpillProxy* sp) -> double {
    if(!kHasNuSlc(sp))
      return 0;

    const unsigned lead_index = kLeadingShwID(sp);
    if(lead_index == 999999)
      return -999999;

    else return sp->slc[kBestSliceID(sp)].reco.shw[lead_index].cosmicDist;
  });

const SpillVar kSubLeadingShowerEnergy([](const caf::SRSpillProxy* sp) -> double {
    if(!kHasNuSlc(sp))
      return 0;

    const unsigned lead_index = kSubLeadingShwID(sp);
    if(lead_index == 999999)
      return -999999;

    else return sp->slc[kBestSliceID(sp)].reco.shw[lead_index].bestplane_energy;
  });

const SpillVar kSubLeadingShowerdEdx([](const caf::SRSpillProxy* sp) -> double {
    if(!kHasNuSlc(sp))
      return 0;

    const unsigned lead_index = kSubLeadingShwID(sp);
    if(lead_index == 999999)
      return -999999;

    else return sp->slc[kBestSliceID(sp)].reco.shw[lead_index].bestplane_dEdx;
  });

const SpillVar kSubLeadingShowerConvGap([](const caf::SRSpillProxy* sp) -> double {
    if(!kHasNuSlc(sp))
      return 0;

    const unsigned lead_index = kSubLeadingShwID(sp);
    if(lead_index == 999999)
      return -999999;

    else return sp->slc[kBestSliceID(sp)].reco.shw[lead_index].conversion_gap;
  });

const SpillVar kSubLeadingShowerDensity([](const caf::SRSpillProxy* sp) -> double {
    if(!kHasNuSlc(sp))
      return 0;

    const unsigned lead_index = kSubLeadingShwID(sp);
    if(lead_index == 999999)
      return -999999;

    else return sp->slc[kBestSliceID(sp)].reco.shw[lead_index].density;
  });

const SpillVar kSubLeadingShowerLength([](const caf::SRSpillProxy* sp) -> double {
    if(!kHasNuSlc(sp))
      return 0;

    const unsigned lead_index = kSubLeadingShwID(sp);
    if(lead_index == 999999)
      return -999999;

    else return sp->slc[kBestSliceID(sp)].reco.shw[lead_index].len;
  });

const SpillVar kSubLeadingShowerOpeningAngle([](const caf::SRSpillProxy* sp) -> double {
    if(!kHasNuSlc(sp))
      return 0;

    const unsigned lead_index = kSubLeadingShwID(sp);
    if(lead_index == 999999)
      return -999999;

    else return TMath::RadToDeg() * sp->slc[kBestSliceID(sp)].reco.shw[lead_index].open_angle;
  });

const SpillVar kSubLeadingShowerCosmicDist([](const caf::SRSpillProxy* sp) -> double {
    if(!kHasNuSlc(sp))
      return 0;

    const unsigned lead_index = kSubLeadingShwID(sp);
    if(lead_index == 999999)
      return -999999;

    else return sp->slc[kBestSliceID(sp)].reco.shw[lead_index].cosmicDist;
  });

const SpillVar kInvariantMass([](const caf::SRSpillProxy* sp) -> double {
    if(!kHasNuSlc(sp))
      return 0;

    const unsigned lead_index = kLeadingShwID(sp);
    if(lead_index == 999999)
      return -999999;
    const unsigned sublead_index = kSubLeadingShwID(sp);
    if(sublead_index == 999999)
      return -999999;
    
    auto const& lead = sp->slc[kBestSliceID(sp)].reco.shw[lead_index];
    auto const& sublead = sp->slc[kBestSliceID(sp)].reco.shw[sublead_index];

    TVector3 leadDir(lead.dir.x, lead.dir.y, lead.dir.z);
    TVector3 subleadDir(sublead.dir.x, sublead.dir.y, sublead.dir.z);

    const double cosine = leadDir.Dot(subleadDir) / (leadDir.Mag() * subleadDir.Mag());

    return sqrt(2 * (1e+6) * lead.bestplane_energy * sublead.bestplane_energy * (1. - cosine));
  });

const SpillVar kRazzleNElectrons([](const caf::SRSpillProxy *sp) -> unsigned {
    if(sp->nslc == 0)
      return false;

    unsigned nelectrons(0);

    for(auto const& shw : sp->slc[kBestSliceID(sp)].reco.shw)
      {
        if(shw.razzle.pdg == 11) ++nelectrons;
      }

    return nelectrons;
  });

const SpillVar kRazzleNPhotons([](const caf::SRSpillProxy *sp) -> unsigned {
    if(sp->nslc == 0)
      return false;

    unsigned nphotons(0);

    for(auto const& shw : sp->slc[kBestSliceID(sp)].reco.shw)
      {
        if(shw.razzle.pdg == 22) ++nphotons;
      }

    return nphotons;
  });

const SpillVar kDazzleNProtons([](const caf::SRSpillProxy *sp) -> unsigned {
    if(sp->nslc == 0)
      return false;

    unsigned nprotons(0);

    for(auto const& trk : sp->slc[kBestSliceID(sp)].reco.trk)
      {
        if(trk.dazzle.pdg == 2212) ++nprotons;
      }

    return nprotons;
  });

const SpillVar kDazzleNPions([](const caf::SRSpillProxy *sp) -> unsigned {
    if(sp->nslc == 0)
      return false;

    unsigned npions(0);

    for(auto const& trk : sp->slc[kBestSliceID(sp)].reco.trk)
      {
        if(trk.dazzle.pdg == 211) ++npions;
      }

    return npions;
  });

const SpillVar kDazzleNMuons([](const caf::SRSpillProxy *sp) -> unsigned {
    if(sp->nslc == 0)
      return false;

    unsigned nmuons(0);

    for(auto const& trk : sp->slc[kBestSliceID(sp)].reco.trk)
      {
        if(trk.dazzle.pdg == 13) ++nmuons;
      }

    return nmuons;
  });

const Binning binsCount = Binning::Simple(10,0,10);
const Binning binsTrkLength = Binning::Simple(25,0,500);
const Binning binsShwEnergy = Binning::Simple(25,0,1);
const Binning binsShwdEdx = Binning::Simple(30,0,6);
const Binning binsShwConvGap = Binning::Simple(25,0,50);
const Binning binsShwDensity = Binning::Simple(25,0,40);
const Binning binsShwLength = Binning::Simple(30,0,150);
const Binning binsShwOpeningAngle = Binning::Simple(30,0,180);
const Binning binsShwCosmicDist = Binning::Simple(25,0,200);
const Binning binsInvMass = Binning::Simple(30,0,300);

std::vector<Plot> event_plots = {
  {"N Protons", kNProton, binsCount, ";Number of protons", "nprotons"},
  {"N Tracks", kNTracks, binsCount, ";Number of tracks", "ntracks"},
  {"N Showers", kNShowers, binsCount, ";Number of showers", "nshowers"},
  {"Longest Track Length", kLongestTrackLength, binsTrkLength, ";Longest track length (cm);", "longesttrklength"},
  {"Leading Shower Energy", kLeadingShowerEnergy, binsShwEnergy, ";Leading shower energy (GeV);", "leadingshwenergy"},
  {"Leading Shower dE/dx", kLeadingShowerdEdx, binsShwdEdx, ";Leading shower dE/dx (MeV/cm);", "leadingshwdEdx"},
  {"Leading Shower ConvGap", kLeadingShowerConvGap, binsShwConvGap, ";Leading shower conversion gap (cm);", "leadingshwconvgap"},
  {"Leading Shower Density", kLeadingShowerDensity, binsShwDensity, ";Leading shower density (MeV/cm);", "leadingshwdensity"},
  {"Leading Shower Length", kLeadingShowerLength, binsShwLength, ";Leading shower length (cm);", "leadingshwlength"},
  {"Leading Shower Opening Angle", kLeadingShowerOpeningAngle, binsShwOpeningAngle, ";Leading shower openingangle (#circ);", "leadingshwopeningangle"},
  {"Leading Shower Cosmic Distance", kLeadingShowerCosmicDist, binsShwCosmicDist, ";Leading shower cosmic distance (cm);", "leadingshwcosmicdist"},
  {"Sub-Leading Shower Energy", kSubLeadingShowerEnergy, binsShwEnergy, ";Sub-leading shower energy (GeV);", "subleadingshwenergy"},
  {"Sub-Leading Shower dE/dx", kSubLeadingShowerdEdx, binsShwdEdx, ";Sub-leading shower dE/dx (MeV/cm);", "subleadingshwdEdx"},
  {"Sub-Leading Shower ConvGap", kSubLeadingShowerConvGap, binsShwConvGap, ";Sub-leading shower conversion gap (cm);", "subleadingshwconvgap"},
  {"Sub-Leading Shower Density", kSubLeadingShowerDensity, binsShwDensity, ";Sub-leading shower density (MeV/cm);", "subleadingshwdensity"},
  {"Sub-Leading Shower Length", kSubLeadingShowerLength, binsShwLength, ";Sub-leading shower length (cm);", "subleadingshwlength"},
  {"Sub-Leading Shower Opening Angle", kSubLeadingShowerOpeningAngle, binsShwOpeningAngle, ";Sub-leading shower openingangle (#circ);", "subleadingshwopeningangle"},
  {"Sub-Leading Shower Cosmic Distance", kSubLeadingShowerCosmicDist, binsShwCosmicDist, ";Sub-leading shower cosmic distance (cm);", "subleadingshwcosmicdist"},
  {"Diphoton Invariant Mass", kInvariantMass, binsInvMass, ";W (MeV/c^{2});", "invariantmass"},
};
