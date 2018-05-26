#include "samples/prototypes.h"
#include <errno.h>
#include <error.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void print_last_n(FILE *fp, int n)
{
    //using circular queue;
    char **matrix = malloc(n * sizeof(char*));
    for(int i = 0; i < n; i++) {
        matrix[i] = malloc(200*sizeof(char));
        
    }
    char *str;
    int row_num = 0;
    while((str = read_line(fp)) != NULL) {
        
        if(row_num == n) {
            for(int i = 0; i < n - 1; i++) {
                strcpy(matrix[i],matrix[i+1]);
            }

            strcpy(matrix[n - 1],str);
        }
        else{
            strcpy(matrix[row_num++],str);
        }
        free(str);
    }
    for(int i = 0; i < n; i++) {
        printf("%s \n",matrix[i]);
        free(matrix[i]);    
    }
    free(matrix);

    //int count = 0;//count for lines
    //long int pos;
    //fseek(fp,0,SEEK_END);
    //char str[200];
    //pos = ftell(fp);
    //while(pos) {
    //    if(!fseek(fp,++pos,SEEK_SET)) {
    //       if(fgetc(fp) == '\n') {
    //           	if(count++ == n) break;	
    //        }			
    //    }
	//}
  // while(fgets(str,sizeof(str),fp)) printf("%s", str);
}
// ------- DO NOT EDIT ANY CODE BELOW THIS LINE (but do add comments!)  -------

int convert_arg(const char *str, int max)
{
    char *end;
    long n = strtol(str, &end, 10);
    if (*end != '\0') 
        error(1, 0, "Invalid number '%s'", str);
    if (n < 1 || n > max) 
        error(1, 0, "%s is not within the acceptable range [%d, %d]", str, 1, max);
    return n;
}

int main(int argc, char *argv[])
{
    int num = 10;

    if (argc > 1 && argv[1][0] == '-') {
        num = convert_arg(argv[1] + 1, 100000);
        argv++;
        argc--;
    }

    FILE *fp;
    if (argc == 1) {
        fp = stdin;
    } else {
        fp = fopen(argv[1], "r");
        if (fp == NULL) error(1, errno, "cannot access '%s'", argv[1]);
    }
    print_last_n(fp, num);
    fclose(fp);
    return 0;
}
