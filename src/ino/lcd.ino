// LCD library
#include <LiquidCrystal.h>

// LCD Display
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

// Serial baudrate (default)
int baudrate = 9600;

// stdin
String input_buffer;

// debug
// #define DEBUG_MODE 0

void setup() {
  Serial.begin(baudrate);

  Serial.print("[?] Serial port opened [baudrate: ");
  Serial.print(baudrate);
  Serial.println("]");

  lcd.begin(10, 2);
}

void loop() {
  // loop over serial input
  while (Serial.available()) {
    delay(2);
    char c = Serial.read();
    Serial.println(c);
    input_buffer += c;
  }

  // delete last char 
  int length = input_buffer.length();
  input_buffer[length-1] = ' ';

#ifdef DEBUG_MODE
  if (input_buffer != "") {
    Serial.print("[+] Input string: ");
    Serial.println(input_buffer);
  }
#endif

  // handle serial commands
  if (input_buffer.indexOf(";clear") > 0) {
    Serial.println("[?] Cleaning up..");
    lcd.clear();
    input_buffer="";
  }

  lcd.setCursor(0,0);
  lcd.print(input_buffer);
  lcd.flush();
}
