#ifndef POSITIONCLIENT_H
#define POSITIONCLIENT_H

#include <Arduino.h>
#define TINY_GSM_MODEM_SIM7080
#include <TinyGsmClient.h>
#include <Client.h>
#include <ArduinoHttpClient.h>

struct Position {
    float latitude;
    float longitude;
};

class PositionClient {
public:
    size_t postPosition(const Position& pos);
};


#endif // POSITIONCLIENT_H
