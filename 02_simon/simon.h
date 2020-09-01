#ifndef SIMON_H_INCLUDED
#define SIMON_H_INCLUDED

#define N 16 // word size
#define N 16 // num keywords

z = [11111010001001010110000111001101111101000100101011000011100110,
10001110111110010011000010110101000111011111001001100001011010,
10101111011100000011010010011000101000010001111110010110110011,
11011011101011000110010111100000010010001010011100110100001111,
11010001111001101011011000100000010111000011001010010011101111]

#include <cstdio>
#include <cstdlib>


using std::endl;
using std::cout;

class Simon
{
    bitset<22> left, right;

   public:
    Simon();

    void write_block();

    void one_round_encryption();
    void encrypt_a_block(int msg_block);
    void encrypt(int message);

    void one_round_decryption();
    void decrypt_a_block(int msg_block);
    void decrypt(int message);

    void expand_key();
};


#endif // SIMON_H_INCLUDED
