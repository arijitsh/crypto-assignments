#include "lfsr.h"
#include "terminal.h"

LFSR::LFSR(int lent, int clk, vector<int> tapped):
    len(lent),
    reg(0),
    tapped_bits(tapped)
{
}

// void LFSR::print_register(){
//     std::cout << reg << '\n';
// }

void LFSR::clock_a_bit(bool ext_bit)
{
    bool xor_out = ext_bit;
    for(auto tap: tapped_bits){
        xor_out ^= reg[tap];
    }
    reg <<= 1;
    xor_out?reg.set(0):reg.reset(0);
}


void LFSR::print_register(){
    terminal = &tout;
    terminal->magenta();
    for(int it = 0; it < len; it++){
        terminal->green(); fprintf( stdout, "%d",int(reg[it]));
//         int item = sign(trail[it])?var(trail[it]):-var(trail[it]);
//         bool is_decision = (trail_lim[decision_level] == it);
//         if(is_decision) decision_level++;
//         if (is_propagated[it] == 1){terminal->green(is_decision); fprintf( stdout, "%d ", item);}
//         if (is_propagated[it] == -1){terminal->red(is_decision); fprintf( stdout, "%d ", item);}
//         if (is_propagated[it] == 0){terminal->yellow(is_decision); fprintf( stdout, "%d ", item);}
//         if (qhead-1 == it) {terminal->magenta(); fputs("| ", stdout);}
//         if (lqhead-1 == it) {terminal->blue(true); fputs("| ", stdout);}
    }
    fputc(' ',stdout);
    terminal->normal();
    fflush(stdout);
}
