#ifndef POSITIONCLIENT_H
#define POSITIONCLIENT_H

#include <Arduino.h>

struct Position {
    float latitude;
    float longitude;
};

class PositionClient {
public:
    PositionClient(const char* serverUrl);
    void postPosition(const Position& pos);

private:
    const char* _serverUrl;
};

#endif // POSITIONCLIENT_H
