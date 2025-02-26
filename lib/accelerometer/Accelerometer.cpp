#include "Accelerometer.h"
#include <Wire.h>
#include "Config.h"
#include <Arduino.h>

Accelerometer* Accelerometer::instance = nullptr;
volatile bool Accelerometer::g_moved = false;

Accelerometer::Accelerometer() {  
    uint8_t buff;
    g_moved = false;

    // Initialisation I2C du capteur
    this->i2c_read_multiple_bytes(ADXL_ADDR, POWER_CTL, &buff, 1);
    this->i2c_write(ADXL_ADDR, POWER_CTL, buff | 0b00001000);
  
    this->i2c_write(ADXL_ADDR, THRESH_ACT, 0b00011000);
    this->i2c_write(ADXL_ADDR, ACT_INACT_CTL, 0b01110000);

    this->i2c_read_multiple_bytes(ADXL_ADDR, INT_ENABLE, &buff, 1);
    this->i2c_write(ADXL_ADDR, INT_ENABLE, buff | 0b00010000);
    
    this->i2c_read_multiple_bytes(ADXL_ADDR, INT_SOURCE, &buff, 1);

    // Affecte l'instance de la classe pour l'utiliser dans la méthode statique
    instance = this;

    pinMode(INT_INPUT, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(INT_INPUT), movedInterruptHandler, RISING);
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

// Fonction statique pour l'interruption
void IRAM_ATTR Accelerometer::movedInterruptHandler() {
    // Vérifie si l'instance est valide et modifie la variable d'état
    if (instance) {
        instance->g_moved = true;
        Serial.println("Interrupt Triggered!");  // Affichage du message lors de l'interruption
    }
}

void Accelerometer::checkInterruptSource() {
    uint8_t buff;
    i2c_read_multiple_bytes(ADXL_ADDR, INT_SOURCE, &buff, 1);
}
