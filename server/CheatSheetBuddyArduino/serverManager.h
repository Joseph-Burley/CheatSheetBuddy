#include <FreeRTOS.h>
#include "secrets.h"
#include <SPI.h>
#include <WiFi101.h>
#include <aWOT.h>
#include "display.h"

void index(Request &req, Response &res);
void TaskServer(void *pvParameters);