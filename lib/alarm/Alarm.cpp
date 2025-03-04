#include "Alarm.h"
#include "SPIFFS.h"
#include "Config.h"

Alarm::Alarm(uint8_t BCLK, uint8_t LRC, uint8_t DOUT, Audio* audioC) {
    this->audio = audioC;


    Serial.println("Configuring audio");
    Serial.printf("I2S_BCLK: %d, I2S_LRC: %d, I2S_DOUT: %d\n", BCLK, LRC, DOUT);
    this->audio->setPinout(BCLK, LRC, DOUT);
    this->audio->setVolume(AUDIO_VOLUME);

    if (!SPIFFS.begin(true)) {
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }
}

void Alarm::ring(void) {
    if (this->xHandle == NULL) {  
        xTaskCreate(Alarm::loop, "AlarmTask", 8192, this, 5, &this->xHandle);
        this->isPlaying = true;  // Indiquer que la lecture commence
        Serial.println("Alarm task started.");
    } else {
        Serial.println("Alarm task already running.");
    }
}


void Alarm::loop(void *param) {
    Alarm *alarm = (Alarm *)param;  // Convertir le pointeur générique en `Alarm*`

    while (true) {
        if (alarm->audio) {
            alarm->audio->loop();  // Lire l'audio en continu

            // Vérifier si la lecture est terminée et relancer le MP3
            if (!alarm->audio->isRunning() && alarm->isPlaying) {
                Serial.println("MP3 terminé, relancement...");
                alarm->restart();
            }
        }
        vTaskDelay(pdMS_TO_TICKS(10));  // Pause pour éviter de saturer le CPU
    }
}



void Alarm::stop(void) {
    if (this->xHandle != NULL) {  
        vTaskDelete(this->xHandle);
        this->xHandle = NULL;  
        this->isPlaying = false;  // Indiquer que l'audio est stoppé
        Serial.println("Alarm task stopped.");
    } else {
        Serial.println("No alarm task to stop.");
    }
}


void Alarm::restart() {
    Serial.println("Relancement du MP3...");
    this->audio->connecttoFS(SPIFFS, SOUND_FILEPATH.c_str());  // Relancer la lecture
    this->isPlaying = true;
}


