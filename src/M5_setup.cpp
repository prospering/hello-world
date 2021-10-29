
#include <Arduino.h>
#include <M5Stack.h>


void setupM5() {
  M5.begin(115200);
  M5.Power.begin();
  M5.Speaker.begin();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2.5);
}

void setupScreenDisplay() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  long last_millis = 0;
  for(int i = 15; i>0; i--) {    
    if(millis()- last_millis > 1000) {
      last_millis = millis();
      i--;
      M5.Lcd.fillScreen(BLACK);
      M5.Lcd.setCursor(0, 0);
      M5.Lcd.println(i);
    }
  }
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.println("CO2 captor:");
  M5.Lcd.print("\n- TVOC  "); 
  M5.Lcd.println("\n- eCO2  "); 
}