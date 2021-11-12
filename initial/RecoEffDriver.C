#include "RecoEff.C"

void RecoEffDriver()
{
  std::string sample = "defname: official_MC2021Bv1_prodoverlay_corsika_cosmics_proton_genie_nu_spill_gsimple-configh-v1_tpc_reco2_flat_caf_sbnd";
  RunRecoEff(sample, 11);

  sample = "defname: test100_official_test100_MC2021Bv1_prodoverlay_corsika_cosmics_proton_genie_nu_spill_gsimple-configh-v1_tpc_reco2_caf_sbnd with limit 100";
  RunRecoEff(sample, 2212);
  RunRecoEff(sample, 13);
}
