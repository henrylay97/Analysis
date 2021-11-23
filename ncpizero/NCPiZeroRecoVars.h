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

const Binning binsCount = Binning::Simple(10,0,10);
const Binning binsTrkLength = Binning::Simple(25,0,500);
const Binning binsShwEnergy = Binning::Simple(25,0,1);
const Binning binsShwdEdx = Binning::Simple(30,0,6);
const Binning binsShwConvGap = Binning::Simple(25,0,50);
const Binning binsShwDensity = Binning::Simple(25,0,100);
const Binning binsShwLength = Binning::Simple(25,0,100);
const Binning binsShwOpeningAngle = Binning::Simple(30,0,180);
const Binning binsShwCosmicDist = Binning::Simple(25,0,50);

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
};
