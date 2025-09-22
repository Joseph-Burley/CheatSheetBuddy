#include <SPI.h>
#include <WiFi101.h>
#include <aWOT.h>
#include <SD.h>

char ssid[] = NETWORK
char pass[] = PASS

WiFiServer server(80);
Application app;

const int SDchipSelect = 4; //from the RP2350 about page
char content[100];
  
void index(Request &req, Response &res) {
  res.status(200);
  res.set("Content-Type","text/html");
  res.set("Connection", "close");
  res.println("<html>");
  res.println("<p>Hello there</p>");
  res.println("</html>");
  res.end();
}

void about(Request &req, Response &res) {
  res.status(200);
  res.set("Content-Type","text/html");
  res.set("Connection", "close");
  res.println("<html>");
  res.println("<p>This is the about page</p>");
  res.println("</html>");
  res.end();
}

void test(Request &req, Response &res) {
  res.status(200);
  res.set("Content-Type","text/html");
  res.set("Connection", "close");
  res.println("<html>");
  res.println("<p>This is the content of the file</p>");
  res.print("<p>");
  res.print(content);
  res.println("</p>");
  res.println("</html>");
  res.end();
}

void anotherTest(Request &req, Response &res) {
  res.status(200);
  res.set("Content-Type","text/html");
  res.set("Connection", "close");
  res.println("<html>");
  res.println("<p>This is the content of the file from the second test endpoint</p>");
  res.print("<p>");

  bool found_card = 0;
  Serial.println("trying SD card...");
  if (!SD.begin(SDchipSelect)) {
    Serial.println("something is wrong with the card");
  } else {
    Serial.println("Card found");
    found_card = 1;
  }
  Serial.println("\nfile read");
  if (found_card) {
    File dataFile = SD.open("test.txt");
    while (dataFile.available()) {
      res.write(dataFile.read());
    }
    dataFile.close();
  }
  SD.end();

  res.println("</p>");
  res.println("</html>");
  res.end();
}
  
void setup() {
  Serial.begin(115200);
  
  delay(5000);

  bool found_card = 0;
  Serial.println("trying SD card...");
  if (!SD.begin(SDchipSelect)) {
    Serial.println("something is wrong with the card");
  } else {
    Serial.println("Card found");
    found_card = 1;
  }
  Serial.println("\nfile read");
  if (found_card) {
    File dataFile = SD.open("test.txt");
    while (dataFile.available()) {
      dataFile.readBytes(content, 100);
    }
    dataFile.close();
  }
  SD.end();

  Serial.print("Trying to connect to: ");
  Serial.println(ssid);
  
  
  while (WiFi.status() != WL_CONNECTED) {
    WiFi.begin(ssid, pass);
    delay(500);
    Serial.print(".");
  }

  IPAddress ip = WiFi.localIP();
  Serial.println("The local address is:");
  Serial.println(ip);

  app.get("/", &index);
  app.get("/about", &about);
  app.get("/test", &test);
  app.get("/anotherTest", &anotherTest);
  server.begin();
}
  
void loop() {  
  WiFiClient client = server.available();
  
  if (client.connected()) {
    Serial.println("got a request");
    app.process(&client);
    client.stop();
  }
}