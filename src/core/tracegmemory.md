``` cpp

//allocation tracking
typedef struct {
unsigned int 	address;
unsigned int 	size;
char	file[64];
unsigned int	line;
} ALLOC_INFO;

/*

typedef std::list<ALLOC_INFO*> AllocList;

AllocList *allocList;

void AddTrack(unsigned int addr,  unsigned int asize,  const char *fname, unsigned int lnum)
{
ALLOC_INFO *info;

if(!allocList) {
allocList = new(AllocList);
}

info = new(ALLOC_INFO);
info->address = addr;
strncpy(info->file, fname, 63);
info->line = lnum;
info->size = asize;
allocList->insert(allocList->begin(), info);
};

void RemoveTrack(unsigned int addr)
{
AllocList::iterator i;

if(!allocList)
return;
for(i = allocList->begin(); i != allocList->end(); i++)
{
if((*i)->address == addr)
{
allocList->remove((*i));
break;
}
}

}*/

#ifndef NDEBUG
inline void * __cdecl operator new(unsigned int size, const char *file, int line) {
    void *ptr = (void *)malloc(size);       //TODO: use custom allocator
    AddTrack((unsigned int)ptr, size, file, line);
    return(ptr);
};
inline void __cdecl operator delete(void *p) {
    RemoveTrack((unisgned int)p);
    free(p);
};
#endif



/////////////////////////////////////////////////
#define REDZONE_SIZE 4
/*****************************/
/* main static hash table    */
/*****************************/
static _HASH_TABLE _hashtable;
/* a hack to work around limitations with overriding the C++ delete operator */
const char *_mt_src_file;
const char *_mt_src_func;
int _mt_src_line;
void MT_init_hash()
{
    _hashtable.total_rows              = INITIAL_HASH_SZ;
    _hashtable.rows_used               = 0;
    _hashtable.total_entries           = 0;
    _hashtable.next_serial_num         = 1;
    _hashtable.total_bytes             = 0;
    _hashtable.err_total_incompatible  = 0;
    _hashtable.err_total_unallocated   = 0;
    _hashtable.current_bit_mask        = INITIAL_HASH_SZ-1;
    _hashtable.hash_array = (_HASH_ENTRY**) calloc(INITIAL_HASH_SZ, sizeof (_HASH_ENTRY*));
    _hashtable.error_array = NULL;
    _hashtable.leaked_list = NULL;
    if (!_hashtable.hash_array)
    {
        fprintf (stderr, "MemTracker: Internal Error: main hash table init error - calloc()");
        exit (2);
    }

    atexit(MemTrackerFinalReport);
}
int MT_should_double() /* hash table automagically doubles when needed */
{
    if(_hashtable.total_entries > _hashtable.total_rows-1) return 1;
    return 0;
}

int MT_add_entry(unsigned long int address, unsigned int size, const char * TLA, unsigned int source_line,  const char* func_name, const char* file_name) {
    unsigned int all_bits, i;
    _HASH_ENTRY* p_new_entry, *temp;

    if (!_hashtable.hash_array) MT_init_hash (); /* automagic init() */

    if (MT_should_double()) MT_double_hash();

    if ( MT_find_entry(address)  ) /* O/S or internal error */
    {
        fprintf (stderr, "MemTracker: Table Error: Address %lu already in use! %s:%u func:%s()\n",
                address, file_name, source_line, func_name);

        exit(2);
    }

    all_bits = MT_gen_hash_bits (address);
    i = all_bits & _hashtable.current_bit_mask;     //?????
    p_new_entry = (_HASH_ENTRY*) calloc(1, sizeof (_HASH_ENTRY) );
    if (!p_new_entry)
    {
        fprintf (stderr, "MemTracker: Internal error: calloc failed for new hash entry\n");
        exit (2);
    }
    p_new_entry->address      = address;
    p_new_entry->hash_allbits = all_bits;
    p_new_entry->sequence_num = _hashtable.next_serial_num++;
    p_new_entry->size_mem     = size;
    p_new_entry->source_line  = source_line;
    p_new_entry->next         = NULL;
    strncpy (p_new_entry->allocation_TLA, TLA,3);

    /* insert new entry on top of stack*/

    temp = _hashtable.hash_array[i];
    if (!temp){
        _hashtable.rows_used++;
        _hashtable.hash_array[i] = p_new_entry;
    } else {
        p_new_entry->next = temp;
        _hashtable.hash_array[i] = p_new_entry;
    }

    p_new_entry->function_name =(char*) malloc(strlen(func_name)+1);
    if (!p_new_entry->function_name)
    {
        fprintf (stderr, "MemTracker: Internal error: malloc failed for function name\n");
        exit (2);
    }

    strcpy(p_new_entry->function_name, func_name);

    p_new_entry->file_name =(char*) malloc(strlen(file_name)+1);
    if (!p_new_entry->file_name)
    {
        fprintf (stderr, "MemTracker: Internal error: malloc failed for file name\n");
        exit (2);
    }

    strcpy(p_new_entry->file_name, file_name); 

    _hashtable.total_entries++;
    _hashtable.total_bytes += size;
    return 1; /* success */
}

void MT_AddError(const char* allocation_TLA,const char* deallocation_TLA,unsigned int source_line,const char* function_name,const char* file_name) {
    _ERRORS *ptr = NULL;
    ptr = (_ERRORS *) calloc(1,sizeof(_ERRORS));
    if(! (allocation_TLA)) {
        // Then this is not a mismatch, it is a double deallocation call.
        ptr->allocation_TLA = NULL;
        ptr->deallocation_TLA = (char *) calloc(strlen(deallocation_TLA)+1,sizeof(char));
        strcpy(ptr->deallocation_TLA,deallocation_TLA);
    } else {
        ptr->allocation_TLA = (char *) calloc(strlen(allocation_TLA)+1,sizeof(char));
        strcpy(ptr->allocation_TLA,allocation_TLA);
        ptr->deallocation_TLA = 
            (char *) calloc(strlen(deallocation_TLA)+1,sizeof(char));
        strcpy(ptr->deallocation_TLA,deallocation_TLA);
    }
    ptr->source_line = source_line;
    ptr->function_name = (char *) calloc(strlen(function_name)+1,sizeof(char));
    strcpy(ptr->function_name,function_name);
    ptr->file_name = (char *) calloc(strlen(file_name)+1,sizeof(char));
    strcpy(ptr->file_name,file_name);

    _ERRORS *walker = NULL;
    _ERRORS *last = NULL;

    if(! _hashtable.error_array) {// first call
        _hashtable.error_array = ptr;
        _hashtable.error_array->next = NULL;
        return;
    }
    for(walker = _hashtable.error_array;walker;walker = walker->next) {
        if(source_line < walker->source_line) {
            if(!last) { // The line is less then the first one.
                ptr->next = walker;
                _hashtable.error_array = ptr;

            } else {
                last->next = ptr;
                ptr->next = walker;

            }
            return;
        }
        last = walker;
    }
    // If it's the biggest line so far.
    last->next = ptr;
    ptr->next = NULL;
}

int MT_delete_entry (  unsigned long int address,  const char* TLA, int line, const char* func, const char* file_name ) {
    _HASH_ENTRY*  mover = NULL;
    _HASH_ENTRY*  prev  = NULL;
    unsigned int i;

    if (_hashtable.hash_array == NULL )
        return (1); /* Probable cause: MemTrackerFinalReport() called too early */
    /* C++ is continuing to run destructor methods */
    /* I consider that "ok" */

    i = MT_gen_hash_array_index(address);

    if (!_hashtable.hash_array[i])
    {
        /* fprintf (stderr, "MemTracker: %s:%u func:%s()  Deallocator called but 0x%lX not allocated!\n", */
        /*       file_name, line, func, address); */
        MT_AddError(NULL,TLA,line,func,file_name);
        _hashtable.err_total_unallocated++;
        return 0; /* fail */
    }
    mover  =  _hashtable.hash_array[i];
    /* zap the entry on the stack if we can */
    while (mover) {
        if (mover->address == address) {
            if ( !MT_check_redzone((void *)address, mover->size_mem)) {
                fprintf (stderr, "MemTracker: %s:%u func:%s()  Heap corruption before deallocator called!\n", file_name, line, func);
            }
            if ( MT_is_deallocater_wrong(mover->allocation_TLA, TLA) ) {

                /* fprintf (stderr, "MemTracker: %s:%u func:%s()  Deallocator %s not compatible with %s!\n", */

                /*       file_name, line, func, mover->allocation_TLA, TLA); */

                MT_AddError(mover->allocation_TLA,TLA,line,func,file_name);
                _hashtable.err_total_incompatible++;

                /* keep going..the error has been reported..user code may still run! */

                /* we let the user program do what it can */

            }

            _hashtable.total_bytes -= mover->size_mem;
            if (!prev)

                _hashtable.hash_array[i] = mover->next;

            else prev->next = mover->next;
            if ( !_hashtable.hash_array[i] )

                _hashtable.rows_used--;
            _hashtable.total_entries--;

            MT_free_hentry (mover);
            return 1; /* success */

        }
        prev  = mover;
        mover = mover->next;
    }

    fprintf (stderr, "MemTracker: %s:%u func:%s()  Deallocator called but 0x%lX not allocated!\n",
            file_name, line, func, address);


    _hashtable.err_total_unallocated++;
    return 0;       /* fail */
}

void MT_init_redzone(void *address, unsigned long int size ) {
    char *start = (char *)address + size - REDZONE_SIZE;
    strncpy(start, REDZONE_STR, REDZONE_SIZE);
}

#ifdef __cplusplus
/*this appears to be a very slightly documented interface and */
/*the ramifications of this are unknown*/
void operator delete(void* pMem, char* pszFilename, int nLine)
{
    fprintf (stderr, "WOW, WOWIE ***********\n");
    fprintf (stderr, "This function shouldn't be called! \n");
    fprintf (stderr, "address=0x%lX name=%s, line=%d\n", (unsigned long int)pMem, pszFilename, nLine);
    free(pMem); /* http://msdn.microsoft.com/en-us/library/cxdxz3x6%28VS.80%29.aspx */
}
void* operator new(size_t sizee, unsigned int line,  const char* func_name, const char* file_name) {
    void *ptr;
    size += REDZONE_SIZE;

    if ((ptr = (void *) malloc(size)) == NULL)
    {
        perror("C++ function \"new\" failed to get memory!");
        exit(1);
    }
    MT_add_entry((unsigned long int)ptr, size, "NEW", line, func_name, file_name);
    MT_init_redzone(ptr, size);
    return ptr;
}
void* operator new [] (size_t size, unsigned int line, const char* func_name, const char* file_name) {
    void *ptr;
    size += REDZONE_SIZE;

    if ((ptr = (void *) malloc(size)) == NULL)
    {
        perror("C++ Vector form of \"new\" failed to get memory!");
        exit(1);
    }

    MT_add_entry((unsigned long int)ptr, size, "VEC", line, func_name, file_name);
    MT_init_redzone(ptr, size);
    return ptr;
}
/* C++ scalar delete */
/* The default delete "throws" (), I should claim the same     */
/* even if I don't throw anything! Some compilers require this */
void operator delete(void* ptr) throw () {
    if(MT_delete_entry((unsigned long int)ptr ,"DEL", _mt_src_line, _mt_src_func, _mt_src_file))
        free(ptr);
}
/* C++ vector delete */
/* The default delete[] "throws" (), I should claim the same    */
/* even if I don't throw anything!  Some compilers require this */
void operator delete [] (void* ptr) throw () {
    if(MT_delete_entry((unsigned long int)ptr, "VDE", _mt_src_line, _mt_src_func, _mt_src_file))
        free(ptr);
}
#define new new(__LINE__, __func__, __FILE__)
#define delete _mt_src_file=__FILE__, _mt_src_func=__func__, _mt_src_line=__LINE__, delete
#endif
/************* end of C++ specific  ************/
//#define malloc(size)       MT_Malloc (size, __LINE__, __func__, __FILE__)
//#define calloc(n,size)     MT_Calloc (n, size, __LINE__, __func__, __FILE__)
//#define free(adr)          MT_Free   (adr, __LINE__, __func__, __FILE__)
//#define realloc(ptr, size) MT_Realloc(ptr, size, __LINE__, __func__, __FILE__);
////////////////////////////////////////////////////////////////////////////////

```
