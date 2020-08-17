#include "lfsr.h"
#include "terminal.h"

LFSR::LFSR(int lent, int clk, vector<int> tapped)
    : len(lent), reg(0), tapped_bits(tapped), clocking_bit(clk)
{
}

void LFSR::clock_a_bit(bool ext_bit)
{
    bool xor_out = ext_bit;
    for (auto tap: tapped_bits) {
        xor_out ^= reg[tap];
    }
    reg <<= 1;
    xor_out ? reg.set(0) : reg.reset(0);
}

void LFSR::print_register()
{
    terminal = &tout;
    terminal->magenta();
    int t = tapped_bits.size() - 1;
    for (int it = len - 1; it >= 0; it--) {
        if (it == tapped_bits[t] && it > 0) {
            terminal->blue(true);
            fprintf(stdout, "%d", int(reg[it]));
            t--;
        } else if (it == clocking_bit) {
            terminal->red();
            fprintf(stdout, "%d", int(reg[it]));
        } else {
            terminal->green();
            fprintf(stdout, "%d", int(reg[it]));
        }
    }
    fputc(' ', stdout);
    terminal->normal();
    fflush(stdout);
}
