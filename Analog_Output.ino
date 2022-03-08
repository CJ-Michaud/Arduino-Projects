// This program fades an led depending on the value of a variable

// declaring variables. Two empty variables and an analog output
int a; 
int b;
int led = 11; // must use an PWM pin for this program to work

void setup() {
  // no setup needed

}

void loop() {  
for (int a = 0; a <=255; a++){       // This for loop runs only if variable a is equal to 0. 
  analogWrite(led, a);               // Once that condition is met, variable a increments by 1 until a is equal to 256. 
                                     // The loops writes the value of variable a for every increment which turns on the led a little at a time  
  delay(10);                         // A delay is needed in order to see the fade
  }
}
