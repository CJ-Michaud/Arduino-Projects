//Make sure to download the DHT11 Library or the program will not run

#include "DHT.h" 
#define DHTPIN 8                      // digital pin connected to the DHT sensor
#define DHTTYPE DHT11                 // used to DHT 11
DHT dht(DHTPIN, DHTTYPE);             // creating the DHT11 in this program 

void setup() {
dht.begin();                          // needed to activate the dht variable we created
Serial.begin(9600);                   // needed to activate the serial monitor
}

void loop() {
  delay(50);                          // delay between readings
  float h = dht.readHumidity();       // reads the humidity and stores in as a float named "h"
  float t = dht.readTemperature();    // reads the temperature (celcius) and stores in as a float named "y"
  Serial.print("Temp: ");             // creates a text "Temp" in the serial moniter 
  Serial.print(t);                    // prints the temperature reading 
  Serial.print(" F");                 // creates the symbol "F" so that it the temperature is understood as farenheight
  Serial.print("\t");                 // creates a space after the "F"
  Serial.print("Hum: ");              // creates a text "Hum" in the serial moniter 
  Serial.print(h);                    // prints the humidity reading 
  Serial.println(" %");               // creates the symbol "%" so that it the humidity is understood as a percentage
}
