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
    int nlevels = 3;
    print_triangle(nlevels);
    return 0;
}
