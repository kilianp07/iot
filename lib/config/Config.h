#ifndef CONFIG_H
#define CONFIG_H

// WiFi credentials
const String WIFI_SSID = "";
const String WIFI_PASSWORD = "";

const uint8_t AUDIO_VOLUME = 5;

const String SOUND_FILEPATH = "/sound/alarm.mp3";



// I2S Pin assignments for XIAO ESP32C3
#define SPI_MOSI       7   // SPI MOSI
#define SPI_SCK        6   // SPI SCK
#define I2S_DOUT       4   // I2S data out
#define I2S_BCLK       5   // I2S bit clock
#define I2S_LRC        3   // I2S left-right clock


// Modem Related
#define MODEM_RX_PIN 7
#define MODEM_TX_PIN 6

#define APN "TM"
#define USER ""
#define PASS ""

#define PHONE_NUMBER "+33"

#endif