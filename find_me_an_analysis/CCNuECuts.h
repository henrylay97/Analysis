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

    return shw.bestplane_dEdx < 3;
  });

const SpillCut kLargestShwCnvGap([](const caf::SRSpillProxy *sp) {
    if(!kHasAtLeastOneShw(sp))
      return false;

    auto const &slc = sp->slc[kBestSliceID(sp)];
    auto const &shw = slc.reco.shw[kLargestShwID(sp)];

    return shw.conversion_gap < 3;
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


const SpillCut kOtherBack = !kCCNuE && !kCCNuMu && !kPileUp && !kNC;

std::vector<TrueDef> ccnue_sig_back_categories = {
  {"Signal (CC #nu_{e})", kCCNuE, kCyan+2, "Signal"},
  {"CC #nu_{#mu}", kCCNuMu, kMagenta+2, "CCNuMu"},
  {"PileUp", kPileUp, kTeal+8, "PileUp"},
  {"NC", kNC, kOrange+2, "NC"},
  {"Other", kOtherBack, kBlack, "Other"},
  {"Background", !kCCNuE, kBlack, "Background"}
};

std::vector<CutInfo> ccnue_cuts = {
  {"No Selection", kNoSpillCut, "NoCuts"},
  {"Has #nu Slice", kHasNuSlc, "HasNuSlc"},
  {"Reco FV", kRecoFV, "RecoFV"},
  {"Has >=1 Showers", kHasAtLeastOneShw, "HasAtLeastOneShw"},
  {"Largest Shower dEdx <3 MeV/cm", kLargestShwdEdx, "LargestShwdEdx"},
  {"Longest Track Length < 50cm", kLongestTrkLength, "LongestTrkLength"},
  {"Largest Shower Conversion Gap < 3cm", kLargestShwCnvGap, "LargestShwCnvGap"},
};

Selection selection = {
  "CC #nu_{e} Selection",
  ccnue_sig_back_categories,
  ccnue_cuts,
  "ccnue"
};
