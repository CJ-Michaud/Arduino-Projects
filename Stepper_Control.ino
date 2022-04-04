#include <Stepper.h> // library to use the stepper motor driver

int joystick;                 // declaring a variable to control a joystick
int previous = 0;             // declared a variable to recored the previous step

#define STEPS 2038                // defines the maximum amount of steps. The stepper motor has 2038 steps!

Stepper mystepper(STEPS, 8, 9, 10, 11);         // function used to connects the poles of the stepper motor to the arduino pins

void setup() {
Serial.begin(9600);                   // used to setup the serial monitor
mystepper.setSpeed(30);               // sets the maximum RPM of the stepper motor
}

void loop() {

joystick = analogRead(A0);              // reads the values coming from analog 0 and stores the value in "joystick"
mystepper.step(joystick - previous);    // determines how much the stepper motor steps. Its steps in increments of the joystick value - the value previously stored 
previous = joystick;                    // set the previous value equal to the value of the joystick 
Serial.println(joystick);               // serial print the value coming from the joystick
}
