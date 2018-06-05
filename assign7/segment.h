/* File: segment.h
 * ---------------
 * A simple interface to OS low-level allocator. Used to reserve a large
 * segment of memory which can be parceled out in response to malloc requests.
 */

#ifndef _SEGMENT_H_
#define _SEGMENT_H_
#include <stddef.h> // for size_t


/* Function: init_heap_segment
 * ---------------------------
 * This function is called to initialize the heap segment and allocate the
 * segment to hold total_size bytes. If init_heap_segment 
 * is called again, it discards the current heap segment and re-configures. 
 * The function returns the base address of the heap segment if successful 
 * or NULL if the initialization failed. The base address of the heap segment 
 * is always aligned to start on page boundary (page size is 4096 bytes).
 */
void *init_heap_segment(size_t total_size);



/* Functions: heap_segment_start, heap_segment_size
 * ------------------------------------------------
 * heap_segment_start returns the base address of the current heap segment
 * (NULL if no segment has been initialized).
 * heap_segment_size returns the current segment size in bytes.
 * The start and size define the current extent of the heap segment.
 */
void *heap_segment_start(void);
size_t heap_segment_size(void);


#endif
