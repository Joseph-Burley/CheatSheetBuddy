#include <string>
#include <vector>
#include <ArduinoJson.h>
struct metadata {
  String filename;
  std::vector<String> shortnames;
};

enum indexResult {
  OK,
  NO_CARD,
  WRITE_FAILED,
  BAD_SPI,
  BAD_FORMAT,
};

std::vector<metadata> sheetIndex;

//loads the index from the SD card and saves it into the index vector
indexResult loadIndex();

//saves the index to the SD card
indexResult saveIndex();
