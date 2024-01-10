// single-level cache simulator and the memory underneath it
// run: ./cachesim <filename> <cache size kB> <associativity> <block size B>
// example: ./cachesim trace.txt 32 1 32

// Addresses are 24 bits = 3 bytes, addresses range from 0 to 2^24 - 1 (16 MB of addressable memory). Machine is byte-addressable and big-endian. The cache size, associativity, and block size are all powers of 2. Cache size will not be larger than 2MB, block size no bigger than 1024B, and no access will be larger than block size. No cache acces will span multiple blocks (i.e. each cache access fits within a single block)

// Cache is write-through and write-no-allocate. The cache is initially empty.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define DEBUG 0
#define MAX_VALUE_SIZE 8
#define MAX_ADDRESS_SIZE 24
#define MEMORY_SIZE (1ULL << 33)

//********** CACHE STRUCTURE **********//
typedef struct
{
    int valid; // 1 if valid, 0 if invalid
    int tag;
    // have byte array for value
    char value[MAX_VALUE_SIZE];
    time_t LRU; // FIXME: use time_t
} cacheEntry;

typedef struct
{
    cacheEntry *pairs; // array of cache entries to hold multiple ways in a set
    int ways;
    int size;
} Cache;
//********** END CACHE STRUCTURE **********//

//********** GLOBAL VARIABLES **********//
FILE *file;
Cache *cache;
char* mainMemory;
int CACHE_SIZE = 0;
int ASSOCIATIVITY = 0;
int BLOCK_SIZE = 0;
int OFFSET_BITS = 0;
int INDEX_BITS = 0;
int TAG_BITS = 0;
int SETS = 0;
int FRAMES = 0;
time_t globalTime = 0;

//********** CACHE FUNCTIONS **********//
void initializeCache(int argc, char const *argv[]); // initialize cache
void get(int address, int loadSize);                // get value from cache
void put(int address, char data[], int size);        // store value in cache
int log2cache(int n);                               // log base 2 of n
int getTag(int address);                            // get tag from address
int getBlockOffset(int address);                    // get block offset from address
int getIndex(int address);                          // get index from address
int getValueFromStringHex(char *value);             // get value from string hex
void print(char data[], int size, int blockOffset); // print data
int isInCache(int index, int tag, int size);        // check if tag is in cache
int printfromMemory(int address, int size);         // print from main memory
//********** END CACHE FUNCTIONS **********//

int main(int argc, char const *argv[]){
    initializeCache(argc, argv);
    file = fopen(argv[1], "r");
    char word[512];
    int count = 0;
    while(fscanf(file, "%s", word)!=EOF){
        int isStore = strcmp(word, "store");
        int address;
        fscanf(file,"%x",&address); // read address
        int size;
        fscanf(file,"%d",&size); // read numBytes

        if(isStore==0){
            char storeData[size];
            char dataString[100];
            fscanf(file,"%s",dataString); // read data
            for (int i = 0; i < size; i++){
                sscanf(dataString+(2*i), "%02hhx", &storeData[i]);
            }
            put(address, storeData, size); // FIXME: define miss and hit cases
        }else{
            get(address, size); // FIXME: define miss and hit cases
        }
    }
    return 0;
}

void initializeCache(int argc, char const *argv[]){
    // get file from arguments
    CACHE_SIZE = atoi(argv[2]);
    ASSOCIATIVITY = atoi(argv[3]);
    BLOCK_SIZE = atoi(argv[4]);
    globalTime=time(NULL);

    // initialize cache
    FRAMES = CACHE_SIZE * 1024 / BLOCK_SIZE;
    SETS = FRAMES / ASSOCIATIVITY;

    cache = (Cache *)calloc(SETS,sizeof(Cache));
    for (int i = 0; i < SETS; i++){
        // initialize cache
        cache[i].ways = ASSOCIATIVITY;
        cache[i].size = 0;
        cache[i].pairs = (cacheEntry *)calloc(ASSOCIATIVITY,sizeof(cacheEntry));
        for (int j = 0; j < ASSOCIATIVITY; j++){
            cache[i].pairs[j].valid = 0;
        }

        if (DEBUG){
            printf("%d %d %d\n", i, cache[i].size, cache[i].ways);
        }
    }
    OFFSET_BITS = log2cache(BLOCK_SIZE);
    INDEX_BITS = log2cache(SETS);
    TAG_BITS = 24 - OFFSET_BITS - INDEX_BITS;

    // initialize main memory
    mainMemory = (char *)calloc(sizeof(char), MEMORY_SIZE);
}

void get(int address, int loadSize){
    int tag = getTag(address);                 // tag === tag which is how we index into cache
    int blockOffset = getBlockOffset(address); // block offset === offset
    int index = getIndex(address);             // index === set

    if(DEBUG){
        printf("%x %d %d %d\n", address, tag, blockOffset, index);
    }

    // check if tag is in cache
    int exists = isInCache(index, tag, loadSize);
    if(DEBUG) printf("exists: %d\n", exists);
    if (exists){
        // if tag is in cache, print from cache
        for (int i = 0; i < cache[index].size; i++){
            if(cache[index].pairs[i].tag == tag){
                cache[index].pairs[i].LRU = globalTime;
                globalTime++;
            }
        }
        
        printf("load 0x%x hit ", address);
        printfromMemory(address, loadSize);
        printf("\n");
    }else{
        // if tag is not in cache, add to main memory and set valid bit to 1
        int currentSize = cache[index].size;
        if(currentSize<ASSOCIATIVITY){
            // if there is space in the set, add to cache
            cache[index].pairs[currentSize].valid = 1;
            cache[index].pairs[currentSize].tag = tag;
            cache[index].pairs[currentSize].LRU = globalTime;
            cache[index].size++;
            globalTime++;
        }else{
            // if there is no space in the set, evict LRU
            int LRU = globalTime+1;
            int LRUIndex = 0;
            for (int i = 0; i < currentSize; i++){
                if(cache[index].pairs[i].LRU < LRU){
                    LRU = cache[index].pairs[i].LRU;
                    LRUIndex = i;
                }
            }
            cache[index].pairs[LRUIndex].valid = 1;
            cache[index].pairs[LRUIndex].tag = tag;
            cache[index].pairs[LRUIndex].LRU = globalTime;
            globalTime++;
            
        }
        printf("load 0x%x miss ", address);
        printfromMemory(address, loadSize);
        printf("\n");
    }
        
}

void put(int address, char data[], int size){
    int tag = getTag(address);                 // tag === tag which is how we index into cache
    int blockOffset = getBlockOffset(address); // block offset === offset
    int index = getIndex(address);             // index === set

    // check if tag is in cache
    int exists = isInCache(index, tag, size);
    if(DEBUG) printf("exists: %d\n", exists);
    if (exists){
        // if tag is in cache, update on main memory and update LRU
        for (int i = 0; i < size; i++){
            mainMemory[address+i] = data[i];
        }
        int currentSize = cache[index].size;
        for (int i = 0; i < currentSize; i++){
            if(cache[index].pairs[i].tag == tag){
                cache[index].pairs[i].LRU = globalTime;
                globalTime++;
            }
        }
        printf("store 0x%x hit\n", address);
    }else{
        // if tag is not in cache, add to main memory
        for(int i = 0; i < size; i++){
            mainMemory[address+i] = data[i];
        }
        printf("store 0x%x miss\n", address);
    }
}

int log2cache(int n){
    int r = 0;
    while (n >>= 1)
        r++;
    return r;
}

int getTag(int address){
    return address >> (OFFSET_BITS + INDEX_BITS);
}
int getBlockOffset(int address){
    return address & ((1 << OFFSET_BITS) - 1);
}
int getIndex(int address){
    return (address >> OFFSET_BITS) & ((1 << INDEX_BITS) - 1);
}

int isInCache(int index, int tag, int size){
    for (int i = 0; i < cache[index].size; i++){
        if(cache[index].pairs[i].valid == 1){
            if (cache[index].pairs[i].tag == tag){
                return 1;
            }
        }
    }
    return 0;
}
int printfromMemory(int address, int size){
    for (int i = 0; i < size; i++){
        printf("%02hhx", mainMemory[address+i]);
    }
    return 0;
}