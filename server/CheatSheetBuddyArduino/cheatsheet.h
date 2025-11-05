#include <vector>
struct metadata {
  string filename;
  string[] shortnames;
};

enum indexResult {
  OK,
  NO_CARD,
  WRITE_FAILED,
};

std::vector<metadata> index;

//loads the index from the SD card and saves it into the index vector
indexResult loadIndex();

//saves the index to the SD card
indexResult saveIndex();
