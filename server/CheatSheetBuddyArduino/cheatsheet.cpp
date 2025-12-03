#include "cheatsheet.h"
#include "commonGlobals.h"
#include <SPI.h>
#include <SD.h>

namespace ArduinoJson {

template <>
struct Converter<metadata> {
  static void toJson(const metadata& src, JsonVariant dst) {
    dst["filename"] = src.filename;

    JsonArray arr = dst["shortnames"].to<JsonArray>();
    for (const String& s : src.shortnames) {
      arr.add(s);
    }
  }

  static metadata fromJson(JsonVariantConst src) {
    metadata dst;

    dst.filename = src["filename"].as<String>();

    for (JsonVariantConst v : src["shortnames"].as<JsonArrayConst>()) {
      dst.shortnames.push_back(v.as<String>());
    }

    return dst;
  }

  static bool checkJson(JsonVariantConst src) {
    return src["filename"].is<String>() &&
           src["shortnames"].is<JsonArrayConst>();
  }
};

} // namespace ArduinoJson

indexResult loadIndex() {
  int CS = 10;
  bool sdInit = SD.begin(CS);

  if (!sdInit) {
    return indexResult::BAD_SPI;
  }

  File indexFile = SD.open(Common::INDEX_FILE);
  if (!indexFile) {
    return indexResult::NO_CARD;
  }

  JsonDocument doc;
  DeserializationError err = deserializeJson(doc, indexFile);
  if (err) {
    return indexResult::BAD_FORMAT;
  }
  
  //sheetIndex = doc["items"].as<std::vector<metadata>>();

  return indexResult::OK;
}