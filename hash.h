#include <openssl/md5.h>
#include <string.h>

void generate_block_md5(const struct block * block, char * hash) {
    char * string = (char *) malloc(sizeof(block));
    memcpy(string, &block, sizeof(block));

    generate_string_md5(string, hash);

    free(string);
}

void generate_string_md5(const char * string, char * hash) {
    unsigned char digest[16];

    MD5_CTX ctx;
    MD5_Init(&ctx);
    MD5_Update(&ctx, string, strlen(string));
    MD5_Final(digest, &ctx);

    char mdString[33];
    for (int i = 0; i < 16; i++) {
        sprintf(&mdString[i*2], "%02x", (unsigned int) digest[i]);
    }

    memcpy(hash, &mdString, sizeof(char) * 33);
}