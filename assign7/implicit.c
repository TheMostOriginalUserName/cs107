#include "allocator.h"
#include "debug_break.h"
#include <string.h>
#include <stdio.h>
#define BIN_MEM(p) ((void*)((unsigned long)p + sizeof(struct Bin)))
#define BIN_HEADER(p) ((void *)((unsigned long)p - sizeof(struct Bin)))
#define PTR_SIZE sizeof(struct Bin)
static size_t maxSize = 0;
static Bin *head  = NULL;
size_t roundup(size_t sz, size_t mult)
{
    return (sz + mult-1) & ~(mult-1);
}


bool myinit(void *segment_start, size_t segment_size)
{
    head = segment_start;
    head->next = NULL;
    maxSize = segment_size;
    return true;
}

void *mymalloc(size_t requestedsz)
{
   void *binHead;
   struct Bin * p,*newp;
   size_t reqsz = roundup(requestedsz,ALIGNMENT);
   if(requestedsz > MAX_REQUEST_SIZE) return NULL;     
   p = head;
    while(p->next){ 
        if (p->isEmpty && p->size >= reqsz+ PTR_SIZE) {
            binHead = BIN_MEM(p);
            p->isEmpty = false;//no need to split, maintain the original bin size
            return binHead;    
        }
        else {
            p = p->next;    
        }
    }
    

    binHead  = (struct Bin *)p + p->size;
    p->next = (struct Bin *)binHead;
    ((Bin *)binHead)->prev = p;
    ((Bin *)binHead)->next = NULL;
    newp = (struct Bin *)binHead;
    newp->size = reqsz + PTR_SIZE;
    newp->isEmpty = false;
    return BIN_MEM(newp);
}

void myfree(void *ptr)
{
    if(ptr == NULL) return;
    struct Bin * b = BIN_HEADER(ptr);
    b->isEmpty = true;
}

void *myrealloc(void *oldptr, size_t newsz)
{
    if(!oldptr) return mymalloc(newsz);
    struct Bin *b = BIN_HEADER(oldptr);
    void *ptr;
    ptr = mymalloc(newsz);
    if(!ptr) {
        return NULL;
    }
    memcpy(ptr,oldptr,b->size);
    struct Bin * newp = BIN_HEADER(ptr);
    newp->size = newsz + PTR_SIZE;
    newp->isEmpty = false;
    myfree(oldptr);
    return ptr;
}

bool validate_heap()
{
    if(!head) return false;
    return true;
    //future implementation
}
