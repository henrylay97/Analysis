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
      if(prim.pdg == 211) nproton++;

    return nproton;
  });

const SpillCut kCCZeroPi([](const caf::SRSpillProxy* sp) {
    if(!kCC(sp)) return false;

    return kNPiPlus(sp) == 0 && kNPiMinus(sp) == 0 && kNPiZero(sp) == 0;
  });

const SpillCut kCCPiPlusMinus([](const caf::SRSpillProxy* sp) {
    if(!kCC(sp)) return false;

    return kNPiZero(sp) == 0 && (kNPiPlus(sp) + kNPiMinus(sp)) == 1;
  });

const SpillCut kCCPiZero([](const caf::SRSpillProxy* sp) {
    if(!kCC(sp)) return false;
    
    return kNPiPlus(sp) == 0 && kNPiMinus(sp) == 0 && kNPiZero(sp) == 1;
  });

const SpillCut kCCMultiPion([](const caf::SRSpillProxy* sp) {
    if(!kCC(sp)) return false;

    return (kNPiPlus(sp) + kNPiMinus(sp) + kNPiZero(sp)) > 1;
  });

const SpillCut kNCInvisible([](const caf::SRSpillProxy* sp) {
    if(!kNC(sp)) return false;

    return kNPiPlus(sp) == 0 && kNPiMinus(sp) == 0 && kNPiZero(sp) == 0 && kNProton(sp) == 0;
  });

const SpillCut kNCProton([](const caf::SRSpillProxy* sp) {
    if(!kNC(sp)) return false;

    return kNPiPlus(sp) == 0 && kNPiMinus(sp) == 0 && kNPiZero(sp) == 0 && kNProton(sp) > 0;
  });

const SpillCut kNCPiPlusMinus([](const caf::SRSpillProxy* sp) {
    if(!kNC(sp)) return false;

    return kNPiZero(sp) == 0 && (kNPiPlus(sp) + kNPiMinus(sp)) == 1;
  });

const SpillCut kNCPiZero([](const caf::SRSpillProxy* sp) {
    if(!kNC(sp)) return false;

    return kNPiPlus(sp) == 0 && kNPiMinus(sp) == 0 && kNPiZero(sp) == 1;
  });

const SpillCut kNCMultiPion([](const caf::SRSpillProxy* sp) {
    if(!kNC(sp)) return false;

    return (kNPiPlus(sp) + kNPiMinus(sp) + kNPiZero(sp)) > 1;
  });

const SpillCut kOther = !kPileUp && !kNC && !kCCNuMu && !kCCNuE;
const SpillCut kOtherNC = kNC && !kNCInvisible && !kNCProton && !kNCPiPlusMinus && !kNCPiZero && !kNCMultiPion;
const SpillCut kOtherCC = kCC && !kCCZeroPi && !kCCPiPlusMinus && !kCCPiZero && !kCCMultiPion;

struct TrueDef {
  std::string name = "";
  SpillCut cut = kNoSpillCut;
  int colour = kBlack;
  std::string label = "";
};

std::vector<TrueDef> categories = {
  {"PileUp", kPileUp, kTeal+8, "PileUp"},
  {"NC", kNC, kOrange+2, "NC"},
  {"CC #nu_{#mu}", kCCNuMu, kMagenta+2, "CCNuMu"},
  {"CC #nu_{e}", kCCNuE, kCyan+2, "CCNuE"},
  {"Other", kOther, kBlack, "Other"}
};

std::vector<TrueDef> nc_categories = {
  {"NC Invisible", kNCInvisible, kGray+1, "NCInv"},
  {"NC Proton", kNCProton, kOrange+3, "NCProt"},
  {"NC 1#pi^{#pm}", kNCPiPlusMinus, kMagenta+2, "NCPiPlusMinus"},
  {"NC 1#pi^{0}", kNCPiZero, kViolet+2, "NCPiZero"},
  {"NC Multi Pion", kNCMultiPion, kCyan+2, "NCMultiPion"},
  {"Other", kOtherNC, kBlack, "Other"}
};

std::vector<TrueDef> cc_categories = {
  {"CC 0#pi", kCCZeroPi, kRed-3, "CCZeroPi"},
  {"CC 1#pi^{#pm}", kCCPiPlusMinus, kMagenta+2, "CCPiPlusMinus"},
  {"CC 1#pi^{0}", kCCPiZero, kViolet+2, "CCPiZero"},
  {"CC Multi Pion", kCCMultiPion, kCyan+2, "CCMultiPion"},
  {"Other", kOtherCC, kBlack, "Other"}
};
