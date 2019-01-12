#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#include "structs.h"
#include "hash.h"

void new_transaction(char * sender, char * recipient, uint32_t amount, struct block * new_block, struct block * last_block) {
    struct transaction t;
    t.sender = sender;
    t.recipient = recipient;
    t.amount = amount;

    last_block->transactions[new_block->index + 1] = t; 
}

void new_block(struct chain * chain, int proof) {
    struct block block;

    if(chain->last_block_index == -1) {
        block.index = 0;
        chain->last_block_index = 0;
    } else {
        struct block last_block = chain->blocks[chain->last_block_index];
        char * hash = (char *) malloc(sizeof(char) * 33);
        generate_block_md5(&last_block, hash);

        chain->last_block_index = chain->last_block_index + 1;
        block.index = chain->last_block_index;
        block.previous_hash = hash;
    }

    block.proof = proof;
    block.timestamp = time(NULL);
    block.transactions = (struct transaction *) malloc(sizeof(struct transaction *) * 1024);

    chain->blocks[chain->last_block_index] = block;
}

bool proof_of_work(int x, int y) {
    int product = x * y;
    char buffer[5];
    sprintf(buffer, "%d", product);

    char hash[33];

    generate_string_md5(&buffer, &hash);

    if(hash[31] == '0') {
        return 1;
    }

    return 0;
}

void mine(struct chain * chain) {
    struct block last_block = chain->blocks[chain->last_block_index];

    int proof = 0;
    while(proof_of_work(last_block.proof, proof) == 0) {
        proof++;
    }

    new_block(chain, proof);
}

void init(struct chain * chain) {
    chain->blocks = (struct block *) malloc(sizeof(struct block *) * 1024);
    chain->last_block_index = -1;
}