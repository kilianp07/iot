#include <Arduino.h>
#include "Config.h"
#include "SPIFFS.h"
#include "Audio.h"
#include "Alarm.h"
#include "WiFiMulti.h"


WiFiMulti wifiMulti;
Alarm *my_alarm;
Audio audioC;


void setup() {
    Serial.begin(115200);
    my_alarm = new Alarm(uint8_t(I2S_BCLK),uint8_t(I2S_LRC), uint8_t(I2S_DOUT), &audioC);
}

void loop()
{
    my_alarm->ring();
    delay(10000);
    my_alarm->stop();
}

// optional
void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}
void audio_id3data(const char *info){  //id3 metadata
    Serial.print("id3data     ");Serial.println(info);
}

void audio_showstation(const char *info){
    Serial.print("station     ");Serial.println(info);
}
void audio_showstreamtitle(const char *info){
    Serial.print("streamtitle ");Serial.println(info);
}
void audio_bitrate(const char *info){
    Serial.print("bitrate     ");Serial.println(info);
}
void audio_commercial(const char *info){  //duration in sec
    Serial.print("commercial  ");Serial.println(info);
}
void audio_icyurl(const char *info){  //homepage
    Serial.print("icyurl      ");Serial.println(info);
}
void audio_lasthost(const char *info){  //stream URL played
    Serial.print("lasthost    ");Serial.println(info);
}
