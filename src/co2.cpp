//SGP30 needs 15 seconds to initialize calibration after power on.
//The screen will display TVOC and CO2

#include <M5Stack.h>
#include "Adafruit_SGP30.h"

Adafruit_SGP30 sgp;
int i = 15;
long last_millis = 0;



void co2_sensor_setup() {
  M5.Lcd.println("SGP30 test");
  if (! sgp.begin()){
    M5.Lcd.println("Sensor not found :'(");
    while (1);
  }
  
  M5.Lcd.print("Found SGP30 serial #");
  M5.Lcd.print(sgp.serialnumber[0], HEX);
  M5.Lcd.print(sgp.serialnumber[1], HEX);
  M5.Lcd.println(sgp.serialnumber[2], HEX);
  M5.Lcd.println("Initialization...");
}

void co2_sensor_init() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  while(i > 0) {    
    if(millis()- last_millis > 1000) {
      last_millis = millis();
      i--;
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.println(i);
    }
  }

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);

  if (! sgp.IAQmeasure()) {
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("Measurement failed");
    return;
  }

  M5.Lcd.println("CO2 captor:");

  M5.Lcd.print("\n- TVOC "); 
  M5.Lcd.print(sgp.TVOC); 
  M5.Lcd.print(" ppb\t");
  M5.Lcd.print("\n- eCO2 "); 
  M5.Lcd.print(sgp.eCO2); 
  M5.Lcd.println(" ppm");
 
  delay(1000);
}