//SGP30 needs 15 seconds to initialize calibration after power on.
//The screen will display TVOC and CO2

#include <M5Stack.h>
#include "Adafruit_SGP30.h"
#include "printMsg.h"

Adafruit_SGP30 sgp;
int i = 15;
long last_millis = 0;
/* void header_SPG30(const char *string)
{
    M5.Lcd.setTextColor(TFT_WHITE, TFT_BLACK);
    M5.Lcd.fillRect(0, 0, 320, 30, TFT_BLACK);
    M5.Lcd.setTextDatum(TC_DATUM);
    M5.Lcd.drawString(string, 160, 3, 4); 
} */



void co2_sensor_setup() {
  /* header_SPG30("SGP30 TEST"); */
  M5.Lcd.println("SGP30 test");
  if (! sgp.begin()){
    printMsg("Sensor not found :'(");
    while (1);
  }
  
  printMsg("Found SGP30 serial #");
  M5.Lcd.print(sgp.serialnumber[0], HEX);
  M5.Lcd.print(sgp.serialnumber[1], HEX);
  M5.Lcd.println(sgp.serialnumber[2], HEX);
  printMsg("Initialization...");
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
    printMsg("Measurement failed");
    return;
  }

  printMsg("CO2 captor:");

  M5.Lcd.print("\n- TVOC "); 
  M5.Lcd.print(sgp.TVOC); 
  M5.Lcd.print(" ppb\t");
  printMsg("\n- eCO2 "); 
  M5.Lcd.print(sgp.eCO2); 
  M5.Lcd.println(" ppm");
 
  delay(1000);
}