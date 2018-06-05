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
void add(Bin * b){
    b->next = NULL;
    b->prev = NULL;
    if(!head || (unsigned long) head > (unsigned long)b) {
        if(head) {
            head->prev = b;    
        }    
        b->next = head;
        head = b;
    } else {
        Bin * cur = head;
        while(cur->next &&(unsigned long) cur->next <(unsigned long)b) {
            
            cur = cur->next;
        }
        if(cur->next) {
           
            b->next = cur->next;
            cur->next->prev = b;
        }
            cur->next = b;
            b->prev = cur;   
        
        
    }
    
}
void merge(Bin * ptr1, Bin * ptr2) {
    ptr1->next = ptr2->next;
    if(ptr2->next)
    ptr2->next->prev = ptr1;
    ptr1->size += ptr2->size;
    ptr2->next = NULL;
    ptr2->prev = NULL;    
    
}
bool myinit(void *segment_start, size_t segment_size)
{
//    if(segment_size == 0 || segment_size > MAX_REQUEST_SIZE)return false;
    head = segment_start;
    maxSize = segment_size;
    head->next = NULL;
    return true;
}

void *mymalloc(size_t requestedsz)
{
   void *binHead;
   struct Bin * p,*newp;
   size_t reqsz = roundup(requestedsz,ALIGNMENT);
   if(requestedsz > MAX_REQUEST_SIZE) return NULL;     
   p = head;
   while(p->next!=NULL) {
        if(p->isEmpty && p->next->isEmpty) {
            merge(p,p->next);    
        }
        else if(p->size >= reqsz + PTR_SIZE && p->isEmpty) {
            binHead = BIN_MEM(p);
            p->isEmpty = false;//no need to split, maintain the original bin size
            return binHead;    
        }
        else {
            p = p->next;    
        }
//        printf("At line %d, p is NULL\n",count);
    }
    
    //loop over no suitable bin
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
    if(b->size > newsz + PTR_SIZE) {
    // resizes smaller: in place
        struct Bin *newBin =(struct Bin *) b + newsz;
        add(newBin);
        newBin->isEmpty = true;
        newBin->size = b->size - newsz-PTR_SIZE;
    }
    void *ptr;
    ptr = mymalloc(newsz);
    if(!ptr) {
        return NULL;
    }
    memmove(ptr,oldptr,b->size);
    struct Bin * newp = BIN_HEADER(ptr);
    newp->size = newsz + PTR_SIZE;
    newp->isEmpty = false;
    myfree(oldptr);
    return ptr;

}

bool validate_heap()
{
    // check your internal structures here!
    // return true if all ok, false otherwise
    // can also use breakpoint() to stop in debugger, e.g.
    //if (something_is_wrong) breakpoint();
    if(!head)
    return false;
    return true;
    //future implementation  needed
}
