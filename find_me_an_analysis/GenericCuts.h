const SpillCut kTrueFV([](const caf::SRSpillProxy* sp) {
    return PtInVolAbsX(sp->mc.nu[0].position, fvnd);
  });

const SpillCut kHasNuSlc([](const caf::SRSpillProxy *sp) {
    for(auto const& slc : sp->slc) {
      if(!slc.is_clear_cosmic) return true;
    }
    return false;
  });

const SpillVar kBestSliceID([](const caf::SRSpillProxy *sp) -> unsigned {
  unsigned index(999999);
  float nu_score(-std::numeric_limits<float>::max());
  for(int i = 0; i < sp->nslc; ++i){
    auto const &slc = sp->slc[i];
    if(slc.nu_score > nu_score){
      index = i;
      nu_score = slc.nu_score;
    }
  }
  return index;
  });

const SpillCut kRecoFV([](const caf::SRSpillProxy* sp) {
    if(sp->nslc == 0)
      return false;

    return PtInVolAbsX(sp->slc[kBestSliceID(sp)].vertex, fvnd);
  });

const SpillVar kLongestTrkID([](const caf::SRSpillProxy *sp) -> unsigned {
    auto const& slc = sp->slc[kBestSliceID(sp)];

    unsigned index(999999);
    float trk_length(-std::numeric_limits<float>::max());

    for(unsigned i = 0; i < slc.reco.ntrk; ++i) {
      auto const& trk = slc.reco.trk[i];
      if(trk.len > trk_length) {
	trk_length = trk.len;
	index = i;
      }
    }
    
    return index;
  });

const SpillVar kLargestShwID([](const caf::SRSpillProxy *sp) -> unsigned {
    auto const& slc = sp->slc[kBestSliceID(sp)];

    unsigned index(999999);
    float shw_en(-std::numeric_limits<float>::max());

    for(unsigned i = 0; i < slc.reco.nshw; ++i) {
      auto const& shw = slc.reco.shw[i];
      if(shw.bestplane_energy > shw_en) {
	shw_en = shw.bestplane_energy;
	index = i;
      }
    }
    
    return index;
  });
