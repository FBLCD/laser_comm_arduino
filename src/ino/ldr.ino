#include <string.h>
#include <LiquidCrystal.h>

// LCD Display
LiquidCrystal lcd(8, 9, 4, 5, 6, 7); 

/* PROGRAM DEFINES */
#define VERSION 1
#define DEBUG_MODE 1
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5

/* PINOUT DEFINES */
const int LDRPin = A5;
const int BTNPin = 11;

/* (CONST) LOCAL VARIABLES */
const int LIMIT = 1000;
bool status = false; // 0
int rgr = 0;

/* LOCAL VARIABLES */
int count = 0;
int input = -1;
int default_delay = 500;
int lcd_key     = 0;
int adc_key_in  = 0;

/* ENCODING-DECODING VARIABLES */
const char *alphabet[] = {"H", "G", "N", "L", "X", "C", "W", "E", "D", "A", "Z", ".", "V", "Y", "R", "O", "J", "B", "Q", "I", "T", "K", "M", "P", "S", "F", "U", ",", "F", "W", "\n"};
const char *sequences[] = {"33133", "13111", "31113", "13131", "11311", "11113", "11333", "31313", "11331", "33113", "11131", "11111", "33313", "33111", "31111", "31131", "13113", "31331", "11313", "13313", "11133", "13133", "31333", "13333", "33131", "13331", "33331", "13311", "33311", "31311", "33333"};
int concatenated_bits = -1;
char *buf2, *buf;

void setup() 
{
  Serial.begin(9600);
  lcd.begin(10, 2);
  pinMode(LDRPin, INPUT);
  pinMode(BTNPin, INPUT);
}

void clear_variables()
{
  count = 0;
  concatenated_bits = -1;
  rgr = 0;
  status = false;
  memset(buf, 0, sizeof(buf));
  memset(buf2, 0, sizeof(buf2));
}

int read_LCD_buttons() 
{
  adc_key_in = analogRead(0);
  if (adc_key_in > 900) return btnNONE;
  if (adc_key_in < 50)   return btnRIGHT; 
  if (adc_key_in < 250)  return btnUP;
  if (adc_key_in < 450)  return btnDOWN;
  if (adc_key_in < 650)  return btnLEFT;
  if (adc_key_in < 850)  return btnSELECT; 
  return btnNONE;
}

const char *parse_char(char *num)
{
    for (int i = 0; i < sizeof(sequences); i++)
    {
      if (strcmp(num, sequences[i]) == 0)
      {
        return(alphabet[i]);
      }
    }
    return NULL; // this shouldn't be reached 
}

int wait_for_sequence()
{
  while (rgr != 1)
  {
    if (analogRead(LDRPin) > LIMIT)
    {
      Serial.println("[!] Recieved start bytes.");
      rgr = 0;
      return 1;
    }
  }
  return 0; // we should never reach this
}

void loop() 
{
  if (wait_for_sequence() == 1 || status)  
  {
    if (!status) status = true;

#ifdef DEBUG_MODE
    Serial.print("[?] Status = ");
    Serial.println(status);
    Serial.print("[?] COUNT = ");
    Serial.println(count);
#endif

#ifdef DEBUG_MODE
    Serial.println("[?] Begin reading...");
#endif

    input = analogRead(LDRPin);
    int output = (input > LIMIT) ? 1 : 3;

#ifdef DEBUG_MODE
    Serial.println("[?] Allocating memory...");
#endif
    char *buf = malloc(20);
    if (!buf)
      Serial.println("Failed to allocate memory");

#ifdef DEBUG_MODE
    Serial.println("[?] Concatenating bytes...");
#endif
    snprintf(buf, 20, "%d%d", concatenated_bits, output);
    concatenated_bits = atol(buf);
    buf2 = &buf[2];

#ifdef DEBUG_MODE
    Serial.println("[?] Done with parsing...");
#endif
    
    if (sizeof(concatenated_bits) > 5)
    {
#ifdef DEBUG_MODE
      Serial.println("[?] Cleaning up...");
#endif
      clear_variables();
    }

#ifdef DEBUG_MODE
    Serial.println("===============");
    Serial.print("| BUF2 = ");
    Serial.print(buf2);
    Serial.println("    |");
    Serial.println("===============");
#endif

    if (count == 4) 
    {
#ifdef DEBUG_MODE
      Serial.println("[?] Count equals 4, parsing sequence...");
#endif
      lcd.print(parse_char(buf2));
      Serial.print(" ");
      clear_variables();
    }
    else 
    {
      count += 1;
    }
  } else if (read_LCD_buttons() == 3)
  {
    lcd.clear();
  }
  delay(default_delay); 
}
