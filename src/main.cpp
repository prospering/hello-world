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
#include "api_controller.h"
#include "generate_log_json.h"
#include "set_time.h"
#include "wifi_setup.h"
#include "M5_setup.h"
#include "music.h"


void setup() {
  setupM5();
  setup_wifi();
  configTime(3600, 3600, NTP_SERVER);
  printLocalTime();

  co2_sensor_setup();
  pir_sensor_setup();

  setupScreenDisplay();
}

void loop() {

  M5.Lcd.setCursor(10, 80);
  M5.Lcd.fillRect(10, 80, 100, 34, BLACK);
  printLocalTime();

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
