#include "samples/prototypes.h"
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// initial estimate of number of uniq lines
// resize-as-you-go, add in increments of 100
#define ESTIMATE 100
static int used_row = 0;
static int buffer_row = ESTIMATE;
void print_uniq_lines(FILE *fp)
{
    char **line = malloc(ESTIMATE*sizeof(char*)*ESTIMATE);
    for(int i = 0; i < ESTIMATE; i++){
        line[i]  = malloc(ESTIMATE*sizeof(char));
     }
    
    int *freq = malloc(ESTIMATE*sizeof(int));
    for(int i = 0; i<ESTIMATE; i++) {
        freq[i] = 0;
    }
    char *cmp = *line;
    char *str;
    int count = 0;
    while((str = read_line(fp))!= NULL ) {
           cmp = *line;
           for(count = 0; count < used_row; count++) {
               cmp = line[count];     
               if(strcmp(cmp,str)) {
   //                printf("here I for now have a uniq name: %s\n", str);
                   continue;
               }
               else {
                   freq[count]++;
                   goto clear;
               }
            
           }
           
           if(count >= used_row) {
  //             printf("I have used %d row, and I have %d in total\n", used_row,buffer_row);
               if(used_row == buffer_row) {
                    char **temp = realloc(line,(buffer_row+100)*sizeof(char*));
                    int *freq_temp = realloc(freq,(buffer_row+100)*sizeof(int));
                    for(int i = 0; i < ESTIMATE; i++) {
                        temp[used_row+i] = malloc(ESTIMATE*sizeof(char));    
                        freq_temp[used_row+i] = 0;
                    }
                    
                    line  = temp;
                    freq = freq_temp;
                     buffer_row +=100;   
               }
               strcpy(line[used_row],str);
               freq[used_row] = 1;
               used_row++;
         }
         clear:
         free(str);
    }
    for(int i = 0; i < used_row; i++) {
        printf("      %d %s\n",freq[i],line[i]);
        free(line[i]);    
    }

    free(str);
    free(line);
    free(freq);
    
}


// ------- DO NOT EDIT ANY CODE BELOW THIS LINE (but do add comments!)  -------

int main(int argc, char *argv[])
{
    FILE *fp;

    if (argc == 1) {
        fp = stdin;
    } else {
        fp = fopen(argv[1], "r");
        if (fp == NULL) error(1, errno, "cannot access '%s'", argv[1]);
    }
    print_uniq_lines(fp);
    fclose(fp);
    return 0;
}
