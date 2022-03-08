// This program determines the resistance of an unknown resistor and displays it on both the serial monitor and an LCD

// library needed to use the LCD
#include <LiquidCrystal.h>

// declaring arduino pins needed to use the LCD
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // function needed to use the LCD

byte ohm[8] = { // A 5*7 array used to create the Ohm symbol to be displayed on the LCD 
  0b01110,
  0b10001,
  0b10001,
  0b10001,
  0b01010,
  0b01010,
  0b10001,
  
  };

/* declaring more variables. One analog input, one empty variable, a slope variable, 
and variables that represent the known and unknown resistance, voltage of the known resistor, and total current */
 
float voltMeter = A0;
float slope = 5.0/1023.0;
float R1 = 10000.0;
float R2 = 0.0;
int x = 0;
float voltage_R1 = 0.0;
float current = 0.0;

void setup() {
Serial.begin(9600);                    // initializing serial communication at 9600 bits per second
lcd.begin(16,2);                       // initializing the LCD display which is a 16*2 box array
lcd.createChar(1, ohm);                // initializing our custom ohm character to be used in the LCD
}

void loop() {
x = analogRead(voltMeter);             // Reads the value coming from Analog 0
voltage_R1 = x * slope;                // Takes the value coming from Analog 0 and reads it as a voltage
current = (5 - voltage_R1)/R1;         // Formula to find the total current in the circuit
R2 = (voltage_R1)/current;             // Formula to find the value of the unknown resistor
Serial.print(voltage_R1);              // Displays the voltage of Resistor 1 on the serial monitor
Serial.print("\t");                    // Creates a space on the serial monitor
Serial.println(R2);                    // Displays the resistance of Resistor 2 on the serial monitor and presses enter
lcd.setCursor(0,0);                    // Tells the cursor to start typing on the LCD starting from the 0,0 position
lcd.print(R2);                         // displays the resistance of Resistor 2 on the LCD
lcd.setCursor(8,0);                    // Tells the cursor to start typing on the LCD starting from the 8,0 position
lcd.write((byte)1);                    // Displays the custom ohm character on the LCD
}
