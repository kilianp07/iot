#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

class Accelerometer {
    private:
        void i2c_write(uint8_t slave_addr, uint8_t reg, uint8_t val);
        void i2c_read_multiple_bytes(uint8_t slave_addr, uint8_t reg, uint8_t *buff, size_t len);
    public: 
        Accelerometer();
        void start_adxl();
        void moved();
        volatile bool g_moved;        
};

#endif