// LCD library
#include <LiquidCrystal.h>

// LCD Display
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

// encoding/decoding
String alphabet[] = {"H", "G", "N", "L", "X", "C", "W", "E", "D", "A", "Z", ".", "V", "Y", "R", "O", "J", "B", "Q", "I", "T", "K", "M", "P", "S", "F", "U", ",", "F", "W", "\n"};
String sequences[] = {"33133", "13111", "31113", "13131", "11311", "11113", "11333", "31313", "11331", "33113", "11131", "11111", "33313", "33111", "31111", "31131", "13113", "31331", "11313", "13313", "11133", "13133", "31333", "13333", "33131", "13331", "33331", "13311", "33311", "31311", "33333"};

// global defs
int baudrate = 9600;
int default_delay = 250;
int status = 0;

// stdin
String input_buffer;

// stdout
String output_buffer;

// pinout
int laserPin = 11;

// debug
#define DEBUG_MODE 0

String parse_seq(String chars)
{
    for (int i = 0; i < 31; i++)
    {
#ifdef DEBUG_MODE
      Serial.print("(");
      Serial.print(chars);
      Serial.print(") ");
      Serial.print(i);
      Serial.print(" -> ");
      Serial.println(alphabet[i]);
#endif
      if(chars.indexOf(alphabet[i]) >= 0)
      {
#ifdef DEBUG_MODE
        Serial.print("[?] match: ");
        Serial.print(chars);
        Serial.print(" -> ");
        Serial.println(sequences[i]);
#endif
        return(sequences[i]);
      }
    }
    return ""; // this shouldn't be reached 
}

void send_ldata(String sequence) {
  for(auto x : sequence)
  { 
    int b = (x == '1') ? 1 : 0;
    digitalWrite(laserPin, b);
    delay(500); // aligned with LDR code
  }
}

void setup() {
  Serial.begin(baudrate);
  pinMode(laserPin, OUTPUT);

  Serial.print("[?] Serial port opened [baudrate: ");
  Serial.print(baudrate);
  Serial.println("]");

  lcd.begin(10, 2);
  digitalWrite(laserPin, LOW);
}

void loop() {
  status += 1;
  // loop over serial input
  while (Serial.available()) {
    delay(2);
    char c = Serial.read();
    input_buffer += c;
  }

  // delete last char 
  int length = input_buffer.length();
  input_buffer[length-1] = ' ';

  if (status = 1 && input_buffer != "") {
    Serial.println("[?] Sending start sequence");
    digitalWrite(laserPin, HIGH);
    delay(100);
    digitalWrite(laserPin, LOW);
    delay(100);
  }

#ifdef DEBUG_MODE
  if (input_buffer != "") {
    Serial.print("[+] Input string: ");
    Serial.println(input_buffer);
  }
#endif

  if (input_buffer != "") {
    lcd.setCursor(0,0);
    for (int i = 0; i < sizeof(input_buffer); i++)
    {
#ifdef DEBUG_MODE
      Serial.print("[?] Sending ");
      Serial.println(String(input_buffer[i]));
#endif
      send_ldata(parse_seq(String(input_buffer[i])));  // if no laser is connected this will crash
      output_buffer += parse_seq(String(input_buffer[i]));
    }
    lcd.print(output_buffer);
    lcd.flush();
    Serial.print("[+] Sent ");
    Serial.print(sizeof(output_buffer));
    Serial.print(" bits ( ");
    Serial.print(input_buffer);
    Serial.println(") to the host...");
    input_buffer="";
    delay(200);
    digitalWrite(laserPin, LOW);
  }
}
