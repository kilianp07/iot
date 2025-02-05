#include <Arduino.h>
#include <I2S.h>
#include <math.h>

const int SAMPLE_RATE = 44100; 
const int AMPLITUDE = 30000;   
const float FREQUENCY = 1000.0; 

void setup() {
  Serial.begin(115200);

  if (!I2S.begin(I2S_PHILIPS_MODE, SAMPLE_RATE, 16)) {
    Serial.println("Erreur : impossible de démarrer l'I2S.");
    while (1);  
  }

  Serial.println("I2S démarré avec succès !");
}

void loop() {
  const int SAMPLES_PER_CYCLE = SAMPLE_RATE / FREQUENCY;  
  int16_t sampleBuffer[SAMPLES_PER_CYCLE * 2];  
  
  for (int i = 0; i < SAMPLES_PER_CYCLE; i++) {
    float theta = (2.0 * M_PI * i) / SAMPLES_PER_CYCLE;
    int16_t sample = (int16_t)(AMPLITUDE * sin(theta));
    
    sampleBuffer[2 * i] = sample;      // Canal gauche
    sampleBuffer[2 * i + 1] = sample;  // Canal droit
  }

  while (true) {
    I2S.write((uint8_t*)sampleBuffer, sizeof(sampleBuffer));
  }
}
