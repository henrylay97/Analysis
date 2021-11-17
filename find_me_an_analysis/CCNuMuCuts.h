const SpillCut kHasAtLeastOneTrk([](const caf::SRSpillProxy *sp) {
    if(sp->nslc == 0)
      return false;

    auto const &slc = sp->slc[kBestSliceID(sp)];
    
    return slc.reco.ntrk > 0;  
  });

const SpillCut kLongestTrkLength([](const caf::SRSpillProxy *sp) {
    if(!kHasAtLeastOneTrk(sp))
      return false;

    auto const &slc = sp->slc[kBestSliceID(sp)];
    auto const &trk = slc.reco.trk[kLongestTrkID(sp)];

    return trk.len > 50;
  });

const SpillCut kOtherTrkLength([](const caf::SRSpillProxy *sp) {
    if(sp->nslc == 0)
      return false;

    auto const &slc = sp->slc[kBestSliceID(sp)];

    for(unsigned i = 0; i < slc.reco.ntrk; ++i) {
      if(i == kLongestTrkID(sp))
	continue;

      auto const& trk = slc.reco.trk[i];
      if(trk.len > 100)
	return false;
    }

    return true;
  });

const SpillCut kOtherBack = !kCCNuMu && !kPileUp && !kNC && !kCCNuE;

std::vector<TrueDef> ccnumu_sig_back_categories = {
  {"Signal (CC #nu_{#mu})", kCCNuMu, kMagenta+2, "Signal"},
  {"PileUp", kPileUp, kTeal+8, "PileUp"},
  {"NC", kNC, kOrange+2, "NC"},
  {"CC #nu_{e}", kCCNuE, kCyan+2, "CCNuE"},
  {"Other", kOtherBack, kBlack, "Other"},
  {"Background", !kCCNuMu, kBlack, "Background"}
};

std::vector<CutInfo> ccnumu_cuts = {
  {"No Selection", kNoSpillCut, "NoCuts"},
  {"Has #nu Slice", kHasNuSlc, "HasNuSlc"},
  {"Reco FV", kRecoFV, "RecoFV"},
  {"Has >=1 Tracks", kHasAtLeastOneTrk, "HasAtLeastOneTrk"},
  {"Longest Track Length > 50cm", kLongestTrkLength, "LongestTrkLength"},
};
