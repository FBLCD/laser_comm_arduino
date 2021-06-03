#include <string.h>
#include <LiquidCrystal.h>

// LCD Display
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

// DL parser
const int limit = 1000;
String input;

// Arrays
String alphabet[] = {"H", "G", "N", "L", "X", "C", "W", "E", "D", "A", "Z", ".", "V", "Y", "R", "O", "J", "B", "Q", "I", "T", "K", "M", "P", "S", "F", "U", ",", "F", "W", " "};
String sequences[] = {"33133", "13111", "31113", "13131", "11311", "11113", "11333", "31313", "11331", "33113", "11131", "11111", "33313", "33111", "31111", "31131", "13113", "31331", "11313", "13313", "11133", "13133", "31333", "13333", "33131", "13331", "33331", "13311", "33311", "31311", "33333"};

String s2c(String s) {
  for (int i = 0; i < 31; i++) if (s == sequences[i]) return alphabet[i];
}

void setup() {
  Serial.begin(9600); // open serial
  lcd.begin(10, 2); // LCD
  pinMode(A5, INPUT); // LDR
}

void loop() {
   int start_bit = 0;
   
   while (start_bit < limit) {
      start_bit = analogRead(A5);
   }

   start_bit = 0;
   delay(2);
   
   while (start_bit != -1) 
   {
      int output = (analogRead(A5) > limit) ? 1 : 3;
      input += String(output);
      start_bit += 1;
      if (start_bit == 5)
      {
        Serial.println(input);
        lcd.print(s2c(input));
        start_bit = -1;
        input = "";
      }
      delay(500);
   }
}