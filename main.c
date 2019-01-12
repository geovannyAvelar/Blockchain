#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "blockchain.h"

void main() {
    struct chain chain;
    struct chain * chain_p = &chain;
    init(chain_p);

    // Create 'genesis' block
    new_block(chain_p, 1);

    mine(chain_p);
}