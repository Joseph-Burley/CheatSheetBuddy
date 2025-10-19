#include "display.h"
Adafruit_RA8875 tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);

bool startDisplay() {
  Serial.println("starting display");
  delay(5000);
  Serial.println("display starting");
  //tft = Adafruit_RA8875(RA8875_CS, RA8875_RESET);

  if (!tft.begin(RA8875_800x480)) {
    Serial.println("display not found");
    return false;
  }

  tft.displayOn(true);
  tft.GPIOX(true);
  tft.PWM1config(true, RA8875_PWM_CLK_DIV1024);
  tft.PWM1out(255);
  tft.fillScreen(RA8875_BLACK);
  tft.textMode();
  tft.cursorBlink(32);
  
  return true;
}

void runDisplay() {
  tft.textMode();
  tft.cursorBlink(32);
  char message[15] = "Screen Ready";
  tft.textTransparent(RA8875_WHITE);
  tft.textWrite(message);
}

bool updateDisplay(char* message) {
  Serial.print("screen got data: ");
  Serial.println(message);
  tft.fillScreen(RA8875_BLACK);
  tft.textMode();
  tft.textTransparent(RA8875_WHITE);
  tft.textSetCursor(0, 0);
  tft.textEnlarge(2);
  tft.textWrite(message);
  return true;
}