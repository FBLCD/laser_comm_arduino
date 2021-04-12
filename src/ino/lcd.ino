// include the library code:
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

String readString;

void setup() {
  Serial.begin(9600);
  Serial.println("serial test 0021"); // so I can keep track of what is loaded
  lcd.begin(16, 2);
}

void loop() {

  while (Serial.available()) {
    delay(2);  //delay to allow byte to arrive in input buffer
    char c = Serial.read();
    ms.Match(pattern, 0);
    readString += c;
  }

  readString.replace(" ", "");

  if(readString.indexOf(";clear") > 0) {
    Serial.println("Cleaning up..");
    lcd.clear();
    readString="";
  }

  lcd.setCursor(0,0);
  //readString.remove(sizeof(readString) - 3);
  //Serial.println(sizeof(readString));
  lcd.flush();
  lcd.print(readString);
}