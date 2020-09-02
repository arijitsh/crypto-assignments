#include "simon.h"
#include <cstdlib>

Simon::Simon() {}

void Simon::expand_key() {
    bitset<N> roundkey, tmp;

    int key_posision = 0;
    for (int i = 0; i < M ; i++ ){
        for(int j = 0; j < N; j++){
            roundkey.set(j, key[key_posision++]);
        }
        keys.push_back(roundkey);
    }

    for(int  i = M; i < ROUNDS; i++){
        tmp = key[i-1] >> 3;
        if (M == 4) { tmp = tmp ^ keys[i-3]; }
        tmp = tmp ^ (tmp >> 1);
        keys[i] = (keys[i-M]) ^ tmp ^ z[(i-M) % 62] ^ 3;

    }
}

void Simon::encrypt(string filename, string en_filename) {
    FILE *plaintext_file, *encrypted_file;

    plaintext_file = fopen(filename.c_str(), "rb");
    encrypted_file = fopen(en_filename.c_str(), "w+");

    char c;
    int chars_added = 0;

    bitset<BLOCK> block, en_block;
    bitset<BLOCK> one_char;

    while ((c = std::fgetc(plaintext_file)) != EOF) {
        one_char = c;
        block <<= 8;
        block |= one_char;
        chars_added++;

        if(chars_added == BLOCK/8){
            chars_added = 0;
            cout << "encrypting : " << block << endl;
            en_block = encrypt_a_block(block);
            c = en_block.to_string().c_str()[1]; // Needs to be corrected
            std::fputc(c, encrypted_file);
        }
    }

    fclose(plaintext_file);
    fclose(encrypted_file);
}

bitset<BLOCK> Simon::encrypt_a_block(bitset<BLOCK> block) {
  bitset<22> tmp;
  for (int i = 0; i < KEYSIZE; i++) {
    tmp = left;
    left = right ^ ((left << 1) &  (left << 8)) ^  (left<<2) ^ k[i];
    right = tmp;
  }
}
