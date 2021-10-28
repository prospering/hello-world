#include <Arduino.h>
#include <M5Stack.h>
#include <WiFi.h>
#include <time.h>
#include <const.h>
#include <co2.h>

//Will print an error if time is not obtained and will print the time obtained if it gets it
void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    M5.Lcd.println("Failed to obtain time");
    return;
  }
  M5.Lcd.println(&timeinfo, "\n%A, %B %d %Y %H:%M:%S");
}

//sets up the wifi, sends an error message if the connection is established and prints the ip address if it works
void setup_wifi()
{
  WiFi.begin(ssid, pass);
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
  M5.Lcd.println(ssid);
  M5.Lcd.println("\nAdresse IP : ");
  M5.Lcd.println(WiFi.localIP());

  //print time
  printLocalTime();

  delay(3000);
}

void setup()
{
  M5.begin(true, false, true, true);
  M5.begin(115200);
  M5.Power.begin();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2.5);

  //init and get the time
  configTime(3600, 3600, ntpServer);

  setup_wifi();

  delay(1000);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);

  co2_sensor_setup();
}

//updates the time and ip address
void loop()
{

  delay(1000);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  
  

  //print sensor infos
  co2_sensor_init();

  
  
}
