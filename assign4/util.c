#include "samples/prototypes.h"
#include <stdio.h>
#include <string.h>
void *binsert(const void *key, void *base, size_t *p_nelem, size_t width, int (*compar)(const void *, const void *))
{
    void *p = base;
    void *b = base;
    for(size_t nremain = *p_nelem; nremain != 0; nremain >>=1) {
        p = (char *)b + (nremain>>1)*width;
        int sign = compar(key,p);   
        if(sign == 0) return p;
        if(sign > 0) {
            b = (char *) p + width;
            nremain--; 
        } 
        
    }
    if(*p_nelem == 0) {
        memcpy((char *)base,(char *)key,width);
        *p_nelem= *p_nelem + 1;
        return (char *)base;
    
    }
    *p_nelem= *p_nelem + 1;
    int num = compar(key,(char*)p);
    size_t pos = ((char *)p - (char *)base)/width;
    if(num > 0) //key > p
    {
        memmove((char*)p + 2*width,(char*)p + width,(*p_nelem - pos - 2)*width);
        memmove((char*)p + width,(char*)key,width); 
     return (char *)p + width;
    }
    else {
       memmove((char *)p + width,(char *)p,(*p_nelem - pos - 1)*width);
       memmove((char *)p, (char*)key,width);
       return p;
    }

}


