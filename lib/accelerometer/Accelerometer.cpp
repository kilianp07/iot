#include "Accelerometer.h"
#include <Wire.h>
#include "Config.h"
#include <Arduino.h>

Accelerometer::Accelerometer() {  
    uint8_t buff;

    // Initialisation I2C du capteur
    this->i2c_read_multiple_bytes(ADXL_ADDR, POWER_CTL, &buff, 1);
    this->i2c_write(ADXL_ADDR, POWER_CTL, buff | 0b00001000);
  
    this->i2c_write(ADXL_ADDR, THRESH_ACT, 0b00011000);
    this->i2c_write(ADXL_ADDR, ACT_INACT_CTL, 0b01110000);

    this->i2c_read_multiple_bytes(ADXL_ADDR, INT_ENABLE, &buff, 1);
    this->i2c_write(ADXL_ADDR, INT_ENABLE, buff | 0b00010000);
    
    this->i2c_read_multiple_bytes(ADXL_ADDR, INT_SOURCE, &buff, 1);
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
