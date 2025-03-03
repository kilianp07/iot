#include "PositionClient.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

PositionClient::PositionClient(const char* serverUrl) : _serverUrl(serverUrl) {}

void PositionClient::postPosition(const Position& pos) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(_serverUrl);
        http.addHeader("Content-Type", "application/json");

        StaticJsonDocument<200> jsonDoc;
        jsonDoc["latitude"] = pos.latitude;
        jsonDoc["longitude"] = pos.longitude;

        String jsonString;
        serializeJson(jsonDoc, jsonString);

        int httpResponseCode = http.POST(jsonString);
        Serial.print("Réponse du serveur: ");
        Serial.println(httpResponseCode);

        http.end();
    } else {
        Serial.println("WiFi non connecté");
    }
}
