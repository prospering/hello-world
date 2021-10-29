#include <Arduino.h>
#include <HTTPClient.h>
#include <M5Stack.h>

void beginConnect(HTTPClient &http, String url = "https://api.bagtower.bag-era.fr/prod/logs");

void send_data_to_API(String payload);

