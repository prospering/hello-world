#include <Arduino.h>
#include <M5Stack.h>
#include <WiFi.h>
#include <TimeLib.h>


char timeToDisplay[20];
char* ssid = "Campus2"; 
const char* pass = "12345678";


void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Power.begin();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0,10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(3);
  
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.printf("Connecting to WiFi...");
  }
 
  M5.Lcd.println("Connected to the WiFi network");

  
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("Hello World");

}

void loop() {
  // put your main code here, to run repeatedly:
}