const SpillCut kPileUp([](const caf::SRSpillProxy* sp) {
    return sp->mc.nnu > 1;
  });

const SpillCut kNC([](const caf::SRSpillProxy* sp) {
    return !kPileUp(sp) && sp->mc.nu[0].isnc;
  });

const SpillCut kCC([](const caf::SRSpillProxy* sp) {
    return !kPileUp(sp) && sp->mc.nu[0].iscc;
  });

const SpillCut kCCNuMu([](const caf::SRSpillProxy* sp) {
    return kCC(sp) && std::abs(sp->mc.nu[0].pdg) == 14;
  });

const SpillCut kCCNuE([](const caf::SRSpillProxy* sp) {
    return kCC(sp) && std::abs(sp->mc.nu[0].pdg) == 12;
  });
    
const SpillVar kNPiPlus([](const caf::SRSpillProxy* sp) -> unsigned {
    if(kPileUp(sp)) return 999999;

    unsigned int npiplus = 0;

    for(auto const& prim : sp->mc.nu[0].prim)
      if(prim.pdg == 211) npiplus++;

    return npiplus;
  });

const SpillVar kNPiMinus([](const caf::SRSpillProxy* sp) -> unsigned {
    if(kPileUp(sp)) return 999999;

    unsigned int npiminus = 0;

    for(auto const& prim : sp->mc.nu[0].prim)
      if(prim.pdg == -211) npiminus++;

    return npiminus;
  });

const SpillVar kNPiZero([](const caf::SRSpillProxy* sp) -> unsigned {
    if(kPileUp(sp)) return 999999;

    unsigned int npizero = 0;

    for(auto const& prim : sp->mc.nu[0].prim)
      if(prim.pdg == 111) npizero++;

    return npizero;
  });

const SpillVar kNProton([](const caf::SRSpillProxy* sp) -> unsigned {
    if(kPileUp(sp)) return 999999;

    unsigned int nproton = 0;

    for(auto const& prim : sp->mc.nu[0].prim)
      if(prim.pdg == 2212) nproton++;

    return nproton;
  });

const SpillCut kNCPiZero([](const caf::SRSpillProxy* sp) {
    if(!kNC(sp)) return false;

    return kNPiPlus(sp) == 0 && kNPiMinus(sp) == 0 && kNPiZero(sp) == 1;
  });

const SpillCut kNCPiZeroProton([](const caf::SRSpillProxy* sp) {
    return kNCPiZero(sp) && kNProton(sp) == 1;
  });

const SpillCut kNCPiZeroNoProton([](const caf::SRSpillProxy* sp) {
    return kNCPiZero(sp) && kNProton(sp) == 0;
  });


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

const SpillCut kOtherBack = !kNCPiZero && !kCCNuMu && !kCCNuE && !kNC && !kPileUp;

std::vector<TrueDef> ncpizero_categories = {
  {"Signal (NC #pi^{0})", kNCPiZero, kViolet+2, "Signal"},
  {"Background", !kNCPiZero, kRed+3, "Background"},
};

std::vector<TrueDef> ncpizero_split_signal_categories = {
  {"Signal (NC #pi^{0} 0p)", kNCPiZeroNoProton, kViolet+2, "Signal0p"},
  {"Signal (NC #pi^{0} 1p)", kNCPiZeroProton, kOrange+2, "Signal1p"},
  {"Signal (NC #pi^{0} np)", kNCPiZero && !kNCPiZeroNoProton && !kNCPiZeroProton, kAzure+10, "Signalnp"},
  {"Background", !kNCPiZero, kRed+3, "Background"},
};

std::vector<TrueDef> ncpizero_detailed_categories = {
  {"Signal (NC #pi^{0} 0p)", kNCPiZeroNoProton, kViolet+2, "Signal0p"},
  {"Signal (NC #pi^{0} 1p)", kNCPiZeroProton, kOrange+2, "Signal1p"},
  {"Signal (NC #pi^{0} np)", kNCPiZero && !kNCPiZeroNoProton && !kNCPiZeroProton, kAzure+10, "Signalnp"},
  {"Other NC", kNC && !kNCPiZero, kPink-9, "NC"},
  {"CC #nu_{#mu}", kCCNuMu, kMagenta+2, "CCNuMu"},
  {"CC #nu_{e}", kCCNuE, kCyan+2, "CCNuE"},
  {"PileUp", kPileUp, kTeal+8, "PileUp"},
  {"Other", kOtherBack, kBlack, "Other"},
  {"Background", !kNCPiZero, kBlack, "Background"},
};

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
