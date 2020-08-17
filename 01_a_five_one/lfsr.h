#ifndef LFSR_H_INCLUDED
#define LFSR_H_INCLUDED

#include <assert.h>
#include <bitset>
#include <cstdio>
#include <iostream>
#include <vector>

#include "terminal.h"

using namespace std;

class LFSR
{
    const int len;
    bitset<23> reg;
    vector<int> tapped_bits;
    int clocking_bit;
    Terminal* terminal;

   public:
    LFSR(int lent, int clk, vector<int> tapped);
    void clock_a_bit(bool ext_bit);
    void print_register();

    int get_clocking_bit()
    {
        return (reg[clocking_bit]);
    }

    int get_msb()
    {
        return (reg[len - 1]);
    }
};
#endif // LFSR_H_INCLUDED
