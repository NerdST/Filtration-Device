#include <Arduino.h>

// Initialize the ADC pin
const int ADCPin = A0;
int potVal = 0;

// Initialize the output LED pin
const int LEDPin = 13;

// LED Blink Timer
unsigned long previousMillis = 0;
long interval = 1000;

void setup ()
{
  // Initialize serial communication
  Serial.begin ( 9600 );

  // Set the LED pin as an output
  pinMode ( LEDPin, OUTPUT );
}

void loop ()
{
  // Read from the ADC pin
  potVal = analogRead ( ADCPin );

  // Have the LED blink with potVal ms interval
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    digitalWrite(LEDPin, !digitalRead(LEDPin));
    interval = potVal;
  }

  // Delay for 100ms
  delay ( 10 );
}