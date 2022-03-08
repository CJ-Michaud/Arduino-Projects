
// This program will turn on and off an LED based on the value of a pushbutton


// declaring two variables. An Push Button (Digital Input) and LED (Digital Output)
int pushButton = 2;
int led = 13;

void setup() {
  Serial.begin(9600);                                 // initialize serial communication at 9600 bits per second:
  pinMode(pushButton, INPUT_PULLUP);                  // make the pushbutton's pin an input
  pinMode(led, OUTPUT);                               // make the led's pin an output
}

void loop() {
  int buttonState =! digitalRead(pushButton);         // read the input pin and saves its value to a variable named "buttonState"
  Serial.println(buttonState);                        // prints out the state of the button:
  delay(1);                                           // delay in between reads for stability
  if (buttonState == HIGH) {                          // If the buttonstate's value is read as 'HIGH', the led will turn on.   
    digitalWrite(led, HIGH);
  }
  else {
    digitalWrite(led, LOW);                           // If the buttonstate's value is read as 'LOW', the led will turn off.
  }
  }
 
