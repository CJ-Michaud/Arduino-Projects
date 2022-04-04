#include <Servo.h>     // includes the library to use servo motors

Servo myservo;   // creating a servo in the program
int joystick;    // declaring a variale to use as out joystick
int val;         // declaring a variable to use the values coming from the joystick

void setup() {
myservo.attach(10);     // attaches the servo to pin 10 of the arduino
Serial.begin(9600);     // setup to use the serial monitor 
}

void loop() {
joystick = analogRead(A0);                // the "joystick" variable reads the value coming from analog 0
val = map(joystick, 0, 1023, 0, 180);     // takes the bit values from joystick (0 - 1023) and converts it to 0 - 180 degrees and stores the value in the variable "val" 
myservo.write(val);                       // writes the value of "val" to the servo motor
delay(15);                                // delay used to give the servo motor time to the reach the angle specified 

}
