/*This program allows for the control of a LED from  0 - 100 % which changes the resitance of an LDR.
This process is a replication of the manual control strategy */

// Screen is used to display values such as CO and PV. To use the LCD, we have to include the library and declare the LCD pins

#include <LiquidCrystal.h> 

const int rs = 10, en = 9, d4 = 5, d5 = 4, d6 = 3, d7 = 2; 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Declaring variables to control the system 

int CO;
int ldr = A0;
int actuator = 11;
int PV; 

// Declaring variable to control pushbuttons and arduino LED

int button1 = 7;
int button2 = 6;
int button3 = 12;
int enter;
int led = 13;

void setup() {
Serial.begin(9600);                         //enables the serial monitor
pinMode(actuator, OUTPUT);                  //enables the light which will be used as the actuator
pinMode(led, OUTPUT);                       //enables the arduino led on pin 13 
pinMode(button1, INPUT_PULLUP); 
pinMode(button2, INPUT_PULLUP);             // enables pushbuttons to be used to write values to Control Output 
pinMode(button3, INPUT_PULLUP);
lcd.begin(16,2); // enables the LCD 
}

void loop() {
   PV = analogRead(ldr);             // reads the resistance of the LDR which is then names "PV"
   int bs1 =! digitalRead(button1); 
   int bs2 =! digitalRead(button2);  // declared variables used to read the state of the pushbutton 
   int bs3 =! digitalRead(button3); 
   
// controlling CO with pushbuttons

   if (bs1 == HIGH and CO < 255){   // if the UP pushbutton is pressed, increment the CO by 1 until CO is 255
    CO = CO + 1;
    delay(100);                     // delay is needed to be able to select a specific CO and not go past it
    }
    
   if (bs2 == HIGH and CO > 0){     // if the DONN pushbutton is pressed, decrement the CO by 1 until CO is 0
    CO = CO - 1;
    delay(100);                     // delay is needed to be able to select a specific CO and not go past it
    }

   if (bs3 == HIGH){                // if a third button is pressed invert a boolean variable. This acts as an enter button 
    enter = !enter;
    }

   if (enter == HIGH){              // if the boolean variable called "enter" is True;
    digitalWrite(led, HIGH);        // turn on the arduino led to visually indicate the enter variable is true
    analogWrite(actuator, CO);      // write the value of CO to the actuator
    //delay(100);
    }
   else{
    digitalWrite(led, LOW);         // turns of the arduino led
    delay(50);
    }

// displaing CO and PV on the serial monitor   

   Serial.print("CO: ");
   Serial.print(CO);
   Serial.print("\t");
   Serial.print("PV: ");
   Serial.println(PV);

// displaying PV and CO on the LCD

   lcd.setCursor(0,0);
   lcd.print("CO: ");
   lcd.setCursor(4,0);
   lcd.print(CO);
   lcd.setCursor(0,1);
   lcd.print("PV: ");
   lcd.setCursor(4,1);
   lcd.print(PV);

// conditions so that the number does not remain after changing CO or PV form a two digit number to a three digit number or vice versa

if (CO < 100){
  lcd.setCursor(6,0); 
  lcd.print(" ");
  }

if (CO < 10){
  lcd.setCursor(5,0);
  lcd.print(" ");
  }

if (PV < 1000){
  lcd.setCursor(7,1);
  lcd.print(" ");
  }

if (PV < 100){
  lcd.setCursor(6,1);
  lcd.print(" ");
  }
  
}
