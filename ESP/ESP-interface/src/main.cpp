#include <Arduino.h>

// Initialize the ADC pin
const int ADCPin = A0;
int potVal = 0;

// Initialize Select switches
const int SelectPin1 = 5;
const int SelectPin2 = 4;

// Initialize set button
const int SetButton = 0;

// Initialize the output LED pins
const int LEDPin1 = 15;
const int LEDPin2 = 13;
const int LEDPin3 = 12;
const int LEDPin4 = 14;

// Timer Delays
int delay1 = 1000;
int delay2 = 1000;
int delay3 = 1000;
int delay4 = 1000;

// Timer State
int timerCount = millis ();
int currentMillis = millis ();

int LEDstate = 0;

void setup ()
{
  // Initialize serial communication
  Serial.begin ( 9600 );

  // Set the Select pins as input
  pinMode ( SelectPin1, INPUT );
  pinMode ( SelectPin2, INPUT );

  // Set the set button as input
  pinMode ( SetButton, INPUT );

  // Set the LED pins as output
  pinMode ( LEDPin1, OUTPUT );
  pinMode ( LEDPin2, OUTPUT );
  pinMode ( LEDPin3, OUTPUT );
  pinMode ( LEDPin4, OUTPUT );

  // Set the ADC pin as input
  pinMode ( ADCPin, INPUT );
}

void loop ()
{
  // Read from the ADC pin
  potVal = analogRead ( ADCPin );

  // Read from the Select pins
  int S1 = digitalRead ( SelectPin1 );
  int S2 = digitalRead ( SelectPin2 );

  // Print the values to the serial monitor
  Serial.print ( potVal );
  Serial.print ( " " );
  Serial.print ( S1 );
  Serial.print ( " " );
  Serial.print ( S2 );
  Serial.print ( " " );
  Serial.println ( digitalRead ( SetButton ) );

  // Have the select pins control the LEDs when the set button is pressed
  if ( digitalRead ( SetButton ) == LOW )
  {
    if ( S1 == LOW && S2 == LOW )
      delay1 = potVal;
    else if ( S1 == LOW && S2 == HIGH )
      delay2 = potVal;
    else if ( S1 == HIGH && S2 == LOW )
      delay3 = potVal;
    else if ( S1 == HIGH && S2 == HIGH )
      delay4 = potVal;
  }

  currentMillis = millis ();

  if ( LEDstate % 4 == 0 )
  {
    if ( currentMillis >= timerCount + delay1 )
    {
      digitalWrite ( LEDPin2, HIGH );
      digitalWrite ( LEDPin1, LOW );
      timerCount = millis ();
      LEDstate += 1;
    }
  }
  else if ( LEDstate % 4 == 1 )
  {
    if ( currentMillis >= timerCount + delay2 )
    {
      digitalWrite ( LEDPin3, HIGH );
      digitalWrite ( LEDPin2, LOW );
      timerCount = millis ();
      LEDstate += 1;
    }
  }
  else if ( LEDstate % 4 == 2 )
  {
    if ( currentMillis >= timerCount + delay3 )
    {
      digitalWrite ( LEDPin4, HIGH );
      digitalWrite ( LEDPin3, LOW );
      timerCount = millis ();
      LEDstate += 1;
    }
  }
  else if ( LEDstate % 4 == 3 )
  {
    if ( currentMillis >= timerCount + delay4 )
    {
      digitalWrite ( LEDPin1, HIGH );
      digitalWrite ( LEDPin4, LOW );
      timerCount = millis ();
      LEDstate += 1;
    }
  }
  
  // Delay for 10 ms
  delay ( 10 );
}