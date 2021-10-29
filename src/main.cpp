#include <Arduino.h>
#include <M5Stack.h>
#include <WiFi.h>
#include <time.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Vector.h>

#include "pir.h"
#include "co2.h"
#include "const.local.h"
#include "printMsg.h"

StaticJsonDocument<256> doc;
StaticJsonDocument<256> dataDoc;

float maxNotesCount[100];
typedef Vector<float> Notes;
typedef Vector<float> Duration;
Notes notes_vector;
Duration dur_vector;

void setupM5() {
  M5.begin(115200);
  M5.Power.begin();
  M5.Speaker.begin();
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 10);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2.5);
}

void addNote(String key, float ms, bool isSharp = false, bool high = true) {
  int freq = 0;
  if (key == "C") {
    if (high) {
      if (isSharp) {
        freq = 554.37;
      }
      else {
        freq = 523.25;  
      } 
    }
    else {
      if (isSharp) {
        freq = 277.18;
      }
      else {
        freq = 261.63;
      }
    }  
  }
  else if (key == "D") {
      if (high) {
        if (isSharp) {
          freq = 622.25;
        }
        else {
          freq = 587.33; 
        }
      }
      else {
        if (isSharp) {
          freq = 311.13;
        }
        else {
          freq = 293.66;
        }
      }
  }
  else if (key == "E") {
      if (high) {
        freq = 659.25;
      }
      else {
        freq = 329.63;
      }
  }
  else if (key == "F") {
    if (high) {
        if (isSharp) {
          freq = 739.99;
        }
        else {
          freq = 698.46; 
        }
      }
      else {
        if (isSharp) {
          freq = 369.99;
        }
        else {
          freq = 349.23;
        }
      }
  }
  else if (key == "G") {
          if (high) {
        if (isSharp) {
          freq = 830.61;
        }
        else {
          freq = 783.99; 
        }
      }
      else {
        if (isSharp) {
          freq = 415.30;
        }
        else {
          freq = 392.00;
        }
      }
  }
  else if (key == "A") {
          if (high) {
        if (isSharp) {
          freq = 932.33;
        }
        else {
          freq = 880.00; 
        }
      }
      else {
        if (isSharp) {
          freq = 466.16;
        }
        else {
          freq = 440.00;
        }
      }
  }
  else if (key == "B") {
    if (high) {
      freq = 987.77;
    }
    else {
      freq = 493.88;
    }
  }
  Serial.println(freq);
  notes_vector.push_back(freq);
  dur_vector.push_back(ms);
}

void playCurrentTune() {
  for(int i = 0; i < notes_vector.size(); i++) {
    Serial.println(notes_vector[i]);
    Serial.println(dur_vector[i]);
    // M5.Speaker.tone(notes_vector[i], dur_vector[i]);
    // delay(dur_vector[i]);
    // M5.Speaker.end();
  }
}

void playGiorno() {
  addNote("F", 500, true);
  addNote("F", 500, false);
  delay(200);
  addNote("D", 100);
  addNote("E", 100);
  addNote("F", 200);
  addNote("E", 200);
  addNote("D", 100);
  addNote("C", 200, true);
  addNote("D", 200);
  addNote("E", 200);
  playCurrentTune();
}

// void playRickRoll() {
//   addNote(207.65,100);
//   addNote(233.08,100);
//   addNote(277.18,100);
//   addNote(233.08,100);
//   addNote(349.23,250,150);
//   addNote(349.23,250,150);
//   addNote(311.13,400);

//   delay(400);

//   addNote(207.65,100);
//   addNote(233.08,100);
//   addNote(277.18,100);
//   addNote(233.08,100);
//   addNote(311.13,250,150);
//   addNote(311.13,250,150);
//   addNote(277.18,400);
//   delay(400);
//   addNote(261.63,100);
//   addNote(233.08,100);
// }

void printLocalTime()
{
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    M5.Lcd.println("Failed to obtain time");
    return;
  }
  M5.Lcd.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
}

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

String generateLogJson(String id, String type, String val, int timestamp, String UTCTimestamp, String deviceId) {
  JsonObject root = doc.to<JsonObject>();
  JsonObject data = dataDoc.to<JsonObject>();
  data["id"] = id;
  data["type"] = type;
  data["val"] = val;
  root["unixTimestamp"] = timestamp;
  root.createNestedArray("data");
  root["data"].add(data);
  root["UTCTimestamp"] = UTCTimestamp;
  root["deviceId"] = deviceId;
  String payload;
  serializeJson(doc, payload);
  return payload;
}

void beginConnect(HTTPClient &http, String url = "https://api.bagtower.bag-era.fr/prod/logs") {
  http.begin(url);
  http.addHeader("Content-type", "application/json");
  http.addHeader("x-api-key", X_API_KEY);
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

void setup() {
  setupM5();
  notes_vector.setStorage(maxNotesCount);
  dur_vector.setStorage(maxNotesCount);
  setup_wifi();
  playGiorno();
  configTime(3600, 3600, NTP_SERVER);
  printLocalTime();
  HTTPClient http;
  beginConnect(http);
  String payload = generateLogJson("title", "string", "value", 0, "now", DEVICE_ID);
  printMsg(payload);
  int httpCode = http.POST(payload);

  co2_sensor_setup();
  pir_sensor_setup();

  if (httpCode >= 200 && httpCode < 300) {
    String content = http.getString();
    printMsg(content);
  }
  else {
    printMsg("error");
  };
  setupScreenDisplay();
}

void loop() {
  Serial.println("eho");
  // M5.Lcd.fillScreen(BLACK);
  // M5.Lcd.setCursor(0, 0);

  // M5.Lcd.println("Connected to the WiFi network");
  // M5.Lcd.println(SSID);
  // M5.Lcd.println("\nAdresse IP : ");
  // M5.Lcd.println(WiFi.localIP());
  M5.Lcd.setCursor(10, 80);
  M5.Lcd.fillRect(10, 80, 100, 34, BLACK);
  printLocalTime();
  // M5.Lcd.fillScreen(BLACK);
  // M5.Lcd.setCursor(0, 0);

  co2_sensor_init();
  pir_sensor_init();
  delay(1000);
}
