#include <string.h>
#include <LiquidCrystal.h>

/* Power ON LCD display */
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

/* Light limit (for DL) */
const int limit = 1000;

/* Concatenated input bits */
String input;

/* Start bit */
int start_bit = 0;

/* Hardcoded arrays (for parsing) */
String alphabet[] = {"H", "G", "N", "L", "X", "C", "W", "E", "D", "A", "Z", ".", "V", "Y", "R", "O", "J", "B", "Q", "I", "T", "K", "M", "P", "S", "F", "U", ",", "F", "W", " "};
String sequences[] = {"33133", "13111", "31113", "13131", "11311", "11113", "11333", "31313", "11331", "33113", "11131", "11111", "33313", "33111", "31111", "31131", "13113", "31331", "11313", "13313", "11133", "13133", "31333", "13333", "33131", "13331", "33331", "13311", "33311", "31311", "33333"};

String s2c(String s) {
  /* Converts sequences to single-characters */
  for (int i = 0; i < 31; i++) if (s == sequences[i]) return alphabet[i];
}

void setup() {
  /* Open the serial port */
  Serial.begin(9600);

  /* Set up LCD display */
  lcd.begin(10, 2);

  /* Set up LDR */
  pinMode(A5, INPUT);
}

void loop() {
  /* Wait for start sequence */
  while (start_bit < limit) {
    start_bit = analogRead(A5);
  }

  /* Reset the bit counter */
  start_bit = 0;
  delay(2);
  
  /* Loop over start_bit */
  while (start_bit != -1) 
  {
    /* Read laser data (check > 1000) */
    int output = (analogRead(A5) > limit) ? 1 : 3;

    /* Concatenate sequence/bits */
    input += String(output);
    start_bit += 1;

    /* Parse sequences */
    if (start_bit == 5)
    {
      lcd.print(s2c(input));
      start_bit = -1;
      input = "";
    }

    /*
     * NOTE: DON'T TOUCH ME
     */
    delay(500);
  }

  /*
  * NOTE: DON'T TOUCH ME
  */
  delay(1.5);
}