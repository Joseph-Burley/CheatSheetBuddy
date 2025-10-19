#include "secrets.h"
#include <SPI.h>
#include <WiFi101.h>
//#include <aWOT.h>
#include <FreeRTOS.h>
#include "serverManager.h"
#include "neopixelTest.h"
#include <Adafruit_NeoPixel.h>
#include "display.h"

void taskBlink(void *pvParameters) {
  //TickType_t delayTime = *((TickType_t *)pvParameters);
  Serial.println("This is the setup portion of the blink task");
  pinMode(7, OUTPUT);

  while (1) {
    digitalWrite(7, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    digitalWrite(7, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS);
  }
}

void setup() {
  Serial.begin(115200);

  delay(5000);

  if (startDisplay()) {
    runDisplay();
  } else {
    Serial.println("The display did not start");
  }

  char ssid[] = NETWORK;
  char pass[] = PASS;

  Serial.print("Trying to connect to: ");
  Serial.println(ssid);

  int max_time = 10000;
  int time = 0;
  bool connection = false;
  while (WiFi.status() != WL_CONNECTED && time <= max_time) {
    WiFi.begin(ssid, pass);
    delay(500);
    Serial.print(".");
    time += 500;
  }
  if (time <= max_time) {
    connection = true;
  }

  if (connection) {
    IPAddress ip = WiFi.localIP();
    Serial.println("The local address is:");
    Serial.println(ip);

    Serial.print("The tick period is: ");
    Serial.println(portTICK_PERIOD_MS);


    Serial.println("Creating the server task");
    TickType_t serverDelay = 5;
    Serial.print("The server delay is: ");
    Serial.println((serverDelay / portTICK_PERIOD_MS));
    xTaskCreate(TaskServer,
                "server",
                4096,
                (void *)&serverDelay,  //run every 50ms
                6,
                NULL);
  } else {
    Serial.println("There was an issue connecting. Server task not created.");
  }


  xTaskCreate(taskBlink,
              "Blink",
              128,
              NULL,
              3,
              NULL);

  //vTaskStartScheduler();
}

void loop() {
  //Serial.println("In the loop for some reason");
}