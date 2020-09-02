#include "simon.h"
#include <cstdlib>

Simon::Simon() {}

void Simon::expand_key() {
  bitset<KEYSIZE> roundkey, tmp;
      for(int  i = ROUNDS; i < KEYSIZE; i++){ //TODO : to change
          tmp = key[i-1] >> 3;
          if (ROUNDS = 4) {
              tmp = tmp ^ k[i-3];
          }
          tmp = tmp ^ (tmp >> 1);
//           k[i] ← (!k[i-m]) ^ tmp ^ (z[j][(i-m)) % 62] ^ 3;

        keys.push_back(roundkey);
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
