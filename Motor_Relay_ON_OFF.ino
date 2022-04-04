const int pushbutton = 8;             // declaring a variable to use as our pushbutton assigning to pin 8 on the arduino
const int coil = 9;                   // declaring a variable to use to activate the coil of the relay assigning to pin 9 on the arduino

int coilstate = LOW;                  // declaring a variable to control the state of the coil on the relay
int lastbstate;                       // declaring a variable to record the last state of the pushbutton
int currentbstate;                    // declaring a variable to record the current state of the pushbutton

void setup() {
pinMode(pushbutton, INPUT_PULLUP);     // setting the pushbutton as an input. Pullup uses the internal resistances from the arduino
pinMode(coil, OUTPUT);                 // sets coil (pin 9) as an output
}

void loop() {
 currentbstate = lastbstate;                             // sets currentbstate equal to lastbstate
 currentbstate = digitalRead(pushbutton);                // reads whether the pushbutton has been pressed and saves its value to currentbstate
 if(currentbstate = HIGH and lastbstate = LOW){          // if the pushbutton is pressed, currentbstate will be changed. If "currentbstate" is the opposite of "lastbstate",
 coilstate = !coilstate;                                 // the "coilstate" will be set to the opposite of itself. This will toggle from HIGH to LOW
 }

digitalWrite(coil, coilstate);                // turn the output named "coil" on depending on the value of "coilstate". This will toggle the relay coil ON and OFF
}
