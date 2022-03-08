// this program will turning on and off three LED's in a line.  

int green = 13;  
int yellow = 12;
int red = 11;

// declaring variables and assigning them to pins on the arduino board

void setup() {
  pinMode(green, OUTPUT); 
  pinMode(yellow, OUTPUT);
  pinMode(red, OUTPUT);

// configuring the variables (arduino pins) to function as digital outputs
}

void loop() {
  digitalWrite(green, HIGH);     // turns ON the arduino pin assosiated with the variable "green"
  digitalWrite(red, LOW);        // turns OFF the arduino pin assosiated with the variable "red"
  delay(500);                    // delays the program for 500 milliseconds
  digitalWrite(yellow, HIGH);    // turns ON arduino pin assosiated with the variable "yellow"
  digitalWrite(green, LOW);      // turns OFF the arduino pin assosiated with the variable "green"
  delay(500);                    // delays the program for 500 milliseconds
  digitalWrite(red, HIGH);       // turns ON the arduino pin assosiated with the variable "red"
  digitalWrite(yellow, LOW);     // turns OFF the arduino pin assosiated with the variable "yellow"
  delay(500);                    // delays the program for 500 milliseconds         
  
}
