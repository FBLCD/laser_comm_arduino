// LCD library
#include <LiquidCrystal.h>

// LCD Display
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

/* Test String */
String input_buffer;

/* Array Length */
int array_size = 31;

/* Arrays */
String alphabet[] = {"H", "G", "N", "L", "X", "C", "W", "E", "D", "A", "Z", ".", "V", "Y", "R", "O", "J", "B", "Q", "I", "T", "K", "M", "P", "S", "F", "U", ",", "F", "W", " "};
String sequences[] = {"33133", "13111", "31113", "13131", "11311", "11113", "11333", "31313", "11331", "33113", "11131", "11111", "33313", "33111", "31111", "31131", "13113", "31331", "11313", "13313", "11133", "13133", "31333", "13333", "33131", "13331", "33331", "13311", "33311", "31311", "33333"};

/* Sequence delimiter */
#define DELIMITER "-" // temp char until we figure out how to completely delete '\0's

void setup() {
  pinMode(11, OUTPUT); // DL
  lcd.begin(10, 2); // LCD
  digitalWrite(11, LOW); // turn off laser by default
  Serial.begin(9600); // turn on serial
}

String c2s(String c) {
  for (int i = 0; i < array_size; i++) {
    if (c.indexOf(alphabet[i]) >= 0) {
      return sequences[i];
    }
  }
}

void s2l(String s) {
  for(auto x : s)
  {
    int b = (x == '1') ? 1 : 0;
    digitalWrite(11, b);
    delay(400);
  }
}

void loop() {
  while (Serial.available()) {
    delay(2);
    char c = Serial.read();
    if (c != "" || c != '\0') { 
      input_buffer += c;
    }
  }
  
  if (input_buffer != "") {
    digitalWrite(11, HIGH);
    delay(1);
    digitalWrite(11, LOW);
    Serial.println(c2s(input_buffer));
    if (input_buffer.length() ==  2) {
      Serial.print("short");
      s2l(c2s(input_buffer));
    } else {
      for (int i = 0; i < input_buffer.length() - 1; i++) {
        Serial.println(input_buffer[i]);
        s2l(c2s(String(input_buffer[i])));
        delay(500);
        digitalWrite(11, HIGH);
        delay(1);
        digitalWrite(11, LOW);
      }
    }

    input_buffer = "";
    digitalWrite(11, LOW);
  }
}