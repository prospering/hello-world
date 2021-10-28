#include <Arduino.h>
#include <M5Stack.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <const.local.h>
StaticJsonDocument<256> doc;
StaticJsonDocument<256> dataDoc;

void setup() {
  // put your setup code here, to run once:
  M5.begin(115200);
  M5.Power.begin();
  M5.Lcd.textsize = 2;
  WiFi.begin(ssid, pass);
  M5.Lcd.println("connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1);
  }
  M5.Lcd.clear();
  M5.Lcd.println("connected");
  HTTPClient http;
  http.addHeader("x-api-key", "CifhSACFQeaS21CNsLMjO3WQ1GjEucyT5ytQXez0");
  http.addHeader("Content-type", "application/json");
  http.begin("https://api.bagtower.bag-era.fr/prod/logs");
  JsonObject root = doc.to<JsonObject>();
  JsonObject data = dataDoc.to<JsonObject>();
  data["id"] = "title";
  data["type"] = "string";
  data["val"] = "testval";
  root["unixTimestamp"] = 0;
  root.createNestedArray("data");
  root["data"].add(data);
  root["deviceId"] = "6f34c9b0-1791-1:69e1c3d0-365b-11ec-b";
  String payload;
  serializeJson(doc, payload);
  M5.Lcd.println(payload);
  Serial.println(payload);
  int httpCode = http.POST(payload);
  Serial.printf("%d: %s", httpCode, http.getString().c_str());
  if (httpCode >= 200 && httpCode < 300) {
    String content = http.getString();
    M5.Lcd.println(httpCode);
    Serial.println(content);
  }
  else {
    M5.Lcd.println("error");
  };
}

void loop() {
}