
#include <Arduino.h>
#include <M5Stack.h>
#include <ArduinoJson.h>

StaticJsonDocument<256> doc;
StaticJsonDocument<256> dataDoc;

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