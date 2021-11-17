const SpillCut kHasAtLeastOneShw([](const caf::SRSpillProxy *sp) {
    if(sp->nslc == 0)
      return false;

    auto const &slc = sp->slc[kBestSliceID(sp)];
    
    return slc.reco.nshw > 0;  
  });

const SpillCut kLargestShwdEdx([](const caf::SRSpillProxy *sp) {
    if(!kHasAtLeastOneShw(sp))
      return false;

    auto const &slc = sp->slc[kBestSliceID(sp)];
    auto const &shw = slc.reco.shw[kLargestShwID(sp)];

    return shw.bestplane_dEdx > 2;
  });

const SpillCut kLongestTrkLength([](const caf::SRSpillProxy *sp) {
    if(sp->nslc == 0)
      return false;

    auto const &slc = sp->slc[kBestSliceID(sp)];
    if(slc.reco.ntrk == 0) 
      return true;

    auto const &trk = slc.reco.trk[kLongestTrkID(sp)];

    return trk.len < 50;
  });

const SpillCut kHasNoTrk([](const caf::SRSpillProxy *sp) {
    if(sp->nslc == 0)
      return false;

    auto const &slc = sp->slc[kBestSliceID(sp)];
    return slc.reco.ntrk == 0;
  });

const SpillCut kOtherBack = !kNCPiZero && !kCCNuMu && !kCCNuE && !kNC && !kPileUp;

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
  {"Has >=1 Showers", kHasAtLeastOneShw, "HasAtLeastOneShw"},
  {"Largest Shower dEdx >2 MeV/cm", kLargestShwdEdx, "LargestShwdEdx"},
  {"Has No Tracks", kHasNoTrk, "HasNoTrk"},
};
