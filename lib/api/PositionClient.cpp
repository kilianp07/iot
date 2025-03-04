#include "PositionClient.h"
#include <WiFi.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include <Client.h>

String PositionClient::postPosition(const Position& pos) {
    StaticJsonDocument<200> jsonDoc;
    jsonDoc["latitude"] = pos.latitude;
    jsonDoc["longitude"] = pos.longitude;

    String jsonString;
    serializeJson(jsonDoc, jsonString);
    return jsonString;
}
