// Make sure to include the dht unified sensor library in order for the program to work

#include <LiquidCrystal.h> // library needed to use to run the liquid crystal display

const int rs = 10, en = 9, d4 = 5, d5 = 4, d6 = 3, d7 = 2;    // setting the pins to setup the liquid crystal display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                    // function to use the pins to turn on and use the liquid crystal display

#include "DHT.h"             // creates the dht library
#define DHTPIN 8             // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11        // DHT 11
DHT dht(DHTPIN, DHTTYPE);    

void setup() {
lcd.begin(16,2);             // needed to activate the lcd. generates a 16 by 2 array
dht.begin();                 // needed to activate the DHT11
}

void loop() {
  delay(500);                            // delay between readings
  float h = dht.readHumidity();          // reads the humidity of the DHT11 and stores it as a float named "h"
  float t = dht.readTemperature();       // reads the temperature of the DHT11 and stores it as a float named "t"
  lcd.setCursor(0,0);                    // sets the cursor of the LCD to the 0,0 grid position 
  lcd.print("Temp: ");                   // prints "Temp: " in the lcd at the 0,0 position
  lcd.setCursor(6,0);                    // sets the cursor of the LCD to the 6,0 grid position 
  lcd.print(t);                          // prints the actual temperature in the lcd from the determined position
  lcd.setCursor(12,0);                   // sets the cursor of the LCD to the 12,0 grid position 
  lcd.print("F");                        // prints "F" in the lcd from the determined position 
  lcd.setCursor(0,1);                    // sets the cursor of the LCD to the 0,1 grid position 
  lcd.print("Hum: ");                    // prints "Hum: " in the lcd from the determined position 
  lcd.setCursor(5,1);                    // sets the cursor of the LCD to the 5,1 grid position 
  lcd.print(h);                          // prints the actual humidity in the lcd from the determined position
  lcd.setCursor(11,1);                   // sets the cursor of the LCD to the 11,1 grid position 
  lcd.print("%");                        // prints the symbol "%" in the lcd from the determined position
}
