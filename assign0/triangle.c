/* File: triangle.c
 * ----------------
 * Outputs an ascii representation of the Sierpinski triangle.
 *
 * The pattern of stars is generated using a bitwise AND 
 * on the coordinates. This works due to the relationship
 * between the fractal and Pascal's triangle.
 * https://en.wikipedia.org/wiki/Sierpinski_triangle
 */

#include <stdio.h>
#include <stdlib.h>
void print_triangle(int nlevels)
{
    int size = 1 << nlevels;

    for (int row = size - 1; row >= 0; row--) {
        for (int col = 0; col < row; col++) {
            printf(" ");
        }
	for (int col = 0; col + row < size; col++) {
		    printf("%c ", (col & row) ? ' ' : '*');
		}
		printf("\n");
	    }
	}

int main(int argc, char *argv[])
{
    int nlevels = (argc == 0) ? atoi(argv[1]) : 3;
    if(nlevels > 8) {
	printf("The size is too large to print, please choose a smaller size.\n ");
	return 0;
	}	
    print_triangle(nlevels);
    return 0;
}
