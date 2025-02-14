#include <Arduino.h>
#include <Wire.h>
#include <Accelerometer.h>
#include "Config.h"

volatile bool g_moved = false;

Accelerometer::Accelerometer() {
    uint8_t buff;

    this->i2c_read_multiple_bytes(ADXL_ADDR, DEVICE_ID, &buff, 1);
    if (!buff) {
        Serial.println("An Error has occurred while mounting ADXL345 (Accelerometer).");
        return;
    } else {
        Serial.println("Accelerometer find.");
    }
}

void Accelerometer::i2c_write(uint8_t slave_addr, uint8_t reg, uint8_t val) {
    Wire.beginTransmission(slave_addr);
    Wire.write(reg);
    Wire.write(val);
    Wire.endTransmission();
}
void Accelerometer::i2c_read_multiple_bytes(uint8_t slave_addr, uint8_t reg, uint8_t *buff, size_t len) {
    Wire.beginTransmission(slave_addr);
    Wire.write(reg);
    Wire.endTransmission();
  
    Wire.requestFrom(slave_addr, len);
    Wire.readBytes(buff, len);
}

void Accelerometer::moved() {
    g_moved = true;
}

void Accelerometer::start_adxl() {
    uint8_t buff;
  
    // On réveille le module
    i2c_read_multiple_bytes(ADXL_ADDR, POWER_CTL, &buff, 1);
    i2c_write(ADXL_ADDR, POWER_CTL, buff | 0b00001000);
  
    // On définit la value pour détecter l'activity
    i2c_write(ADXL_ADDR, THRESH_ACT, 0b00011000);
  
    // On enable les 3 axes
    i2c_write(ADXL_ADDR, ACT_INACT_CTL, 0b01110000);
  
    // On enable l'activity
    i2c_read_multiple_bytes(ADXL_ADDR, INT_ENABLE, &buff, 1);
    i2c_write(ADXL_ADDR, INT_ENABLE, buff | 0b00010000);
    
    // On lit la valeur au démarrage pour ne pas déclancher l'alerte de suite
    i2c_read_multiple_bytes(ADXL_ADDR, INT_SOURCE, &buff, 1);
  }

