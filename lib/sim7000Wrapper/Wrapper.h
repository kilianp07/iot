#ifndef WRAPPER_H
#define WRAPPER_H

#include <Arduino.h>
#define TINY_GSM_MODEM_SIM7080
#include <TinyGsmClient.h>
#include <ArduinoHttpClient.h>

class SIM7000Wrapper {
private:
    HardwareSerial *serial;
    TinyGsm modem;
    TinyGsmClient client;
    HttpClient http;
    uint8_t rxPin, txPin, pwrKeyPin;
    bool isPoweredOn = false;
    const char* apn;
    const char* user;
    const char* pass;
    bool sendSMS(const String &phoneNumber, const String &message);

public:
    SIM7000Wrapper(HardwareSerial &serialPort, uint8_t rx, uint8_t tx, 
                   const char* server, int port, const char* apn, const char* user, const char* pass);

    bool begin();
    void sendsms(const String &phoneNumber, const String &message);
    String httpRequest(const String &url, const String &payload, const String &method, bool useHTTPS);
};

#endif