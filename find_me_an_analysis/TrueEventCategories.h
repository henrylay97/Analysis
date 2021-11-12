#include "sbnana/CAFAna/StandardRecord/Proxy/SRProxy.h"

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
    return kCC(sp) && sp->mc.nu[0].pdg == 14;
  });

const SpillCut kCCNuE([](const caf::SRSpillProxy* sp) {
    return kCC(sp) && sp->mc.nu[0].pdg == 12;
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

struct TrueDef {
  std::string name = "";
  SpillCut cut = kNoSpillCut;
  int colour = kBlack;
};

std::vector<TrueDef> categories = {
  {"PileUp", kPileUp, kTeal+8},
  {"NC", kNC, kOrange+2},
  {"CC #nu_{#mu},", kCCNuMu, kMagenta+2},
  {"CC #nu_{e},", kCCNuE, kCyan+2},
  {"Other", !kPileUp && !kNC && !kCCNuMu && !kCCNuE, kBlack}
};

std::vector<TrueDef> nc_categories = {
  {"NC Invisible", kNCInvisible, kGray+1},
  {"NC Proton", kNCProton, kOrange+3},
  {"NC 1#pi^{#pm},", kNCPiPlusMinus, kMagenta+2},
  {"NC 1#pi^{0},", kNCPiZero, kViolet+2},
  {"NC Multi Pion,", kNCMultiPion, kCyan+2},
  {"Other", !kNCInvisible && !kNCProton && !kNCPiPlusMinus && !kNCPiZero && !kNCMultiPion, kBlack}
};

std::vector<TrueDef> cc_categories = {
  {"CC 0#pi", kCCZeroPi, kRed-3},
  {"CC 1#pi^{#pm},", kCCPiPlusMinus, kMagenta+2},
  {"CC 1#pi^{0},", kCCPiZero, kViolet+2},
  {"CC Multi Pion,", kCCMultiPion, kCyan+2},
  {"Other", !kCCZeroPi && !kCCPiPlusMinus && !kCCPiZero && !kCCMultiPion, kBlack}
};
