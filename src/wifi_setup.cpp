#include <Arduino.h>
#include <M5Stack.h>
#include <WiFi.h>

#include "const.local.h"

//sets up the wifi, sends an error message if the connection is established and prints the ip address if it works
void setup_wifi()
{
  WiFi.begin(SSID, PASS);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.printf("Connecting to WiFi...");
  }

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);

  M5.Lcd.println("Connected to the WiFi network");
  M5.Lcd.println(SSID);
  M5.Lcd.println("\nAdresse IP : ");
  M5.Lcd.println(WiFi.localIP());
}