#include <Arduino.h>
#include <M5Stack.h>
#include <WiFi.h>
#include <time.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "pir.h"
#include "co2.h"
#include "const.local.h"
#include "printMsg.h"

StaticJsonDocument<256> doc;
StaticJsonDocument<256> dataDoc;


void setupM5() {
  M5.begin(115200);
  M5.Power.begin();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2.5);
}

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    M5.Lcd.println("Failed to obtain time");
    return;
  }
  M5.Lcd.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

//sets up the wifi, sends an error message if the connection is established and prints the ip address if it works
void setup_wifi()
{
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.printf("Connecting to WiFi...");
  }

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);

  M5.Lcd.println("Connected to the WiFi network");
  M5.Lcd.println(SSID);
  M5.Lcd.println("\nAdresse IP : ");
  M5.Lcd.println(WiFi.localIP());
}

String generateLogJson(String id, String type, String val, int timestamp, String UTCTimestamp, String deviceId) {
  JsonObject root = doc.to<JsonObject>();
  JsonObject data = dataDoc.to<JsonObject>();
  data["id"] = id;
  data["type"] = type;
  data["val"] = val;
  root["unixTimestamp"] = timestamp;
  root.createNestedArray("data");
  root["data"].add(data);
  root["UTCTimestamp"] = UTCTimestamp;
  root["deviceId"] = deviceId;
  String payload;
  serializeJson(doc, payload);
  return payload;
}

void beginConnect(HTTPClient &http, String url = "https://api.bagtower.bag-era.fr/prod/logs") {
  http.begin(url);
  http.addHeader("Content-type", "application/json");
  http.addHeader("x-api-key", X_API_KEY);
}

void setup() {
  setupM5();
  setup_wifi();
  //init and get the time
  configTime(3600, 3600, NTP_SERVER);
  printLocalTime();
  HTTPClient http;
  beginConnect(http);
  String payload = generateLogJson("title", "string", "value", 0, "now", DEVICE_ID);
  // printMsg(payload);
  int httpCode = http.POST(payload);
  // Serial.printf("%d: %s", httpCode, http.getString().c_str());

  co2_sensor_setup();
  pir_sensor_setup();

  if (httpCode >= 200 && httpCode < 300) {
    String content = http.getString();
    printMsg(content);
  }
  else {
    printMsg("error");
  };
}

void loop() {
  delay(1000);
  // M5.Lcd.fillScreen(BLACK);
  // M5.Lcd.setCursor(0, 0);

  // M5.Lcd.println("Connected to the WiFi network");
  // M5.Lcd.println(SSID);
  // M5.Lcd.println("\nAdresse IP : ");
  // M5.Lcd.println(WiFi.localIP());
  
  printLocalTime();

  delay(1000);
  // M5.Lcd.fillScreen(BLACK);
  // M5.Lcd.setCursor(0, 0);

  co2_sensor_init();
  pir_sensor_init();

}
