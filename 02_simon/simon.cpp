#include "simon.h"
#include <cstdlib>

Simon::Simon() {}

void Simon::expand_key() {
    bitset<WORDSIZE> roundkey, tmp;

    int key_posision = 0;
    for (int i = 0; i < NUMKEYWORDS ; i++ ){
        for(int j = 0; j < WORDSIZE; j++){
            roundkey.set(j, key[key_posision++]);
        }
        keys.push_back(roundkey);
        cout << "key for round " << i << " : " << roundkey << endl;
    }

    for(int  i = NUMKEYWORDS; i < ROUNDS; i++){
        tmp = keys[i-1] >> 3;
        cout << tmp << endl << keys[i-3] << endl;
        if (NUMKEYWORDS == 4) { tmp  ^= keys[i-3]; }
        tmp = tmp ^ (tmp >> 1);
        keys[i] = (keys[i-NUMKEYWORDS]) ^ tmp ; //^ z[(i-M) % 62] ^ 3; // TODO : this is wrong
        cout << "key for round " << i << " : " << roundkey << endl;
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
            en_block = encrypt_a_block(block);
            c = en_block.to_string().c_str()[1]; // Needs to be corrected
            cout << "plaintext block : " << block << " ciphertext block : " << en_block << endl;
            std::fputc(c, encrypted_file);
        }
    }

    fclose(plaintext_file);
    fclose(encrypted_file);
}

bitset<BLOCK> Simon::encrypt_a_block(bitset<BLOCK> block) {
    bitset<BLOCK> en_block;
    for(int j = 0; j < BLOCK/2; j++){
        left.set(j, block[j]);
        right.set(j, block[j+BLOCK/2]);
    }
    for (int i = 0; i < ROUNDS; i++) {
        tmp = left;
        left = right ^ ((left << 1) &  (left << 8)) ^  (left<<2) ^ keys[i];
        right = tmp;
        cout << "round" << i <<  " converted " << block << " to " << left << right << endl;
    }

    for(int j = 0; j < BLOCK/2; j++){
        en_block.set(j, left[j]);
        en_block.set(j+BLOCK/2, right[j]);
    }



    return en_block;
}
