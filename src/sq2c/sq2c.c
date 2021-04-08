#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *alphabet[256] = {"H", "G", "N", "L", "X", "C", "W", "E", "D", "A", "Z", ".", "V", "Y", "R", "O", "J", "B", "Q", "I", "T", "K", "M", "P", "S", "F", "U", ",", "F", "W", "\n"};
const char *sequences[] = {"33133", "13111", "31113", "13131", "11311", "11113", "11333", "31313", "11331", "33113", "11131", "11111", "33313", "33111", "31111", "31131", "13113", "31331", "11313", "13313", "11133", "13133", "31333", "13333", "33131", "13331", "33331", "13311", "33311", "31311", "33333"};
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
	int match = 0; // default is false
	
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
				match = 1;
				break;
			}
			if (i == 30 && match != 1) // FIXME: this is ugly
			{
				// no variable was found - handle it, otherwise we'll crash.
				printf("[-] Invalid handle: %s\n", argv[2]);
				return -1;
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
				match = 1;
				break;
			}
			if (i == 30 && match != 1) // FIXME: this is ugly
			{
				// no variable was found - handle it, otherwise we'll crash.
				printf("[-] Invalid handle: %s\n", argv[2]);
				return -1;
			}	
		}
	}
	
	else if (strcmp(argv[1], "-h") == 0)
	{
		show_usage();
		return 0;
	}
	
	printf("[?] OUTPUT = %s\n", output);
    return 0;
}
