#include <Arduino.h>
#include <HTTPClient.h>
#include <M5Stack.h>

#include "printMsg.h"
#include "const.h"

HTTPClient http;

void beginConnect(HTTPClient &http, String url = "https://api.bagtower.bag-era.fr/prod/logs") {
  http.begin(url);
  http.addHeader("Content-type", "application/json");
  http.addHeader("x-api-key", X_API_KEY);
}

void send_data_to_API(String payload){
  beginConnect(http);
  int httpCode = http.POST(payload);
  Serial.println("httpcode");
  Serial.println(httpCode);
  if (httpCode >= 200 && httpCode < 300) {
    String content = http.getString();
    printMsg(content);
  }
  else {
    printMsg("error");
  };
}
