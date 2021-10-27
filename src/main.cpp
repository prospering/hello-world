#include <Arduino.h>
#include <M5Stack.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
StaticJsonDocument<256> doc;
StaticJsonDocument<256> dataDoc;

void setup() {
  // put your setup code here, to run once:
  M5.begin(115200);
  M5.Power.begin();
  M5.Lcd.textsize = 2;
  WiFi.begin("CAMPUS NUMERIQUE GRENOBLE", "TQPYE97437");
  M5.Lcd.println("connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1);
  }
  M5.Lcd.clear();
  M5.Lcd.println("connected");
  HTTPClient http;
  http.addHeader("x-api-key", "cHqVZbl1sA248m3bg21uF7AhZqMvySeJ447BDXKe");
  // http.addHeader("Content-type", "application/json");
  http.begin("http://api.bagtower.bag-era.fr/prod/logs");
  JsonObject root = doc.to<JsonObject>();
  JsonObject data = dataDoc.to<JsonObject>();
  data["id"] = "title";
  data["type"] = "string";
  data["val"] = "testval";
  root["unixTimestamp"] = 0;
  root.createNestedArray("data");
  root["data"].add(data);
  root["UTCTimestamp"] = "now";
  root["deviceId"] = "6f34c9b0-1791-1:86539070-365b-11ec-b";
  String payload;
  serializeJson(doc, payload);
  M5.Lcd.println(payload);
  int httpCode = http.POST(payload);
  if (httpCode > 0) {
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