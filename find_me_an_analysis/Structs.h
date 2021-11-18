struct TrueDef {
  std::string name = "";
  SpillCut cut = kNoSpillCut;
  int colour = kBlack;
  std::string label = "";
};

struct CutInfo {
  std::string name = "";
  SpillCut cut = kNoSpillCut;
  std::string label = "";
};

struct Selection {
  std::string name = "";
  std::vector<TrueDef> categories = {};
  std::vector<CutInfo> cuts = {};
  std::string label = "";
};
