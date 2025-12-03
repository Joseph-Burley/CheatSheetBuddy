#include "commonGlobals.h"
#include "settings.h"
#include <SPI.h>
#include <SD.h>
#include <ArduinoJson.h>

settingResult loadSettings() {
  int CS = 10;
  bool sdInit = SD.begin(CS);

  if (!sdInit) {
    return settingResult::BAD_SPI;
  }

  File settingsFile = SD.open(Common::SETTING_FILE);
  if (!settingsFile) {
    return settingResult::NO_CARD;
  }

  JsonDocument doc;

  DeserializationError err = deserializeJson(doc, settingsFile);
  if (err) {
    return settingResult::BAD_FORMAT;
  }

  settings.brightness = doc["brightness"];
  settings.switching_time = doc["switching_time"];

  settingsFile.close();
  return settingResult::OK;
}

settingResult saveSettings() {
  int CS = 10;
  bool sdInit = SD.begin(CS);

  if (!sdInit) {
    return settingResult::BAD_SPI;
  }
  SD.remove(Common::SETTING_FILE);

  File settingFile = SD.open(Common::SETTING_FILE, FILE_WRITE);
  if (!settingFile) {
    return settingResult::BAD_SPI;
  }

  JsonDocument doc;
  doc["brightness"] = settings.brightness;
  doc["switching_time"] = settings.switching_time;

  if (serializeJson(doc, settingFile) == 0) {
    return settingResult::WRITE_FAILED;
  }

  settingFile.close();
  return settingResult::OK;
}

settingResult defaultSettings() {
  settings.brightness = 255;
  settings.switching_time = 1000;
  return saveSettings();
}