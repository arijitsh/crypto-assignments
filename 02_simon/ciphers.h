#ifndef SIMON_H_INCLUDED
#define SIMON_H_INCLUDED

#include <bitset>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <bit>
#include <assert.h>
#include <fstream>
// setting up simon 32/64

#define WORDSIZE 16   // word size
#define NUMKEYWORDS 4 // num keywords
#define ROUNDS 32     // 2*N
#define KEYSIZE 64    // N*M
#define BLOCK 32      // block size

// also speck 32/64

#define ALPHA 7
#define BETA 2

using namespace std;

inline bitset<WORDSIZE> binAdd(bitset<WORDSIZE> a, bitset<WORDSIZE> b)
{
    unsigned long sum = ( a.to_ulong() + b.to_ulong()) % 0x10000;
    std::bitset<WORDSIZE> result(sum);
    return result;
}

inline bitset<WORDSIZE> substarct(bitset<WORDSIZE> a, bitset<WORDSIZE> b)
{
    unsigned long long diff = ( a.to_ulong() - b.to_ulong()) % 0x10000;
    std::bitset<WORDSIZE> result(diff);
    return result;
}

inline bitset<WORDSIZE> rotl (bitset<WORDSIZE> x, int n)
{
  assert (n<WORDSIZE);
  return (x<<n) | (x>>(WORDSIZE-n));
}

inline bitset<WORDSIZE> rotr (bitset<WORDSIZE> x, int n)
{
  assert (n<WORDSIZE);
  return (x>>n) | (x<<(WORDSIZE-n));
}

class Cipher
{
    bitset<KEYSIZE> key;
    bitset<BLOCK / 2> left, right, tmp;
    bitset<BLOCK> en_block, dec_block;
    vector<bitset<WORDSIZE>> keys, ls;
    bitset<64> z = 0b11111010001001010110000111001101111101000100101011000011100110;

   public:
    Cipher();

    int verb = 0, show_key = false;

    bitset<BLOCK> encrypt_a_block(bitset<BLOCK> block);
    void encrypt(string, string);

    bitset<BLOCK> decrypt_a_block(bitset<BLOCK> block);
    void decrypt(string, string);

    void read_key(string);
    void expand_key();
};

#endif // SIMON_H_INCLUDED
