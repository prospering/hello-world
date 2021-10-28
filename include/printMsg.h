#include <Arduino.h>
#include <M5Stack.h>

void printMsg(String msg) {
  M5.Lcd.println(msg);
  Serial.println(msg);
}