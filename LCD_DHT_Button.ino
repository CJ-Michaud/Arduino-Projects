// Make sure to include the dht unified sensor library in order for the program to work

#include <LiquidCrystal.h>           // library needed to use to run the liquid crystal display

const int rs = 10, en = 9, d4 = 5, d5 = 4, d6 = 3, d7 = 2;        // setting the pins to setup the liquid crystal display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                        // function to use the pins to turn on and use the liquid crystal display

#include "DHT.h"                          // includes the dht library
#define DHTPIN 8                          // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11                     //  includes the type of DHT sensor
DHT dht(DHTPIN, DHTTYPE);                 // function that creates the dht variable as assigned the pin and type of sensor 

int button = 7;                 // declaring a variable called "button" to use for a pushbutton
float c2f;                      // declaring a variable to use as a formula to calculate the celcius to farenheight

void setup() {

lcd.begin(16,2);                     // needed to activate the lcd. generates a 16 by 2 array
lcd.setCursor(0,0);                  // sets the cursor of the LCD to the 0,0 grid position
lcd.print("Temp: ");                 // prints "Temp: " in the lcd at the 0,0 position
dht.begin();                         // needed to activate the DHT11
pinMode(button, INPUT_PULLUP);       // sets the variable "button" as an input. pullup is needed to use the built in resistor
Serial.begin(9600);                  // used to setup the serial monitor 

}

void loop() {
  delay(500);                            // time between readings
  float h = dht.readHumidity();          // reads the humidity of the DHT11 and stores it as a float named "h"
  float t = dht.readTemperature();       // reads the temperature of the DHT11 and stores it as a float named "t"
  Serial.print(h);                       // prints the humidity on the serial monitor 
  Serial.print(t);                       // prints the temperature on the serial monitor 
  

  int buttonState =! digitalRead(button);       // creates a variable called "buttonState" to read the value of the pushbutton 
  c2f = (t * 1.8) + 32.0;                       // formula to convert celcius to farenheight 

  if (buttonState == HIGH){         // if the pushbutton is pressed, print the temperature value as farenheight
    lcd.setCursor(6,0);
    lcd.print(c2f);
    lcd.setCursor(12,0);
    lcd.print("F");
    } 
  if (buttonState == LOW){         // if the pushbutton is not pressed, print the temperature value as celcius 
    lcd.setCursor(6,0);
    lcd.print(t);
    lcd.setCursor(12,0);
    lcd.print("C");
    }

  lcd.setCursor(0,1);             // prints the humidity below the temperature value on the LCD. This code
  lcd.print("Hum: ");             // is outside of the if statements because we are not changing how
  lcd.setCursor(5,1);             // the humidity is displayed 
  lcd.print(h);
  lcd.setCursor(11,1);
  lcd.print("%");

}
