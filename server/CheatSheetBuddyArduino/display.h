#include <SPI.h>
//#include <string.h>
#include "Adafruit_GFX.h"
#include "Adafruit_RA8875.h"

#define RA8875_CS 6
#define RA8875_RESET 9
//Adafruit_RA8875 tft;
// Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);

bool startDisplay();
void runDisplay();

bool updateDisplay(char* message);