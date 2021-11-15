const SpillCut kHasAtLeastOneTrk([](const caf::SRSpillProxy *sp) {
    auto const &slc = sp->slc[kBestSliceID(sp)];
    
    return slc->reco.ntrk > 0;  
  });

const SpillCut kLongestTrkLength([](const caf::SRSpillProxy *sp) {
    auto const &slc = sp->slc[kBestSliceID(sp)];
    auto const &trk = slc->reco.trk[kLongestTrkID(sp)];

    return trk.len > 50;
  });

const SpillCut kOtherTrkLength([](const caf::SRSpillProxy *sp) {
    auto const &slc = sp->slc[kBestSliceID(sp)];

    for(unsigned i = 0; i < slc->reco.ntrk; ++i) {
      if(i == kLongestTrkID(sp))
	continue;

      auto const& trk = slc->reco.trk[i];
      if(trk.len > 100)
	return false;
    }

    return true;
  });
