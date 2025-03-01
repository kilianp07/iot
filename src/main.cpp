#include <Arduino.h>
#include <Config.h>
#include <SPIFFS.h>
#include <Audio.h>
#include <Alarm.h>
#include <Wrapper.h>
#include <Accelerometer.h>
#include <Wire.h>
#include <TinyGPS++.h>


Alarm *my_alarm;
Audio audioC;
HardwareSerial simSerial(1);
SIM7000Wrapper modem(simSerial, MODEM_RX_PIN, MODEM_TX_PIN, "", 0, APN, USER, PASS);
Accelerometer *accelerometer;
TinyGPSPlus gps;
HardwareSerial gpsSerial(2);
uint8_t buff;


void setup() {
  Serial.begin(115200);
  Wire.begin();

  Serial.println("Starting GPS");
  gpsSerial.begin(9600, SERIAL_8N1, D7, D6);
  if (gpsSerial.available() > 0) {
    Serial.write("GPS Ready");
  } else {
    Serial.println("WARNING: GPS not responding");
  }
  
  Serial.println("Starting alarm");
  my_alarm = new Alarm(uint8_t(I2S_BCLK), uint8_t(I2S_LRC), uint8_t(I2S_DOUT), &audioC);
 
  Serial.println("Starting accelerometer");
  accelerometer = new Accelerometer(); 

  Serial.println("Starting modem");
  // modem.begin();
  
  delay(200);
}

void loop()
{
  accelerometer->i2c_read_multiple_bytes(ADXL_ADDR, INT_SOURCE, &buff, 1);
  if (buff == MOVEMENT_DETECTED) {
    Serial.println("The accelerometer moved.");
    Serial.print(gpsSerial.read());
    my_alarm->ring();
    // modem.sendsms(PHONE_NUMBER, MESSAGE);
    delay(10000);
    my_alarm->stop();
    // On lit l'adresse pour éviter de relancer directement la boucle 
    accelerometer->i2c_read_multiple_bytes(ADXL_ADDR, INT_SOURCE, &buff, 1);
  }
  delay(10);
}

