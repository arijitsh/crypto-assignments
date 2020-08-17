#include "lfsr.h"

LFSR::LFSR(int lent, int clk, vector<int> tapped):
    len(lent),
    reg(0)
{
    tapped_bits = &tapped;
}

void LFSR::print_register(){
    std::cout << reg << '\n';
}

void LFSR::clock_a_bit(bool ext_bit)
{
    bool xor_out = ext_bit;
    for(auto tap: *tapped_bits){
        xor_out ^= reg[tap];
    }
    reg <<= 1;
    xor_out?reg.set(0):reg.reset(0);
}


