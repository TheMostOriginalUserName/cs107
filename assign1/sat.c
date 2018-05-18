#include "samples/prototypes.h"
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>


long signed_max(int bitwidth)
{
    return 0;
}

long signed_min(int bitwidth)
{
    return 0;
}

long sat_add(long a, long b, int bitwidth)
{
    return 0;
}




// ------- DO NOT EDIT ANY CODE BELOW THIS LINE (but do add comments!)  -------


long convert_arg(const char *str, long low, long high, const char *argname)
{
    char *end;
    long n = strtol(str, &end, 0);
    if (*end != '\0') 
        error(1, 0, "Invalid number '%s'", str);
    if (n < low || n > high || errno == ERANGE) 
        error(1, 0, "Illegal value %s. %s must be in range [%ld, %ld]", str, argname, low, high);
    return n;
}

int main(int argc, char *argv[])
{
    if (argc < 2) error(1, 0, "Missing argument. Please specify the bitwidth.");
    
    int bitwidth = convert_arg(argv[1], 4, sizeof(long)*8, "Bitwidth");
    long min = signed_min(bitwidth);
    long max = signed_max(bitwidth);

    if (argc < 4)  {
        printf("%d-bit signed integer range\n", bitwidth);
        printf("min: %ld   %#018lx\n", min, min);
        printf("max:  %ld   %#018lx\n", max, max);
    } else {
        long sum = convert_arg(argv[2], min, max, "Operand");
        printf("%ld ", sum);
        for (int i = 3; i < argc; i++) {
            long next = convert_arg(argv[i], min, max, "Operand");
            printf("+ %ld ", next);
            sum = sat_add(sum, next, bitwidth);
        }
        printf("= %ld\n", sum);   
    }
    return 0;
}

