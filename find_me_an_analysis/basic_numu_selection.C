#include "sbnana/CAFAna/Core/Spectrum.h"
#include "sbnana/CAFAna/Core/SpectrumLoader.h"
#include "sbnana/CAFAna/StandardRecord/Proxy/SRProxy.h"
#include "sbnana/SBNAna/Cuts/VolumeDefinitions.h"

using namespace ana;

#include "TrueEventCategories.h"
#include "TrueNuVars.h"
#include "GenericCuts.h"
#include "CCNuMuCuts.h"

#include "plot_a_selection.C"

void basic_numu_selection()
{
  setlocale(LC_NUMERIC, "");
  const std::string inputName = "defname: test100_official_test100_MC2021Bv1_prodoverlay_corsika_cosmics_proton_genie_nu_spill_gsimple-configh-v1_tpc_reco2_caf_sbnd";

  const double gPOT = 1e20;

  std::vector cumulative_cuts = make_cumulative_cuts(ccnumu_cuts);
  std::vector n_minus_one_cuts = make_n_minus_one_cuts(ccnumu_cuts);

  std::vector all_cuts = ccnumu_cuts;
  all_cuts.insert(all_cuts.end(), cumulative_cuts.begin(), cumulative_cuts.end());
  all_cuts.insert(all_cuts.end(), n_minus_one_cuts.begin(), n_minus_one_cuts.end());

  fill_and_save_spectra(inputName, all_cuts, ccnumu_sig_back_categories);

  plot_selection(ccnumu_cuts, ccnumu_sig_back_categories, gPOT);
  plot_selection(cumulative_cuts, ccnumu_sig_back_categories, gPOT);
  plot_selection(n_minus_one_cuts, ccnumu_sig_back_categories, gPOT);

  plot_cumulative_selection_metrics(cumulative_cuts, gPOT);
}
