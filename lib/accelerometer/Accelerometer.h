#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <Arduino.h>
#include <Wire.h>

class Accelerometer {
    private:
        static Accelerometer* instance;
        void i2c_write(uint8_t slave_addr, uint8_t reg, uint8_t val);
        
    public: 
        Accelerometer();
        void i2c_read_multiple_bytes(uint8_t slave_addr, uint8_t reg, uint8_t *buff, size_t len);

};

#endif
