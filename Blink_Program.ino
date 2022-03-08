int red = 11;

// declaring variable and assigning it to pin 11 on the arduino board

void setup() {
  pinMode(red, OUTPUT);

// configuring the variable (arduino pin) to function as a digital output
}

void loop() {
  digitalWrite(red, LOW);        // turns OFF the red led
  delay(500);                    // delays the program for 500 milliseconds
  digitalWrite(red, HIGH);       // turns ON the red led
  delay(500);                    // delays the program for 500 milliseconds
}
