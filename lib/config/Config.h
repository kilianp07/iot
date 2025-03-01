#ifndef CONFIG_H
#define CONFIG_H

/* 
GPIO1 -> Rien (à éviter)
GPIO2 -> TX Modem 
GPIO3 -> RX Model
GPIO4 -> INT1 ADXL345
SDA   -> ADXL345
SCL   -> ADXL345
TX    -> RX GPS

5V 
GND
3V3 
GPIO9 -> I2S BCLK 
GPIO8 -> I2S DIN
GPIO7 -> I2S LRC
RX    -> TX GPS
*/

// HIBOX3070-K - Speaker (Alarm) :
const uint8_t AUDIO_VOLUME = 5;
const String SOUND_FILEPATH = "/sound/alarm.mp3";
// ESP32S3 - I2S Pin assignments
#define I2S_DOUT      8  // I2S data out
#define I2S_BCLK      9  // I2S bit clock
#define I2S_LRC       7  // I2S left-right clock

// ADXL345 - Accelerometer :
#define ADXL_ADDR     0x53
#define POWER_CTL     0x2D
#define DEVICE_ID     0x00
#define THRESH_ACT    0x24 
#define ACT_INACT_CTL 0x27
#define INT_SOURCE    0x30
#define INT_ENABLE    0x2E
#define DATA_X0       0x32
// ESP32S3 - Pin assignments
#define MOVED_OUTPUT  D3
// + SDA/SCL


// MODEM
#define MODEM_RX_PIN 3
#define MODEM_TX_PIN 2

#define APN "TM"
#define USER ""
#define PASS ""

#define PHONE_NUMBER "+33"
#define MESSAGE "a"

#endif