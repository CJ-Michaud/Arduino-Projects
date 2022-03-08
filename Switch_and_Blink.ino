// This program will turn blink an LED while simultaniously turning on and off an LED depending on the state of a push button


// declaring variables. Two LED's, the state of one LED and push button, and the push button itself

int ledState;             
int button = 10;
int buttonState;
int led2 = 11;
const int ledPin =  LED_BUILTIN; 

unsigned long previousMillis = 0;                        // will store last time LED was updated

const long interval = 1000;                              // interval at which to blink (milliseconds)

void setup() {
  
  pinMode(ledPin, OUTPUT);                               // sets the built in LED as an output
  pinMode(button, INPUT_PULLUP);                         // sets the button as a input with a built in resistor
  pinMode(led2, OUTPUT);                                 // sets the other LED as an output
}

void loop() {

buttonState =! digitalRead(button);                      // reads the value of the button
if (buttonState == HIGH){                                // if the button is pressed, turn on the LED
  digitalWrite(led2, HIGH); 
  }
else{
    digitalWrite(led2, LOW);                             // if the button is not pressed, turn off the LED
    }
    
 
  unsigned long currentMillis = millis();                // check to see if it's time to blink the LED; that is, if the difference
                                                         // between the current time and last time you blinked the LED is bigger than
                                                         // the interval at which you want to blink the LED.
 
  if (currentMillis - previousMillis >= interval) {
   
    previousMillis = currentMillis;                      // saves the last time the LED was blinked

   
    if (ledState == LOW) {                               // if the LED is off turn it on and if the LED is off turn it on:
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

   
    digitalWrite(ledPin, ledState);                      // set the LED with the ledState of the variable:
  }
}
