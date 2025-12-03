struct {
  int brightness = 255;
  int switching_time = 1000;
} settings;

enum settingResult {
  OK,
  NO_CARD,
  WRITE_FAILED,
  BAD_SPI,
  BAD_FORMAT,
};

//reads the settings file from the SD card and saves the contents to the struct
//returns true if the settings were loaded and false if an error was encountered
settingResult loadSettings();

//writes the settings struct to the SD card
//returns true if the settings were saved and false if an error was encountered
settingResult saveSettings();

//writes the defaut settings into the struct and then calls saveSettings()
//returns the return value from saveSettings()
settingResult defaultSettings();