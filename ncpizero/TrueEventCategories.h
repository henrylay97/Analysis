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

std::vector<TrueDef> ncpizero_split_signal_detailed_categories = {
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

std::vector<TrueDef> ncpizero_detailed_categories = {
  {"Signal (NC #pi^{0})", kNCPiZero, kViolet+2, "Signal"},
  {"Other NC", kNC && !kNCPiZero, kOrange+2, "NC"},
  {"CC #nu_{#mu}", kCCNuMu, kMagenta+2, "CCNuMu"},
  {"CC #nu_{e}", kCCNuE, kCyan+2, "CCNuE"},
  {"PileUp", kPileUp, kTeal+8, "PileUp"},
  {"Other", kOtherBack, kBlack, "Other"},
  {"Background", !kNCPiZero, kBlack, "Background"},
};

