#include <Arduino.h>
#include <M5Stack.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <const.local.h>
StaticJsonDocument<256> doc;
StaticJsonDocument<256> dataDoc;

void setupM5() {
  M5.begin(115200);
  M5.Power.begin();
  M5.Lcd.textsize = 2;
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

void printMsg(String msg) {
  M5.Lcd.println(msg);
  Serial.println(msg);
}

void beginConnect(HTTPClient &http, String url = "https://api.bagtower.bag-era.fr/prod/logs") {
  http.addHeader("x-api-key", "CifhSACFQeaS21CNsLMjO3WQ1GjEucyT5ytQXez0");
  http.addHeader("Content-type", "application/json");
  http.begin(url);
}

void setup() {
  setupM5();
  WiFi.begin(ssid, pass);
  printMsg("connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1);
  }
  printMsg("connected");
  HTTPClient http;
  beginConnect(http);
  String payload = generateLogJson("title", "string", "value", 0, "now", "6f34c9b0-1791-1:69e1c3d0-365b-11ec-b");
  printMsg(payload);
  int httpCode = http.POST(payload);
  Serial.printf("%d: %s", httpCode, http.getString().c_str());

  if (httpCode >= 200 && httpCode < 300) {
    String content = http.getString();
    printMsg(content);
  }
  else {
    printMsg("error");
  };
}

void loop() {
}