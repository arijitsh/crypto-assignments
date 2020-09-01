#include "simon.h"
#include <cstdlib>

Simon::Simon() {}

void Simon::expand_key() {
  int tmp;
  //     for(int  i = m; i < T; i++){
  //         tmp = k[i-1] >> 3;
  //         if (m = 4) {
  //             tmp = tmp ^ k[i-3];
  //         }
  //         tmp = tmp ^ (tmp >> 1);
  //         k[i] ← (!k[i-m]) ^ tmp ^ (z[j][(i-m)) % 62] ^ 3;
  //     }
}

// void Simon::get_next_block(string *message){
//
// }

void Simon::encrypt(string filename, string en_filename) {
      FILE *plaintext_file, *encrypted_file;

    plaintext_file = fopen(filename.c_str(), "rb");
    encrypted_file = fopen(en_filename.c_str(), "w+");
    int c;
    while ((c = std::fgetc(plaintext_file)) != EOF) {
       std::fputc(c, encrypted_file);
    }


  //     while(remaining_message != NULL){
  //         int block = get_next_block();
  //         en_block = encrypt_a_block(block);
  //         write_block(en_block);
  //     }

}

void Simon::encrypt_a_block(int message) {
  bitset<22> tmp;
  for (int i = 0; i < KEYSIZE; i++) {
    tmp = left;
    //         left = right ^ ((left << 1) &  (left << 8)) ^  (left<<2) ^ k[i];
    right = tmp;
  }
}
