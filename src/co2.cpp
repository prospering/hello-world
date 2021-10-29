//SGP30 needs 15 seconds to initialize calibration after power on.
//The screen will display TVOC and CO2

#include <M5Stack.h>
#include "Adafruit_SGP30.h"

Adafruit_SGP30 sgp;

void co2_sensor_setup() {
  M5.Lcd.println("SGP30 test");
  if (! sgp.begin()){
    Serial.println("Sensor not found :'(");
    while (1);
  }
  
  M5.Lcd.print("Found SGP30 serial #");
  M5.Lcd.print(sgp.serialnumber[0], HEX);
  M5.Lcd.print(sgp.serialnumber[1], HEX);
  M5.Lcd.println(sgp.serialnumber[2], HEX);
  M5.Lcd.println("Initialization...");
}

void co2_sensor_print_data() {
  if (! sgp.IAQmeasure()) {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("Measurement failed");
    return;
  }
  M5.Lcd.setCursor(75, 48);
  M5.Lcd.fillRect(75,48,200,32,BLACK);
  M5.Lcd.print(sgp.TVOC);
  M5.Lcd.print("  ppb");
  M5.Lcd.setCursor(75, 64);
  M5.Lcd.print(sgp.eCO2);
  M5.Lcd.print("  ppm");
} 

int getTVOC() {
  return sgp.TVOC;
}

int getECO2() {
  return sgp.eCO2;
}