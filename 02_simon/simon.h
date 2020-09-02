#ifndef SIMON_H_INCLUDED
#define SIMON_H_INCLUDED

#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

// setting up simon 32/64

#define WORDSIZE 16 // word size
#define NUMKEYWORDS 4  // num keywords
#define ROUNDS 32  // 2*N
#define KEYSIZE 64 // N*M
#define BLOCK 32    // block size

using namespace std;

class Simon {

  bitset<KEYSIZE> key = 0b10001110111110010011000010110101000111011111001001100001011010; // TODO : read key from file
  bitset<BLOCK/2> left, right, tmp;
  vector<bitset<WORDSIZE>> keys ;
  bitset<64> z =
      0b11111010001001010110000111001101111101000100101011000011100110;
  // z[1] = 10001110111110010011000010110101000111011111001001100001011010;
  // z[2] = 10101111011100000011010010011000101000010001111110010110110011;
  // z[3] = 11011011101011000110010111100000010010001010011100110100001111;
  // z[4] = 11010001111001101011011000100000010111000011001010010011101111;

public:
  Simon();

  void write_block();
  int get_next_block();

  void one_round_encryption();
  bitset<BLOCK> encrypt_a_block(bitset<BLOCK> block);
  void encrypt(string, string);

  void one_round_decryption();
  void decrypt_a_block(int msg_block);
  void decrypt(FILE *ciphertext);

  void expand_key();
};

#endif // SIMON_H_INCLUDED
