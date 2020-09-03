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

  bitset<KEYSIZE> key;
  bitset<BLOCK/2> left, right, tmp;
  bitset<BLOCK> en_block, dec_block;
  vector<bitset<WORDSIZE>> keys ;
  bitset<64> z =
      0b11111010001001010110000111001101111101000100101011000011100110;

public:
  Simon();

  int verb = 0;

  bitset<BLOCK> encrypt_a_block(bitset<BLOCK> block);
  void encrypt(string, string);

  bitset<BLOCK> decrypt_a_block(bitset<BLOCK> block);
  void decrypt(string, string);

  void read_key(string);
  void expand_key();
};

#endif // SIMON_H_INCLUDED
