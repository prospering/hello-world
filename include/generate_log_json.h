#include <Arduino.h>
#include <M5Stack.h>
#include <ArduinoJson.h>

String generateLogJson(String id, String type, int val, int timestamp, String UTCTimestamp, String deviceId);