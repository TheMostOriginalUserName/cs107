#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
enum { SORT_BY_NAME, SORT_BY_TYPE };
enum { EXCLUDE_DOT, INCLUDE_DOT };

// On the myth filesystem, the only file type information that is accurate is
// directory/not-directory. Other type info in struct direct is not reliable.
bool is_dir(const struct dirent *d)
{
    return d->d_type == DT_DIR;
}
int typesort(const struct dirent **a, const struct dirent **b) {
   
    
    if((*a)->d_type == (*b)->d_type && (*b)->d_type == DT_DIR) return alphasort(a,b);
    else if((is_dir(*a))&& !is_dir(*b)) return 0;
    else if((!is_dir(*a))&& is_dir(*b)) return 1;
    else return alphasort(a,b);
    
}
void ls(const char *dirpath, int filter, int order)
{
    struct dirent **namelist;
    int n = 0;
    DIR *d = opendir(dirpath);
    if(!d){ printf("./myls: cannot access %s: No such file or directory",dirpath); return;}
    closedir(d);
    if(order == 0)
    n = scandir(dirpath,&namelist,NULL,alphasort);
    else if(order == 1)
    n = scandir(dirpath,&namelist,NULL,typesort);
    if(n < 0) perror("scandir");
    else {
        if(!filter) {
            for(int i = 0; i < n; i++) {
                if(namelist[i]->d_name[0] == '.')
                    continue;
                else {
                    if(is_dir(namelist[i]))
                        printf("%s/ \n",namelist[i]->d_name);

                    else
                        printf("%s \n",namelist[i]->d_name);
                   free(namelist[i]);    
                }
            }
        }
        else {
            for(int i = 0; i < n; i++) 
            {

                 if(is_dir(namelist[i]))
                        printf("%s/ \n",namelist[i]->d_name);
                 else
                        printf("%s \n", namelist[i]->d_name);
                 free(namelist[i]);    
            }

        }
    }
    free(namelist);
}
        
int main(int argc, char *argv[])
{
    int order = SORT_BY_NAME;
    int filter = EXCLUDE_DOT;

    int opt;
    while ((opt = getopt(argc, argv, "az")) != -1) {
        switch (opt) {
            case 'a': filter = INCLUDE_DOT; break;
            case 'z': order = SORT_BY_TYPE; break;
            default: return 1;
        }
    }
    if (optind < argc -1) {
        for (int i = optind; i < argc; i++) {
            printf("%s:\n", argv[i]);
            ls(argv[i], filter, order);
            printf("\n");
        }
    } else {
        ls(optind == argc -1? argv[optind] : ".", filter, order);
    }
    return 0;
}
