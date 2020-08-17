#include "lfsr.h"

LFSR::LFSR():
    reg(42)
{
}

void LFSR::print_register(){
    printf("%d\n",reg);
}
