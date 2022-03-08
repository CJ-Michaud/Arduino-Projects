// This program fades an led based on the value coming from the Analog Input 

// declaring variable. One analog input, one analog output, and two empty variables
int analogValue = A0;
int a;
int b;
int led = 11;                                // the analog output has to be a pin with PWM capability

void setup() {

}

void loop() {
a = analogRead(analogValue);                // reads the value from Analog 0
b = map(a, 0, 1023, 0, 255);                // The map function takes the values coming from Analog 0 which can be between 0 and 1023
                                            // and converts it into values from 0 to 255 

analogWrite(11, b);                         // maps the value coming from variable b and writes it to the led 

}
