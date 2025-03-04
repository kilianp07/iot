#include "PositionClient.h"
#include <WiFi.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include <Client.h>

size_t PositionClient::postPosition(const Position& pos) {
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["latitude"] = pos.latitude;
    jsonDoc["longitude"] = pos.longitude;

    String jsonString;
    return serializeJson(jsonDoc, jsonString);
}
