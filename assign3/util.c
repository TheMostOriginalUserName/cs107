#include "samples/prototypes.h"
#include <assert.h>
#include <stdlib.h>
// initial allocation will be for min size, if not big enough, doubles
// to 64, then 128, then 256, etc. as needed to accommodate the entire line
// resize-as-you-go, doubling each time
#define MINIMUM_SIZE 32
static int buffer_size = 0;
static int used_size = 0;

char *read_line(FILE *fp)
{
    buffer_size = MINIMUM_SIZE;
    assert(buffer_size >= used_size);
    char *dst = malloc(MINIMUM_SIZE);
    char c;
    if(fp == NULL) return NULL;
    while(( c = fgetc(fp)) != EOF) {
   		if(c == '\n')  break;
		if(buffer_size == used_size){
			char *temp = realloc(dst,buffer_size*2*sizeof(char));
			assert(temp != NULL);
			dst = temp;
			buffer_size *=2;
		}
		dst[used_size]  = c;
		used_size++;
   	 }
    if(c == EOF) return NULL;
    dst[used_size] = '\0';
    used_size = 0;
    buffer_size = 0;
    return dst; // replace with your implementation 
}
