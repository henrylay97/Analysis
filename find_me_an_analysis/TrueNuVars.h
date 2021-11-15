const SpillVar kTrueNuEn([](const caf::SRSpillProxy* sp) -> float {
    float en(-5.f);
    for(auto const& nu : sp->mc.nu) {
      if(nu.E > en)
	en = nu.E;
    }
    return en;
  });
