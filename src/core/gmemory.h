#ifndef GMEMORY_H
#define GMEMORY_H

#include "defines.h"

enum memory_tag {
    MEMORY_TAG_UNKNOW,
    MEMORY_TAG_APPLICATION,
    MEMORY_TAG_GAME,
    MEMORY_TAG_ENTITY,
    
    NUMBER_MEMORY_TAG_DO_NOT_USE
};

void init_gmemory();
void end_gmemory();

//API
//WARN: is it ok/better inline this functions?
//for inlining:
//The compiler may not perform inlining in such circumstances as: 
//- If a function contains a loop. (for, while and do-while) 
//- If a function contains static variables. 
//- If a function is recursive. 
//- If a function return type is other than void, and the return statement doesn’t exist in a function body. 
//- If a function contains a switch or goto statement. 

static inline void* gallocate(unsigned long long int size, memory_tag tag);
static inline void gfree(void* block, unsigned long long int size, memory_tag tag);

//overload a new new operator to use gallocate() (same for delete)
//https://stackoverflow.com/questions/58900136/custom-allocator-including-placement-new-case

//...
//zero
//copy
//set

//debug
char* getGMemoryUsageStr();

#endif 
