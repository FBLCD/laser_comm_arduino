/* PROGRAM DEFINES */
#define VERSION 1
#define DEBUG_MODE 1

/* PINOUT DEFINES */
const int LDRPin = A5;
const int BTNPin = 7;

/* (CONST) LOCAL VARIABLES */
const int LIMIT = 1000;
bool status = false; // 0

/* LOCAL VARIABLES */
int count = 0;
int input = -1;
int default_delay = 1000;

/* ENCODING-DECODING VARIABLES */
const String alphabet[] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
const int mult[] = {16, 8, 4, 2, 1};
int concatenated_bytes = -1;
char *buf = malloc(20);
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
  concatenated_bytes = -1;
  status = false;
  memset(buf, 0, sizeof(buf));
  memset(buf2, 0, sizeof(buf2));
}

int d2t(char d)
{
 char str[2];
 str[0] = d;
 str[1] = '\0';
 return (int) strtol(str, NULL, 10);
}

int strbin2dec(const char *strbin)
{
  int result = 0;
  for (size_t i = 0; i < strlen(strbin); i++)
  {
    result = (d2t(strbin[i]) * mult[i]) + result;
  }
  return result;
}

void loop() 
{
  if (digitalRead(BTNPin) || status) 
  {
    if (!status) status = true;
    
    input = analogRead(LDRPin);
    int output = (input > LIMIT) ? 1 : 0;
    
    snprintf(buf, 20, "%d%d", concatenated_bytes, output);
    concatenated_bytes = atol(buf);
    buf2 = &buf[2];
    
    if (sizeof(concatenated_bytes) > 5)
    {
      clear_variables();
    }
    
    if (count == 4) 
    {
      Serial.print(strbin2dec(buf2));
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
