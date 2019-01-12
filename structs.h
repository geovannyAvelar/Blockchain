#include <stdint.h>
#include <time.h>

struct transaction {
    char * sender;
    char * recipient;
    uint32_t amount;
};

struct block {
    uint8_t index;
    time_t timestamp;
    struct transaction * transactions;
    uint64_t proof;
    char * previous_hash;
};

struct chain {
    struct block * blocks;
    int last_block_index;
};