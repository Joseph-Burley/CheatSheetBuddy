// #include <FreeRTOS.h>
// #include "secrets.h"
// #include <SPI.h>
// #include <WiFi101.h>
// #include <aWOT.h>
#include "serverManager.h"

WiFiServer server(80);
Application app;

char data[100] = {0};

void index(Request &req, Response &res) {
  Serial.println("processing request");
  res.status(200);
  res.set("Content-Type", "text/html");
  res.set("Connection", "close");
  res.println("<html>");
  res.println("<p>Hello from FreeRTOS</p>");
  res.println("</html>");
  res.end();
}

void testPost(Request &req, Response &res) {
  Serial.println("Here is the data: ");
  while (req.available()) {
    Serial.println(req.readString());
  }
  res.status(200);
  res.end();
}

void store(Request &req, Response &res) {
  Serial.println("processing a store");
  bool success = req.query("data", data, 100);
  if (success) {
    res.status(200);
    res.set("Content-Type", "text/html");
    res.set("Connection", "close");
    res.println("<html>");
    res.println("<p>Successfully stored data</p>");
    res.println("</html>");
    res.end();
  } else {
    res.status(500);
    res.set("Content-Type", "text/html");
    res.set("Connection", "close");
    res.println("<html>");
    res.println("<p>Could not store data</p>");
    res.println("</html>");
    res.end();
  }
}

void retrieve(Request &req, Response &res) {
  res.status(200);
  res.set("Content-Type", "text/html");
  res.set("Connection", "close");
  res.println("<html>");
  res.print("<p>The data is: ");
  res.print(data);
  res.println("</p>");
  res.println("</html>");
  res.end();
}

void TaskServer(void *pvParameters) {
  TickType_t delayTime = *((TickType_t *)pvParameters);
  //data = {0};

  app.get("/", &index);
  app.get("/store", &store);
  app.get("/retrieve", &retrieve);
  app.post("/testPost", &testPost);
  server.begin();
  Serial.println("server is set up");
  int num_loops = 0;
  UBaseType_t uxHighWaterMark = 0;

  while (1) {
    //Serial.println("server loop is running");
    num_loops += 1;
    WiFiClient client = server.available();

    //this nest of conditionals is required because of task switching
    //to ensure the entire http request has arrived before processing it.
    if (client) {
      if (client && client.connected()) {
        while (client.connected() && !client.available()) {
          vTaskDelay(pdMS_TO_TICKS(1));
        }
        if (client.available()) {
          Serial.println("got a request");
          app.process(&client);
          client.stop();
        }
      }
    }

    if (num_loops > 10000) {
      Serial.println("The server loop is still running");
      uxHighWaterMark = uxTaskGetStackHighWaterMark(NULL);
      Serial.print("The highwater mark is: ");
      Serial.println(uxHighWaterMark);
      num_loops = 0;
    }

    vTaskDelay(pdMS_TO_TICKS(delayTime));
  }
}