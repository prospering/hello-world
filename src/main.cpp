#include <Arduino.h>
#include <M5Stack.h>

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Power.begin();

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0,10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);
  M5.Lcd.printf("Hello World");

}

void loop() {
  // put your main code here, to run repeatedly:
}