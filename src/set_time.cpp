#include <Arduino.h>
#include <M5Stack.h>
#include <time.h>

time_t getTimestamp() {
  time_t timestamp;
  return time(&timestamp);
}

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    M5.Lcd.println("Failed to obtain time");
    return;
  }
  M5.Lcd.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}