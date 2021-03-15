#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *alphabet[256] = {"H", "G", "N", "L", "X", "C", "W", "E", "D", "A", "Z", ".", "V", "Y", "R", "O", "J", "B", "Q", "I", "T", "K", "M", "P", "S", "F", "U", ",", "F", "W", "\n"};
char *sequences[256] = {"00100", "10111", "01110", "10101", "11011", "11110", "11000", "01010", "11001", "00110", "11101", "11111", "00010", "00111", "01111", "01101", "10110", "01001", "11010", "10010", "11100", "10100", "01000", "10000", "00101", "10001", "00001", "10011", "00011", "01011", "00000"};
char const * program_name;

//#define DEBUG_MODE

void show_usage()
{
	printf("USAGE:\n");
	printf("     %s -d sequence --> decodes byte sequences.\n", program_name);
	printf("     %s -e characters --> encodes char sequences.\n", program_name);
	printf("     %s -h --> shows this help message.\n", program_name);
	printf("");
}

int main(int argc, char *argv[])
{
	program_name = argv[0];
	char *output;
	
	if (argc < 3)
	{
		show_usage();
		return -1;
	}
	
    printf("[?] INPUT = %s\n", argv[2]);
	
	if (strcmp(argv[1], "-d") == 0)
	{
#ifdef DEBUG_MODE
		printf("[?] Decoding...\n");
#endif
		for (int i = 0; i < sizeof(sequences); i++)
		{
			if (strcmp(argv[2], sequences[i]) == 0)
			{
				output = alphabet[i];
				break;
			}
		}
	}
	
	else if (strcmp(argv[1], "-e") == 0)
	{
#ifdef DEBUG_MODE
		printf("[?] Encoding...\n");
#endif

		for (int i = 0; i < sizeof(alphabet); i++)
		{
			if (strcmp(argv[2], alphabet[i]) == 0)
			{
				output = sequences[i];
				break;
			}
		}
	}
	
	else if (strcmp(argv[1], "-h") == 0)
	{
		show_usage();
		return 0;
	}
	
	if (output == NULL)
	{
		printf("[-] Invalid handle\n");
		return -1;
	}
	
	printf("[?] OUTPUT = %s\n", output);
    return 0;
}