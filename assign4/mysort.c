#include "samples/prototypes.h"
#include <error.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#define MAX_LINE_LEN 4096
#define MIN_NLINES 100
static size_t used_line = 0;
static size_t buffer_line = MIN_NLINES;
typedef int (*cmp_fn_t)(const void *p, const void *q);

int cmp_pstr(const void *p, const void *q)
{
   const char *pp = *(const char **)p;
   const char *qq= *(const char **)q;
   int rt = strcmp(pp,qq);
   if( rt < 0) return -1;
   else if( rt > 0) return 1;
   return 0;
}


int cmp_pstr_len(const void *p, const void *q)
{
   
   const char * pp = *(const char **)p;
   const char * qq = *(const char **)q;
   int sign = strlen(pp) - strlen(qq);
   if(sign < 0) return -1;
   else if(sign > 0) return 1;
   return 0; 
}

int cmp_pstr_numeric(const void *p, const void *q)
{
    const char * pp = *(const char **)p;
    const char * qq = *(const char **)q;
    int pv = atoi(pp);
    int qv = atoi(qq);
    return pv - qv; 
}
void sort_lines(FILE *fp, cmp_fn_t cmp, bool uniq, bool reverse)
{   
    
    char line[MAX_LINE_LEN];
    
    size_t selem = sizeof(char*);
    char **file = malloc(MIN_NLINES * sizeof(char *));
    while(fgets(line, MAX_LINE_LEN, fp)!= NULL) {
        char *s = strdup(line);
        if(uniq) {
             for(int i = 0; i < used_line; i++) {
                 if(!strcmp(line,file[i])){
                      free(s);
                      goto loop;
                 
                 }
             }
             binsert(&s, file, &used_line, selem, cmp);
        } else {
            file[used_line] = s;
            used_line += 1;
        }
        loop:
        if (used_line == buffer_line) {
            char ** temp = realloc(file, 2 * buffer_line * sizeof(char *));
            file = temp;
            buffer_line *= 2;
        }
   }
   if(!uniq) {
       qsort(file, used_line, selem, cmp);
   }
   if(reverse) {
       for(int i = used_line - 1; i >=0; i--) {
           printf("%s",file[i]);    
           free(file[i]);
        }     
   }
   else {
       for(int i = 0; i < used_line; i++)    
       {
           printf("%s",file[i]);
           free(file[i]);
       }
       
   }
   free(file);
 }

int main(int argc, char *argv[])
{
    cmp_fn_t cmp = cmp_pstr;
    bool uniq = false, reverse = false;

    int opt;
    while ((opt = getopt(argc, argv, "lnru")) != -1) {
        switch (opt) {
            case 'l': cmp = cmp_pstr_len; break;
            case 'n': cmp = cmp_pstr_numeric; break;
            case 'r': reverse = true; break;
            case 'u': uniq = true; break;
            default: return 1;
        }
    }

    FILE *fp = stdin;
    if (optind < argc) {
        fp = fopen(argv[optind], "r");
        if (fp == NULL) error(1, 0, "%s: no such file", argv[optind]);
    }
    sort_lines(fp, cmp, uniq, reverse);
    fclose(fp);
    return 0;
}
