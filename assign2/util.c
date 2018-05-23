#include "samples/prototypes.h"
#include <string.h>


const char *get_env_value(const char *envp[], const char *key)
{
  	size_t size = 0;
         const char * move = key;

	while(*move != '\0') {
		move++;
		size++;
	}
	
	int lon = 0;
	while(envp[++lon] != '\0');
	
	for(int i = 0; i < lon; i++) {
		int index = 0;
		while(envp[i][++index] != '=');
		if(strncmp(key,envp[i],index) == 0) {
			return (envp[i] + index + 1);
		}
	}
	return NULL;
	
}


bool scan_token(const char **p_input, const char *delimiters, char buf[], size_t buflen)
{

	const char * start;
	start  = *p_input;
	
	int end = 0;
	if(*start == '\0') return false;	
	int i = 0;
	end = strcspn(start,delimiters);
	while(end == 0 && *start != '\0'){
		end = strcspn(++start,delimiters);
	}
	if(*start == '\0') return false;
	while( i != end  && strlen(buf) != buflen - 1){
		buf[i] = *start;
		i++;
		start++;
	}
	*p_input = start;
	buf[i] = '\0';
	
    return true;
}
