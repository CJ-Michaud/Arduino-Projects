// Make sure to include the dht unified sensor library in order for the program to work

#include <LiquidCrystal.h>              // library needed to use to run the liquid crystal display

const int rs = 10, en = 9, d4 = 5, d5 = 4, d6 = 3, d7 = 2;        // setting the pins to setup the liquid crystal display
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                        // function to use the pins to turn on and use the liquid crystal display

#include "DHT.h"                // includes the dht library
#define DHTPIN 8                // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11           //  includes the type of DHT sensor
DHT dht(DHTPIN, DHTTYPE);       // function that creates the dht variable as assigned the pin and type of sensor 

#include <SPI.h>               // includes the library needed to communicate with the sd card module
#include <SD.h>                // includes the library needed to use the sd card

/* MOSI - pin 11
   MISO - pin 12
   SCK - pin 13

Arduino pins needed to connect to the SD card module.
Cannot be changed. They are probably predefined in the SD Card library. */

const int chipSelect = 6;      // declaring a variable for the "CS" pin on the SD card module 

void setup() {
dht.begin();                // needed to activate the DHT11
Serial.begin(9600);         // used to setup the serial monitor 

}

void loop() {

  delay(100);                           // time between temperature and humidity readings
  float h = dht.readHumidity();         // reads the humidity of the DHT11 and stores it as a float named "h"
  float t = dht.readTemperature();      // reads the temperature of the DHT11 and stores it as a float named "t"
 
File dataFile = SD.open("datalog.csv", FILE_WRITE); // creates a variable called "DataFile" which creates a csv file called "datalog.csv" 
                                                    // on the SD card that can be written to 

   //if the file is available, write to it:
 if (dataFile) {
    dataFile.print(t);                  // prints the temperature reading to the datalog.csv file 
    dataFile.print(",");                // prints a comma after the temperature to the datalog.csv file 
    dataFile.println(h);                // prints the humidity reading to the datalog.csv file 
    dataFile.close();                   // closes the datalog.csv file. The resulting sequence looks like: "temperature,humidity"
  }
   //if the file isn't open, pop up an error:
  else {
   Serial.println("error opening datalog.txt");
 }
}
