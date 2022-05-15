/*This program is a closed loop that reads the resistance of an LDR and changes the brightness of an LED 
depending on a given setpoint. In this loop, pGain is responsible for reducing the error and Ti is 
responsible for elimiating the error. This is a replication of PI control.*/

// Screen is used to display values such as CO and PV. To use the LCD, we have to include the library and declare the LCD pins

#include <LiquidCrystal.h>

const int rs = 10, en = 9, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Declaring variables to control the system 

int CO;
int ldr = A0;
int actuator = 11;
int PV; 
float pGain;
int error;
int sp;
float Ti;
const signed long interval = 100; 
float integAction;
unsigned long currentMillis;
unsigned long previousMillis;

// Declaring variable to control pushbuttons and arduino LED

int button1 = 7;
int button2 = 6;
int button3 = 12;
int button4 = 8;
int enter;
int inc;
unsigned long lastDebounceTime = 0;  
unsigned long debounceDelay = 50; 
int bsL;
int bsC;


void setup() {
Serial.begin(9600);               // enables the serial monitor
pinMode(actuator, OUTPUT);        // enables the light which will be used as the actuator
pinMode(LED_BUILTIN, OUTPUT);     // enables the arduino led on pin 13
pinMode(button1, INPUT_PULLUP);
pinMode(button2, INPUT_PULLUP);
pinMode(button3, INPUT_PULLUP);   // enables pushbuttons to be used to write values to Control Output
pinMode(button4, INPUT_PULLUP);
lcd.begin(16,2);                  // enables the LCD 
}

void loop() {
PV = analogRead(ldr);             // reads the resistance of the LDR which is then names "PV"
currentMillis = millis();

if (currentMillis - previousMillis >= interval){
  previousMillis = currentMillis;                         // saves the time that has passed as the new "previousMillis" to be used during the next code cycle
  error = sp - PV;                                        // error is the setpoint - process variable
  integAction = integAction + error;                      // simplified equation that integrates the error

 if (integAction > 500){                                  // caps the intergral action
    integAction = 500;
    }
    
  CO = (pGain * error) + (Ti * integAction);              // new equation for the Control Output in PI control 
  
  if (CO > 255){                                          // caps the allowable Control Output to be no greater than 255
    CO = 255;
    }

  if (CO < 0){                                            // caps the allowable Contrl Output to be no less than 0
    CO = 0;
    }
}
 
  
 int bs1 =! digitalRead(button1);                         // declared variables used to read the state of the pushbutton
 int bs2 =! digitalRead(button2);
 int bs3 =! digitalRead(button3);
 int bs4 =! digitalRead(button4);

if (bs3 == HIGH){                                         // if a button is pressed, invert a boolean variable. This acts as an enter button 
 enter = !enter;
 delay(100);
 }
  
if (enter == HIGH){                                       // if the boolean variable called "enter" is True;
 digitalWrite(LED_BUILTIN, HIGH);                         // turn on the arduino led to visually indicate the enter variable is true
 analogWrite(actuator, CO);                               // write the value of CO to the actuator
 } 
else{
 digitalWrite(LED_BUILTIN, LOW);                          // turns of the arduino led
 }

// code to use a pushbutton with debounce which controls a variable called "inc"
 
if (bs4 != bsL){
  lastDebounceTime = currentMillis;
  }
if (currentMillis - lastDebounceTime >= debounceDelay){    // if current time - last time the button was pressed > the debounce delay
  if (bs4 != bsC){                                         // increments the button only if bs4 is not equal to bsC 
    bsC = bs4;
    if (bsC == HIGH){
      inc = inc + 1;
      if (inc == 5){
        inc = 0;
       }
      } 
     }
    }
bsL = bs4; 

//if (inc == 0){                                           // if the variable "inc" is 0, display PV, INC, pGain, SP and Ti on the LCD
   lcd.setCursor(0,0);
   lcd.print("PV");
   lcd.setCursor(3,0);
   lcd.print(PV);
   lcd.setCursor(7,0);
   lcd.print("Pg");
   lcd.setCursor(10,0);
   lcd.print(pGain);
   lcd.setCursor(15,0);
   lcd.print(inc);
   lcd.setCursor(0,1);
   lcd.print("SP");
   lcd.setCursor(3,1);
   lcd.print(sp);
   lcd.setCursor(7,1);
   lcd.print("Ti");
   lcd.setCursor(10,1);
   lcd.print(Ti);
  }


  
if (inc == 2){                                            // increment or decrement the setpoint only if the variable "inc" is 2
 if (bs1 == HIGH and sp < 700){                           // if the UP pushbutton is pressed, increment the setpoint by 10 until the setpoint is 700
    sp = sp + 10;
    delay(100);                                           // delay is needed to be able to select a specific CO and not go past it
    }
    
 if (bs2 == HIGH and sp > 60){                            // if the DOWN pushbutton is pressed, decrement the setpoint by 10 until the setpoint is 60
    sp = sp - 10;
    delay(100);                                           // delay is needed to be able to select a specific CO and not go past it
    }
}
  
if (inc == 3){                                            // increment or decrement the pGain only if the variable "inc" is 3
 if (bs1 == HIGH and pGain < 10){                         // if the UP pushbutton is pressed increment the pGain by 0.1 until the pGain is 10
    pGain = pGain + 0.1;
    delay(100);                                           // delay is needed to be able to select a specific CO and not go past it
    }
    
 if (bs2 == HIGH and pGain > 0){                          // if the DOWN pushbutton is pressed decrement the pGain by 0.1 until the pGain is 0
    pGain = pGain - 0.1;
    delay(100);                                           // delay is needed to be able to select a specific CO and not go past it
    }
}

if (inc == 4){                                            // increment or decrement the Ti only if the variable "inc" is 4
 if (bs1 == HIGH and Ti < 10.0){                          // if the UP pushbutton is pressed increment the Ti by 0.1 until the Ti is 10
    Ti = Ti + 0.1;
    delay(100);                                           // delay is needed to be able to select a specific CO and not go past it
    }
    
 if (bs2 == HIGH and Ti > 0){                             // if the DOWN pushbutton is pressed decrement the Ti by 0.1 until the Ti is 0
    Ti = Ti - 0.1;
    delay(100);                                           // delay is needed to be able to select a specific CO and not go past it
    } 
}

if (inc == 5){                                            // if the variable "inc" is 4, clear the lcd screen
  lcd.clear();
  }

// displaing inc, pGain, Ti, SP, and PV on the serial monitor 

   Serial.print(inc);
   Serial.print("\t");
   Serial.print("Gain: ");
   Serial.print(pGain);
   Serial.print("\t");
   Serial.print("Ti: ");
   Serial.print(Ti);
   Serial.print("\t");
   Serial.print("SP: ");
   Serial.print(sp);
   Serial.print("\t");
   Serial.print("PV: ");
   Serial.println(PV);

/* conditions so that a number does not remain in the LCD after changing PV, or SP from 
   a two digit number to a three digit number or vice versa */


if (PV < 100){
  lcd.setCursor(5,0);
  lcd.print(" ");
  }

if (sp < 100){
  lcd.setCursor(5,1);
  lcd.print(" ");
  }
}
