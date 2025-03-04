#include <Arduino.h>
#include <Config.h>
#include <SPIFFS.h>
#include <Audio.h>
#include <Alarm.h>
#include <Wrapper.h>
#include <Accelerometer.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <PositionClient.h>

Alarm *my_alarm;
Audio audioC;
Accelerometer *accelerometer;
uint8_t buff;
HardwareSerial simSerial(1);
SIM7000Wrapper modem(simSerial, MODEM_RX_PIN, MODEM_TX_PIN, "", 0, APN, USER, PASS);
TinyGPSPlus gps;
HardwareSerial gpsSerial(2);
PositionClient positionClient;
Position position;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  delay(3000);
  Serial.println("---SETUP---");
  delay(1000);
  Serial.println("Starting alarm....");
  my_alarm = new Alarm(uint8_t(I2S_BCLK), uint8_t(I2S_LRC), uint8_t(I2S_DOUT), &audioC);
  delay(1000);
  Serial.println("Starting accelerometer...");
  accelerometer = new Accelerometer(); 
  delay(1000);
  Serial.println("Starting modem...");
  modem.begin();
  delay(1000);
  Serial.println("Starting gps...");
  gpsSerial.begin(9600, SERIAL_8N1, D7, D6);

  Serial.println("---LOOP---");
}

void loop() {
  accelerometer->i2c_read_multiple_bytes(ADXL_ADDR, INT_SOURCE, &buff, 1);
  if (buff == MOVEMENT_DETECTED) {
    Serial.println("The accelerometer moved");
    my_alarm->ring();
    modem.sendsms(PHONE_NUMBER, MESSAGE);
    Serial.println("Récupération des coordonnées GPS");
    if (gpsSerial.available() > 0) {
      if (gps.encode(gpsSerial.read())) {
        Serial.println(gps.location.lat());
        Serial.println(gps.location.lng());
        position.latitude = gps.location.lat();
        position.longitude = gps.location.lng();
        String data = positionClient.postPosition(position);
        modem.httpRequest(APIURL, String(data), "POST", false);
      }
    }
    delay(1000);
    my_alarm->stop();
    accelerometer->i2c_read_multiple_bytes(ADXL_ADDR, INT_SOURCE, &buff, 1);
  }
  delay(100);
}
