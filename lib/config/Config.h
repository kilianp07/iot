#ifndef CONFIG_H
#define CONFIG_H

// WiFi credentials
const String WIFI_SSID = "";
const String WIFI_PASSWORD = "";

const uint8_t AUDIO_VOLUME = 5;

const String SOUND_FILEPATH = "/sound/alarm.mp3";



// I2S Pin assignments for XIAO ESP32C3
// #define SPI_MOSI       7   // SPI MOSI
// #define SPI_SCK        6   // SPI SCK
#define I2S_DOUT       9   // I2S data out
#define I2S_BCLK       8   // I2S bit clock
#define I2S_LRC        7   // I2S left-right clock

// ADXL345
#define ADXL_ADDR     0x53
#define POWER_CTL     0x2D
#define DEVICE_ID     0x00
#define THRESH_ACT    0x24 
#define ACT_INACT_CTL 0x27
#define INT_SOURCE    0x30
#define INT_ENABLE    0x2E
#define DATA_X0       0x32

#define MOVED_OUTPUT  D2


// Modem Related
#define MODEM_RX_PIN 7
#define MODEM_TX_PIN 6

#define APN "TM"
#define USER ""
#define PASS ""

#define PHONE_NUMBER "+33"

#endif