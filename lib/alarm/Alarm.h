#ifndef ALARM_H
#define ALARM_H

#include "Audio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

class Alarm {
    private:
        Audio* audio;
        TaskHandle_t xHandle = NULL;
        bool isPlaying = false;
        static void loop(void *param);  
    public:
        Alarm(uint8_t BCLK, uint8_t LRC, uint8_t DOUT, Audio* audio);
        void stop(void);
        void restart();
        void ring(void);
};

#endif
