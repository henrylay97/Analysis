const SpillCut kTrueFV([](const caf::SRSpillProxy* sp) {
    return PtInVolAbsX(sp->mc.nu[0].position, fvnd);
  });
