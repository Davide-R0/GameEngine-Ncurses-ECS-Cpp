#include "gmemory.h"
#include "logger.h"

//#include <stdio.h>      /* printf, scanf, NULL */
#include <cstring>
#include <stdlib.h>     /* malloc, free, rand */

//#include "platform/platform.h"

//save the number of all allocations
struct memory_stats {
    unsigned long long int total_allocated;
    unsigned long long int total_tagged_allocated[NUMBER_MEMORY_TAG_DO_NOT_USE];
};

static struct memory_stats stats;

void init_gmemory() {
    //TODO: zero all the memory
    stats.total_allocated = 0;
    stats.total_tagged_allocated[0] = 0;
    // ....
}

void end_memory() {

}

//TODO: place the verification statments and the memory size trace in a compile specific guard, so that in the final realise are not present

void* gallocate(unsigned long long int size, memory_tag tag) {
    if (tag == MEMORY_TAG_UNKNOW) GWARN("gallocate called with MEMORY_TAG_UNKNOW, reclass this");

    stats.total_allocated += size;
    stats.total_tagged_allocated[tag] += size;

    //TODO: memory allignment
    //void* block = platform_allocate(size, false);
    void* block = malloc(size);
    //zero the memory created, so that each memory created is clean
    //inline? platform_zero_memory(block, size);
    memset(block, 0, size);
    return block;
    
}

void gfree(void* block, unsigned long long int size, memory_tag tag) {
    if (tag == MEMORY_TAG_UNKNOW) GWARN("gfree called with MEMORY_TAG_UNKNOW, reclass this");
    
    stats.total_allocated -= size;
    stats.total_tagged_allocated[tag] -= size;
    
    //TODO: memory allignment
    //inline? platform_free(block, false);
    free(block);

}

//...
//...
//...


//debug
char* getGMemoryUsageStr() {
    //print the memory usage in mB kB or gB...
    return nullptr;
}
