#include <Arduino.h>
#include "Config.h"
#include "SPIFFS.h"
#include "Audio.h"
#include "Alarm.h"
#include "WiFiMulti.h"
#include "Wrapper.h"




WiFiMulti wifiMulti;
Alarm *my_alarm;
Audio audioC;
HardwareSerial simSerial(1);
SIM7000Wrapper modem(simSerial, MODEM_RX_PIN, MODEM_TX_PIN, "", 0, APN, USER, PASS);

void setup() {
    Serial.begin(115200);
    my_alarm = new Alarm(uint8_t(I2S_BCLK),uint8_t(I2S_LRC), uint8_t(I2S_DOUT), &audioC);
    modem.begin();
}

void loop()
{
}

