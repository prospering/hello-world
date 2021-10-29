#include <Arduino.h>
#include <M5Stack.h>
#include <WiFi.h>
#include <time.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#include "pir.h"
#include "co2.h"
#include "const.h"
#include "printMsg.h"

StaticJsonDocument<256> doc;
StaticJsonDocument<256> dataDoc;
struct tm timeinfo;

time_t getTimestamp() {
  time_t timestamp;
  return time(&timestamp);
}

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
  /* struct tm timeinfo; */
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

String generateLogJson(String id, String type, int val, int timestamp, String UTCTimestamp, String deviceId) {
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

void send_data_to_API(String payload){
  HTTPClient http;
  beginConnect(http);
  int httpCode = http.POST(payload);
  Serial.println("httpcode");
  Serial.println(httpCode);
  if (httpCode >= 200 && httpCode < 300) {
    String content = http.getString();
    printMsg(content);
  }
  else {
    printMsg("error");
  };
}

void setup() {
  setupM5();
  setup_wifi();
  configTime(3600, 3600, NTP_SERVER);

  co2_sensor_setup();
  pir_sensor_setup();

}

void loop() {
  delay(1000);


  co2_sensor_init();
  pir_sensor_init();

  int eCO2 = getECO2();
  String payload_CO2 = generateLogJson("Co2 sensor - eCO2", "number", eCO2, getTimestamp(), "now", DEVICE_ID);
  Serial.println(payload_CO2);
  send_data_to_API(payload_CO2);
  
  int TVOC = getTVOC();
  String payload_TVOC = generateLogJson("Co2 sensor - TVOC", "number", TVOC, getTimestamp(), "now", DEVICE_ID);
  send_data_to_API(payload_TVOC);

  delay(100000);

  

}
