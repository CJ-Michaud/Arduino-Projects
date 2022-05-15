/* This program is a closed loop that reads the resistance of the LDR and 
 *  turns on or off an LED depending on the desired setpoint and hysterisis.
This program is a replication of ON OFF control, one of the process control strategies. */

// Screen is used to display values such as CO and PV. To use the LCD, we have to include the library and declare the LCD pins

#include <LiquidCrystal.h>

const int rs = 10, en = 9, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// Declaring variables to control the system 

int CO;
int ldr = A0;
int actuator = 11;
int PV; 
int H;
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
pinMode(button2, INPUT_PULLUP);
pinMode(button3, INPUT_PULLUP);       // enables pushbuttons to be used to write values to Control Output 
pinMode(button4, INPUT_PULLUP);
lcd.begin(16,2);                      // enables the LCD 
}

void loop() {
 PV = analogRead(ldr);                // reads the resistance of the LDR which is then names "PV"
 
 if (PV <= sp - H){                   // Sets the control output to 100% if the process variable is less than the setpoint - hysterisis 
  CO = 255;
  }

 if (PV >= sp + H){                   // Sets the control output to 0% if the process variable is greater than the setpoint + hysterisis 
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
else{
 digitalWrite(LED_BUILTIN, LOW);      // turns of the arduino led
 }

// code to use a pushbutton with debounce which controls a variable called "inc"
 
if (bs4 != bsL){
  lastDebounceTime = millis();
  }
if ((millis() - lastDebounceTime) > debounceDelay){         // if current time - last time the button was pressed > the debounce delay
  if (bs4 != bsC){                                           // increments the button only if bs4 is not equal to bsC 
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


 
if (inc == 0){                            // increment or decrement the setpoint only if the variable "inc" is 0
 if (bs1 == HIGH and sp < 700){           // if the UP pushbutton is pressed, increment the setpoint by 10 until the setpoint is 700
    sp = sp + 10;
    delay(100);                           // delay is needed to be able to select a specific CO and not go past it
    }
    
 if (bs2 == HIGH and sp > 60){            // if the DOWN pushbutton is pressed, decrement the setpoint by 10 until the setpoint is 60
    sp = sp - 10;
    delay(100);                           // delay is needed to be able to select a specific CO and not go past it
    }
}

if (inc == 2){                            // if the variable "inc" is 2, clear the lcd screen
  lcd.clear();
  }
  
if (inc == 3){                            // increment or decrement the hysterisis only if the variable "inc" is 3
 if (bs1 == HIGH and H < 100){            // if the UP pushbutton is pressed, increment the hysterisis by 10 until the hysterisis is 100
    H = H + 10;
    delay(100);                           // delay is needed to be able to select a specific CO and not go past it
    }
    
 if (bs2 == HIGH and H > 0){              // if the DOWN pushbutton is pressed, decrement the hysterisis by 10 until the hysterisis is 0
    H = H - 10;
    delay(100);                           // delay is needed to be able to select a specific CO and not go past it
    }
}

  
// if the variable inc is less than 2 display SP, PV, INC, CO on the LCD 
  
if (inc < 2){  
   lcd.setCursor(0,0);
   lcd.print("PV:");
   lcd.setCursor(4,0);
   lcd.print(PV);
   lcd.setCursor(8,0);
   lcd.print("INC:");
   lcd.setCursor(13,0);
   lcd.print(inc);
   lcd.setCursor(0,1);
   lcd.print("SP:");
   lcd.setCursor(4,1);
   lcd.print(sp);
   lcd.setCursor(9,1);
   lcd.print("CO:");
   lcd.setCursor(13,1);
   lcd.print(CO);
}

// if the variable inc is greater than 2 display H, PV, INC, CO on the LCD

if (inc > 2){
   lcd.setCursor(0,0);
   lcd.print("PV:");
   lcd.setCursor(4,0);
   lcd.print(PV);
   lcd.setCursor(8,0);
   lcd.print("INC:");
   lcd.setCursor(13,0);
   lcd.print(inc);
   lcd.setCursor(1,1);
   lcd.print("H:");
   lcd.setCursor(4,1);
   lcd.print(H);
   lcd.setCursor(9,1);
   lcd.print("CO:");
   lcd.setCursor(13,1);
   lcd.print(CO);
  }

// displaing inc, sp, h, and pv on the serial monitor  

   Serial.print(inc);
   Serial.print("\t");
   Serial.print("SP: ");
   Serial.print(sp);
   Serial.print("\t");
   Serial.print("H: ");
   Serial.print(H);
   Serial.print("\t");
   Serial.print("PV: ");
   Serial.println(PV);


/* conditions so that a number does not remain after changing H, PV, or SP from 
   a two digit number to a three digit number or vice versa */

if (PV < 100){
  lcd.setCursor(6,0);
  lcd.print(" ");
  }

if (sp < 100){
  lcd.setCursor(6,1);
  lcd.print(" ");
  }

if (H < 100){
  lcd.setCursor(15,1);
  lcd.print(" ");
  }
}
