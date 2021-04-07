#include <string.h>

/* PROGRAM DEFINES */
#define VERSION 1
#define DEBUG_MODE 1

/* PINOUT DEFINES */
const int LDRPin = A5;
const int BTNPin = 11;

/* (CONST) LOCAL VARIABLES */
const int LIMIT = 1000;
bool status = false; // 0

/* LOCAL VARIABLES */
int count = 0;
int input = -1;
int default_delay = 1000;

/* ENCODING-DECODING VARIABLES */
const char *alphabet[] = {"H", "G", "N", "L", "X", "C", "W", "E", "D", "A", "Z", ".", "V", "Y", "R", "O", "J", "B", "Q", "I", "T", "K", "M", "P", "S", "F", "U", ",", "F", "W", "\n"};
const char *sequences[] = {"00100", "10111", "01110", "10101", "11011", "11110", "11000", "01010", "11001", "00110", "11101", "11111", "00010", "00111", "01111", "01101", "10110", "01001", "11010", "10010", "11100", "10100", "01000", "10000", "00101", "10001", "00001", "10011", "00011", "01011", "00000"};const int mult[] = {16, 8, 4, 2, 1};
int concatenated_bits = -1;
char *buf2;

void setup() 
{
  Serial.begin(9600);
  pinMode(LDRPin, INPUT);
  pinMode(BTNPin, INPUT);
}

void clear_variables()
{
  count = 0;
  concatenated_bits = -1;
  status = false;
  memset(buf, 0, sizeof(buf));
  memset(buf2, 0, sizeof(buf2));
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

void loop() 
{
  if (digitalRead(BTNPin) || status) 
  {
   
    if (!status) status = true;
    
    input = analogRead(LDRPin);
    int output = (input > LIMIT) ? 1 : 0;

    char *buf = malloc(20);
    if (!buf)
      Serial.println("Failed to allocate memory");

    snprintf(buf, 20, "%d%d", concatenated_bits, output);
    concatenated_bits = atol(buf);
    buf2 = &buf[2];
    
    if (sizeof(concatenated_bits) > 5)
    {
      clear_variables();
    }
    
    if (count == 4) 
    {
      Serial.print(parse_char(buf2));
      Serial.print(" ");
      clear_variables();
    }
    else 
    {
      count += 1;
    }
  }
  delay(default_delay); 
}
