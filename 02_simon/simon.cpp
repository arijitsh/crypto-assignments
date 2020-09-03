#include "simon.h"
#include <cstdlib>
#include <fstream>
#include <assert.h>

Simon::Simon() {}

void Simon::read_key(string key_filename) {

    std::fstream key_file;
    key_file.open (key_filename,  std::fstream::in );
    for (int i = 0; i < KEYSIZE ; i++ ){
        assert(key_file.good());
        char c = key_file.get();
        bool read_bit = atoi(&c);
        key.set(i,read_bit);
    }
}


void Simon::expand_key() {
    bitset<WORDSIZE> roundkey, tmp, three = 3;

    int key_posision = 0;
    for (int i = 0; i < NUMKEYWORDS ; i++ ){
        for(int j = 0; j < WORDSIZE; j++){
            roundkey.set(j, key[key_posision++]);
        }
        keys.push_back(roundkey);
        if (verb > 0)
            cout << "c key for round " << i+1 << " : " << roundkey << endl;
    }

    for(int  i = NUMKEYWORDS; i < ROUNDS; i++){
        tmp = keys[i-1] >> 3;
        if (NUMKEYWORDS == 4) { tmp  ^= keys[i-3]; }
        tmp = tmp ^ (tmp >> 1);
        roundkey = (keys[i-NUMKEYWORDS]) ^ tmp ^ three ; //^ z[(i-M) % 62] // TODO : this is wrong
        if (verb > 0)
            cout << "c key for round " << i+1 << " : " << roundkey << endl;
        keys.push_back(roundkey);
    }
}

void Simon::encrypt(string filename, string en_filename) {


    std::fstream plaintext_file, encrypted_file;

    plaintext_file.open (filename,  std::fstream::in );
    encrypted_file.open (en_filename,  std::fstream::out );

    char c = plaintext_file.get();
    int chars_added = 0;

    bitset<BLOCK> block, en_block;
    bitset<BLOCK> one_char;
    bitset<8> a_char;

    while (plaintext_file.good()) {
        one_char = c;
        block <<= 8;
        block |= one_char;
        chars_added++;

        if(chars_added == BLOCK/8){
            chars_added = 0;
            en_block = encrypt_a_block(block);
            if (verb > 1)
                cout << "c plaintext block : " << block
                     << " ciphertext block : " << en_block << endl;
            for (int i = 0; i < BLOCK/8; i++){
                for (int j = 0; j < 8; j++){
                    a_char.set(j,en_block[i*8+j]);
                }
                unsigned long k = a_char.to_ulong();
                char c = static_cast<unsigned char>( k );
                encrypted_file << c;
            }
        }
        c = plaintext_file.get();
    }

    plaintext_file.close();
    encrypted_file.close();
}

bitset<BLOCK> Simon::encrypt_a_block(bitset<BLOCK> block) {
    for(int j = 0; j < BLOCK/2; j++){
        left.set(j, block[j]);
        right.set(j, block[j+BLOCK/2]);
    }

    for (int i = 0; i < ROUNDS; i++) {
        tmp = left;
        left = right ^ ((left << 1) &  (left << 8)) ^  (left<<2) ^ keys[i];
        right = tmp;
    }

    for(int j = 0; j < BLOCK/2; j++){
        en_block.set(j, left[j]);
        en_block.set(j+BLOCK/2, right[j]);
    }

    return en_block;
}

void Simon::decrypt(string filename, string dec_filename) {


    std::fstream plaintext_file, decrypted_file;

    plaintext_file.open (filename,  std::fstream::in );
    decrypted_file.open (dec_filename,  std::fstream::out);

    char c = plaintext_file.get();
    int chars_added = 0;

    bitset<BLOCK> block;
    bitset<BLOCK> one_char;
    bitset<8> a_char;

    while (plaintext_file.good()) {
        one_char = c;
        for (int i = 8; i < BLOCK; i++){
            one_char.set(i,0);
        }
        one_char <<= 24;
        bitset<8>  y = c;
        block >>= 8;
        if (verb > 1)
            cout << " c " << block << " " << one_char<< " " << y <<  endl;
        block |= one_char;
        chars_added++;

        if(chars_added == BLOCK/8){
            chars_added = 0;
            en_block = decrypt_a_block(block);
            if (verb > 1)
                cout << "c plaintext block : " << block
                     << " ciphertext block : " << en_block << endl;
            std::string word("");
            for (int i = 0; i < BLOCK/8; i++){
                for (int j = 0; j < 8; j++){
                    a_char.set(j,en_block[i*8+j]);
                }
                unsigned long k = a_char.to_ulong();
                char c = static_cast<unsigned char>( k );
                word += c;
            }
            decrypted_file << string(word.rbegin(),word.rend());
        }
        c = plaintext_file.get();
    }

    plaintext_file.close();
    decrypted_file.close();
}

bitset<BLOCK> Simon::decrypt_a_block(bitset<BLOCK> block) {

    for(int j = 0; j < BLOCK/2; j++){
        left.set(j, block[j]);
        right.set(j, block[j+BLOCK/2]);
    }

    for (int i = 0; i < ROUNDS; i++) {
        tmp = right;
        right = left ^ ((right << 1) &  (right << 8)) ^  (right<<2) ^ keys[ROUNDS - i -1];
        left = tmp;
    }

    for(int j = 0; j < BLOCK/2; j++){
        en_block.set(j, left[j]);
        en_block.set(j+BLOCK/2, right[j]);
    }

    return en_block;
}
