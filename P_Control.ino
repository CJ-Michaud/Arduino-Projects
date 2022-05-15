/* This program is a closed loop that reads the resistance of an LDR and changes the brightness of an LED based on the 
setpoint. In this loop the more the P increases the more the error reduces. 
This is a replicdtion of P Control. */


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
Serial.begin(9600);                   // enables the serial monitor
pinMode(actuator, OUTPUT);            // enables the light which will be used as the actuator
pinMode(LED_BUILTIN, OUTPUT);         // enables the arduino led on pin 13
pinMode(button1, INPUT_PULLUP);
pinMode(button2, INPUT_PULLUP);       // enables pushbuttons to be used to write values to Control Output 
pinMode(button3, INPUT_PULLUP);
pinMode(button4, INPUT_PULLUP);
lcd.begin(16,2);                      // enables the LCD 
}

void loop() {
 PV = analogRead(ldr);                // reads the resistance of the LDR which is then names "PV"

error = sp - PV;                      // error is the setpoint - process variable
CO = pGain * error;                   // Control output is the pGain multiplied with error

 if (CO > 255){                       // sets the maximum value of the control output ot 255
  CO = 255;
  }

 if (CO < 0){                         // sets the maximum value of the control output ot 255
  CO = 0;
  }
  

 int bs1 =! digitalRead(button1);     // declared variables used to read the state of the pushbutton 
 int bs2 =! digitalRead(button2);
 int bs3 =! digitalRead(button3);
 int bs4 =! digitalRead(button4);

if (bs3 == HIGH){                     // if a third button is pressed invert a boolean variable. This acts as an enter button 
 enter = !enter;
 delay(100);
 }
  
if (enter == HIGH){                   // if the boolean variable called "enter" is True;
 digitalWrite(LED_BUILTIN, HIGH);     // turn on the arduino led to visually indicate the enter variable is true
 analogWrite(actuator, CO);           // write the value of CO to the actuator
 } 
 } 
else{
 digitalWrite(LED_BUILTIN, LOW);      // turns of the arduino led
 }

// code to use a pushbutton with debounce which controls a variable called "inc"

if (bs4 != bsL){
  lastDebounceTime = millis();
  }
if ((millis() - lastDebounceTime) > debounceDelay){ // if current time - last time the button was pressed > the debounce delay
  if (bs4 != bsC){                                  // increments the button only if bs4 is not equal to bsC 
    bsC = bs4;
    if (bsC == HIGH){
      inc = inc + 1;
      if (inc == 4){
        inc = 0;
       }
      } 
     }
    }
bsL = bs4; 

if (inc == 0){                                      // if the variable "inc" is 0, display INC, PV, and Error on the LCD
   lcd.setCursor(7,0);
   lcd.print("INC");
   lcd.setCursor(11,0);
   lcd.print(inc);
   lcd.setCursor(0,1);
   lcd.print("PV");
   lcd.setCursor(3,1);
   lcd.print(PV);
   lcd.setCursor(7,1);
   lcd.print("Err");
   lcd.setCursor(11,1);
   lcd.print(error);
  }

if (inc == 1){                                     // if the variable "inc" is 1, clear the LCD
  lcd.clear();
  }

if(inc > 1){                                       // if the variable "inc" is greater than 1 display INC, SP, and P on the LCD
   lcd.setCursor(7,0);
   lcd.print("INC");
   lcd.setCursor(11,0);
   lcd.print(inc);
   lcd.setCursor(0,1);
   lcd.print("SP");
   lcd.setCursor(3,1);
   lcd.print(SP);
   lcd.setCursor(9,1);
   lcd.print("P");
   lcd.setCursor(11,1);
   lcd.print(pGain);
  } 

  
if (inc == 2){                                    // increment or decrement the setpoint only if the variable "inc" is 2
 if (bs1 == HIGH and sp < 700){                   // if the UP pushbutton is pressed, increment the setpoint by 10 until the setpoint is 700
    sp = sp + 10;
    delay(100);                                   // delay is needed to be able to select a specific CO and not go past it
    }
    
 if (bs2 == HIGH and sp > 60){                    // if the DOWN pushbutton is pressed, decrement the setpoint by 10 until the setpoint is 60
    sp = sp - 10;
    delay(100);                                   // delay is needed to be able to select a specific CO and not go past it
    }
}
  
if (inc == 3){                                    // increment or decrement the pGain only if the variable "inc" is 3
 if (bs1 == HIGH and pGain < 10){                 // if the UP pushbutton is pressed increment the pGain by 0.1 until the pGain is 10
    pGain = pGain + 0.1;
    delay(100);                                   // delay is needed to be able to select a specific CO and not go past it
    }
    
 if (bs2 == HIGH and pGain > 0){                  // if the DOWN pushbutton is pressed decrement the pGain by 0.1 until the pGain is 0
    pGain = pGain - 0.1;
    delay(100);                                   // delay is needed to be able to select a specific CO and not go past it
    }
}

if (inc == 4){                                    // if the variable "inc" is 4, clear the lcd screen
  lcd.clear();
  }

// displaing inc, sp, h, and pv on the serial monitor 
  
   Serial.print(inc);
   Serial.print("\t");
   Serial.print("SP: ");
   Serial.print(sp);
   Serial.print("\t");
   Serial.print("Gain: ");
   Serial.print(pGain);
   Serial.print("\t");
   Serial.print("PV: ");
   Serial.print(PV);
   Serial.print("\t");
   Serial.print("CO: ");
   Serial.println(CO);
   


/* conditions so that a number does not remain after changing H, PV, or SP from 
   a two digit number to a three digit number or vice versa */

if (PV < 100){
  lcd.setCursor(5,0);
  lcd.print(" ");
  }

if (sp < 100){
  lcd.setCursor(5,1);
  lcd.print(" ");
  }

if (pGain < 10.0){
  lcd.setCursor(13,1);
  lcd.print(" ");
  }
if (error < 100){
  lcd.setCursor(15,0);
  lcd.print(" ");
}
}
