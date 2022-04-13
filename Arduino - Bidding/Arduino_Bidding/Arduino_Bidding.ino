// include the library code:
#include <LiquidCrystal.h>
#include <Wire.h>


int buttonPin = 11; // Button used as a trigger for the user ..

// SET UP FOR THE LCD .. 
const int rs = 7, en = 6, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
 // -----------------------------------------------------------------


int Contrast = 100; // using this so we do not need for a (POTENTIOMETER) .. 
int yellowPin = 8;
int bluePin = 9;

void setup() {
  
  analogWrite(10, Contrast); // setting up the contrast of the LCD
  pinMode(yellowPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

  lcd.begin(16, 2);  // set up the LCD's number of columns and rows .. 
  lcd.setCursor(0, 0); // First line, Welcoming message .. 
  lcd.print("Welcome to Bid");
}

void loop() {

  int push = digitalRead(buttonPin); // Readings from button

  digitalWrite(bluePin, LOW);
  digitalWrite(yellowPin, HIGH);

  if (push != 1) // if the button is pushed. Then and only then, we Turn on the blue led and show a message .. 
  {
    digitalWrite(yellowPin, LOW);
    digitalWrite(bluePin, HIGH);
    
    lcd.setCursor(0, 1);
    lcd.print(" ENTER YOUR BID: ");
    delay(500000); // 50 seconds delay so the the LED stays on ..
  }


  delay(500);
}
