#include "samples/prototypes.h"
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
int main(int argc, char *argv[], const char *envp[])
{
    const char *searchpath = get_env_value(envp, "MYPATH");
    if (searchpath == NULL) searchpath = get_env_value(envp, "PATH");
   // printf("PATH: %s\n", searchpath);
   // printf("argc: %d\n", argc);

    if (argc == 1) {
        char dir[PATH_MAX];
        const char *remaining = searchpath;

        printf("Directories in search path:\n");
        while (scan_token(&remaining, ":", dir, sizeof(dir))) {
            printf("%s\n", dir);
        }
    } else {
	for(int i = 1; i < argc; i++){
            char dir[PATH_MAX];
            const char* path = searchpath;		
	    while(scan_token(&path,":",dir,sizeof(dir))){
		struct dirent *de;
		DIR *dr = opendir(dir);
		if(dr == NULL) continue;
		    while((de = readdir(dr)) != NULL) {
				
			if(strcmp(de->d_name,argv[i]) == 0){
				
			    if(!strcmp(dir,".")|| !strcmp(de->d_name,".")||! strcmp(de->d_name,"..")) continue;
			      strcat(dir,"/");
			      printf("%s\n",strcat(dir,argv[i]));
			      goto flag;	
			}
			}
			
			closedir(dr);
		}	
		flag:;
	}
    }
    return 0;
}
