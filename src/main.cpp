#include <Arduino.h>
#include <M5Stack.h>
#include <WiFi.h>

char* ssid = "Campus2"; 
const char* pass = "12345678";

void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Power.begin();

  WiFi.begin(ssid, pass);

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0,10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);
  M5.Lcd.printf("Hello World");
  M5.Lcd.printf("\nMy name is ...\n\nProspering");
  M5.Lcd.printf("\n\nNice meeting you :)");

}

void loop() {
  // put your main code here, to run repeatedly:
}