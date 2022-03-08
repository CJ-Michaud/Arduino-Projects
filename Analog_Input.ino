// This program will control which led turns on or off as the value of a potentiometer changes.

//declaring variables. One analog input, three digital outputs, and one empty variable.

int analogValue = A0;
float x = 0;
int redLed = 11;
int blueLed = 10;
int greenLed = 9;

void setup() {
}

void loop() {
x = analogRead(analogValue);                // reads the value comimg from Analog 0. The value will be between 0 and 1023

if (x <= 350){                              // If Analog 0 has a value less than 350 it will only turn on the red led 
  digitalWrite(redLed, HIGH); 
  digitalWrite(blueLed, LOW);
  digitalWrite(greenLed, LOW);
  }
if(x > 350 and x <= 700){                   // If Analog 0 has a value between 351 and 700 it will only turn on the blue led 
  digitalWrite(blueLed, HIGH);
  digitalWrite(redLed, LOW);
  digitalWrite(greenLed, LOW);
  }
if (x > 701 and x <=1023){                  // If Analog 0 has a value between 351 and 700 it will only turn on the green led 
  digitalWrite(greenLed, HIGH);
  digitalWrite(blueLed, LOW);
  digitalWrite(redLed, LOW);
  
  }

  }
