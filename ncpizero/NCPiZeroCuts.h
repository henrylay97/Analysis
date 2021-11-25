const SpillCut kHasAtLeastOneShw([](const caf::SRSpillProxy *sp) {
    if(sp->nslc == 0)
      return false;

    auto const &slc = sp->slc[kBestSliceID(sp)];
    
    return slc.reco.nshw > 0;  
  });

const SpillCut kHasAtLeastTwoShw([](const caf::SRSpillProxy *sp) {
    if(sp->nslc == 0)
      return false;

    auto const &slc = sp->slc[kBestSliceID(sp)];
    
    return slc.reco.nshw > 1;  
  });

const SpillCut kLeadingShwdEdx([](const caf::SRSpillProxy *sp) {
    if(!kHasAtLeastOneShw(sp))
      return false;

    auto const &slc = sp->slc[kBestSliceID(sp)];
    auto const &shw = slc.reco.shw[kLeadingShwID(sp)];

    return shw.bestplane_dEdx > 2;
  });

const SpillCut kLongestTrkLength([](const caf::SRSpillProxy *sp) {
    if(sp->nslc == 0)
      return false;

    auto const &slc = sp->slc[kBestSliceID(sp)];
    if(slc.reco.ntrk == 0) 
      return true;

    auto const &trk = slc.reco.trk[kLongestTrkID(sp)];

    return trk.len < 100;
  });

const SpillCut kHasNoTrk([](const caf::SRSpillProxy *sp) {
    if(sp->nslc == 0)
      return false;

    auto const &slc = sp->slc[kBestSliceID(sp)];
    return slc.reco.ntrk == 0;
  });

const SpillCut kCosmicDist([](const caf::SRSpillProxy *sp) {
    if(sp->nslc == 0)
      return false;
    
    if(sp->slc[kBestSliceID(sp)].reco.nshw < 2)
      return false;

    double leadDist = kLeadingShowerCosmicDist(sp);
    double subleadDist = kSubLeadingShowerCosmicDist(sp);

    if(leadDist == -5)
      leadDist = 999999;

    if(subleadDist == -5)
      subleadDist = 999999;
    
    return leadDist > 10 && subleadDist > 10;
  });

const SpillCut kLeadingShwLength([](const caf::SRSpillProxy *sp) {
    if(sp->nslc == 0)
      return false;
    
    if(sp->slc[kBestSliceID(sp)].reco.nshw < 1)
      return false;

    return kLeadingShowerLength(sp) > 10;
  });

const SpillCut kInvMassCut([](const caf::SRSpillProxy *sp) {
    if(sp->nslc == 0)
      return false;
    
    if(sp->slc[kBestSliceID(sp)].reco.nshw < 2)
      return false;

    return kInvariantMass(sp) > 40;
  });

const SpillCut kTwoRazzlePhotons([](const caf::SRSpillProxy *sp) {
    return kRazzleNPhotons(sp) == 2;
  });

const SpillCut kNoRazzleElectrons([](const caf::SRSpillProxy *sp) {
    return kRazzleNElectrons(sp) == 0;
  });

const SpillCut kNoDazzleMuons([](const caf::SRSpillProxy *sp) {
    return kDazzleNMuons(sp) == 0;
  });

const SpillCut kNoDazzlePions([](const caf::SRSpillProxy *sp) {
    return kDazzleNPions(sp) == 0;
  });


std::vector<TrueDef> ncpizero_sig_back_categories = {
  {"Signal (NC #pi^{0})", kNCPiZero, kViolet+2, "Signal"},
  {"CC #nu_{#mu}", kCCNuMu, kMagenta+2, "CCNuMu"},
  {"CC #nu_{e}", kCCNuE, kCyan+2, "CCNuE"},
  {"Other NC", kNC && !kNCPiZero, kOrange+2, "NC"}, 
  {"PileUp", kPileUp, kTeal+8, "PileUp"},
  {"Other", kOtherBack, kBlack, "Other"},
  {"Background", !kNCPiZero, kBlack, "Background"},
};

std::vector<CutInfo> ncpizero_cuts = {
  {"No Selection", kNoSpillCut, "NoCuts"},
  {"Has #nu Slice", kHasNuSlc, "HasNuSlc"},
  {"Reco FV", kRecoFV, "RecoFV"},
  {"Has >=2 Showers", kHasAtLeastTwoShw, "HasAtLeastTwoShw"},
  {"Longest track is < 1m", kLongestTrkLength, "LongestTrkLength"},
  {"Showers aren't near cosmics", kCosmicDist, "CosmicDist"},
  {"Leading shower is > 10 cm", kLeadingShwLength, "LeadingShwLength"},
  {"2 shower invariant mass is > 40MeV/c^{2}", kInvMassCut, "InvMass"},
};

std::vector<CutInfo> ncpizero_half_razz_dazz_cuts = {
  {"No Selection", kNoSpillCut, "NoCuts"},
  {"Has #nu Slice", kHasNuSlc, "HasNuSlc"},
  {"Reco FV", kRecoFV, "RecoFV"},
  {"Has >=2 Showers", kHasAtLeastTwoShw, "HasAtLeastTwoShw"},
  {"No Dazzle Muons", kNoDazzleMuons, "NoDazzleMuons"},
  {"No Dazzle Pions", kNoDazzlePions, "NoDazzlePions"},
};

std::vector<CutInfo> ncpizero_razz_dazz_cuts = {
  {"No Selection", kNoSpillCut, "NoCuts"},
  {"Has #nu Slice", kHasNuSlc, "HasNuSlc"},
  {"Reco FV", kRecoFV, "RecoFV"},
  {"Two Razzle Photons", kTwoRazzlePhotons, "TwoRazzlePhotons"},
  {"No Razzle Electrons", kNoRazzleElectrons, "NoRazzleElectrons"},
  {"No Dazzle Muons", kNoDazzleMuons, "NoDazzleMuons"},
  {"No Dazzle Pions", kNoDazzlePions, "NoDazzlePions"},
};

Selection selection = {
  "NC #pi^{0} Selection",
  ncpizero_detailed_categories,
  ncpizero_cuts,
  "ncpizero"
};
