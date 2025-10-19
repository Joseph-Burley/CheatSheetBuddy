#include "neopixelTest.h"

void TaskNeopixel(void *pvParameters) {
  TickType_t delayTime = *((TickType_t *)pvParameters);

  Adafruit_NeoPixel pixel(NUMPIXELS, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
  pixel.begin();

  Serial.println("Neopixel set up");
  //pixel.setPixelColor(0,255,255,255);
  for (;;) {
    pixel.setPixelColor(0, 255, 0, 0);  //set pixel red
    pixel.show();
    vTaskDelay(delayTime / portTICK_PERIOD_MS);
    pixel.setPixelColor(0, 0, 255, 0);  //set pixel green
    pixel.show();
    vTaskDelay(delayTime / portTICK_PERIOD_MS);
    pixel.setPixelColor(0, 0, 0, 255);  //set pixel blue
    pixel.show();
    vTaskDelay(delayTime / portTICK_PERIOD_MS);
    //Serial.println("cycle over");
  }
}