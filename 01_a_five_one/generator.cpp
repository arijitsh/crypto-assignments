#include "lfsr.h"
#include "generator.h"

#include <cstdlib>

using namespace std;

a51::a51()
{
    set_tap_bits();
    l1 = new LFSR(19,8,t1);
    l2 = new LFSR(22,10,t2);
    l3 = new LFSR(23,10,t3);
    set_keys_counters();
}

void a51::set_keys_counters()
{
    uint64_t isession_key = rand();
    isession_key <<= 16;
    isession_key += rand();
    isession_key <<= 16;
    isession_key += rand();
    isession_key <<= 16;
    isession_key += rand();
    session_key = isession_key;
    uint64_t iframe_counter = rand();
    iframe_counter <<= 16;
    iframe_counter += rand();
    frame_counter =  iframe_counter;
}

void a51::set_tap_bits()
{
    t1.push_back(13);
    t1.push_back(16);
    t1.push_back(17);
    t1.push_back(18);
    t2.push_back(20);
    t2.push_back(21);
    t3.push_back(7);
    t3.push_back(20);
    t3.push_back(21);
    t3.push_back(22);
}

void a51::clock_session_key()
{
    for(int i=0; i < 64;i++){
        l1->clock_a_bit(session_key[i]);
        l2->clock_a_bit(session_key[i]);
        l3->clock_a_bit(session_key[i]);
    }
}



void a51::print_registers()
{
    l1->print_register();
    l2->print_register();
    l3->print_register();
}


int main(){
    a51 *G;
    srand(42);
    G = new a51();
    G->print_registers();
    G->clock_session_key();
}


