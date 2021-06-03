#include <LiquidCrystal.h>

/* Power ON LCD display */
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

/* Input characters */
String input_buffer;

/* Array Length */
int array_size = 31;

/* Custom characters */
byte Check[] = {
  B00000,
  B00001,
  B00011,
  B10110,
  B11100,
  B01000,
  B00000,
  B00000
};

/* Hardcoded arrays (for parsing) */
String alphabet[] = {"H", "G", "N", "L", "X", "C", "W", "E", "D", "A", "Z", ".", "V", "Y", "R", "O", "J", "B", "Q", "I", "T", "K", "M", "P", "S", "F", "U", ",", "F", "W", " "};
String sequences[] = {"33133", "13111", "31113", "13131", "11311", "11113", "11333", "31313", "11331", "33113", "11131", "11111", "33313", "33111", "31111", "31131", "13113", "31331", "11313", "13313", "11133", "13133", "31333", "13333", "33131", "13331", "33331", "13311", "33311", "31311", "33333"};

void setup() {
  /* Open the serial port */
  Serial.begin(9600);

  /* Set up laser diode */
  pinMode(11, OUTPUT);

  /* Set up LCD display */
  lcd.begin(10, 2);

  /* Turn off laser by default */
  digitalWrite(11, LOW);

  /* Create custom char */
  lcd.createChar(0, Check);
}

String c2s(String c) {
  /* Converts single-characters to sequences */
  for (int i = 0; i < array_size; i++) if (c.indexOf(alphabet[i]) >= 0) return sequences[i];
}

void s2l(String s) {
  /* Sends given sequence through laser diode */
  for(auto x : s)
  {
    int b = (x == '1') ? 1 : 0;
    digitalWrite(11, b);
    delay(400);
  }
}

void loop() {
  /* Read user input data */
  while (Serial.available()) {
    delay(2);
    char c = Serial.read();

    /* Skip NULL characters (useless crap) */
    if (c != "" || c != '\0') { 
      input_buffer += c;
    }
  }
  
  /* Parse user input data (if it's not empty) */
  if (input_buffer != "") {
    /* Send start frame */
    digitalWrite(11, HIGH);
    delay(1);
    digitalWrite(11, LOW);

    Serial.println(c2s(input_buffer));

    /* Parse one character */
    if (input_buffer.length() == 2) {
      s2l(c2s(input_buffer));
    } else {
      /* Parse multiple characters */
      for (int i = 0; i < input_buffer.length() - 1; i++) {
        Serial.println(input_buffer[i]);
        s2l(c2s(String(input_buffer[i])));
        /*
        * NOTE: DON'T TOUCH ME
        */
        delay(500);

        /* Send start frame (again) */
        digitalWrite(11, HIGH);
        delay(1);
        digitalWrite(11, LOW);
      }
    }

    /* Clean up user input data */
    input_buffer = "";

    /* Turn off the laser diode */
    digitalWrite(11, LOW);

    /* Success */
    lcd.setCursor(0,0);
    lcd.write((byte)0);
    lcd.print(" All ok!");
  }
}
