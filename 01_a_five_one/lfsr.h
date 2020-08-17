#ifndef LFSR_H_INCLUDED
#define LFSR_H_INCLUDED

#include <cstdio>
#include <bitset>
#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

class LFSR
{
    const int len;
    bitset<22> reg;
    vector<int> tapped_bits;


public:
    LFSR(int lent, int clk, vector<int> tapped);
    void clock_a_bit(bool ext_bit);
    void print_register();

    int  getbit(int k){
        assert(k < len);
        return(reg[k]) ;
    }


};
#endif // LFSR_H_INCLUDED
