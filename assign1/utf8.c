#include "samples/prototypes.h"
#include <error.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>



int to_utf8(unsigned short cp, unsigned char seq[])
{
    unsigned short s = cp;
	if(cp <= 0x7F && cp >0x00) {
	   seq[0] = cp & 0xFF;
	   return 1;
	}
	else if (cp >= 0x80 && cp <= 0x07FF) {
		seq[0] = (s >> 0x06) ^ 0xC0;
		seq[1] = ((s ^ 0xFFC0) | 0x80) & ~0x40;
		return 2;
	}
	else if (cp >= 0x0800 && cp <0xFFFF) {
		seq[0] = ((s ^ 0xFC0FFF) >> 0x0C) | 0xE0;
        	seq[1] = (((s ^ 0xFFF03F) >> 0x06) | 0x80) & ~0x40;
        	seq[2] = ((s ^ 0xFFFC0) | 0x80) & ~0x40;
		return 3;
	}
	else
	return 0;
}




// ------- DO NOT EDIT ANY CODE BELOW THIS LINE (but do add comments!)  -------

void print_utf8(unsigned short cp, unsigned char seq[], int len)
{
    int i;
    printf("U+%04X   Hex:", cp);
    for (i = 0; i < len; i++)
       printf(" %02x", seq[i]);
    for ( ; i < 4; i++) printf("   ");
    seq[len] = '\0';
    printf("Character: %s  \n", seq);  
}

unsigned short convert_arg(const char *str, unsigned short low, unsigned short high)
{
    char *end;
    long n = strtol(str, &end, 0);
    if (*end != '\0')
        error(1, 0, "Invalid code point '%s'", str);
    if (n < low || n > high) 
        error(1, 0, "Code point %s not in range [%u, %u]", str, low, high);
    return n;
}

int main(int argc, char *argv[])
{
    if (argc < 2) 
        error(1, 0, "Missing argument. Please supply one or more unicode code points in decimal or hex.");
    
    for (int i = 1; i < argc; i++) {
        unsigned short cp = convert_arg(argv[i], 0, USHRT_MAX);
        unsigned char seq[4];
        int len = to_utf8(cp, seq);
        print_utf8(cp, seq, len);  
    }
    return 0;
}
