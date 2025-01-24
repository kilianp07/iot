#include <Arduino.h>
#include <Adafruit_AHTX0.h>
#ifdef YNOV_ESP
	#include <WiFi.h>
#endif

void setup() {
	// put your setup code here, to run once:
	Serial.begin(115200);
	pinMode(LED_PIN, OUTPUT);
}

void loop() {
	// put your main code here, to run repeatedly:
	digitalWrite(LED_PIN, HIGH);
	delay(500);
	digitalWrite(LED_PIN, LOW);
	delay(500);

#ifdef YNOV_ESP
	Serial.println("I am ESP");
#else
	Serial.println("I am UNO");
#endif
}