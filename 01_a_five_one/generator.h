#ifndef GENERATOR_H_INCLUDED
#define GENERATOR_H_INCLUDED

#include "lfsr.h"

using namespace std;
int verbosity;


class a51
{
    LFSR *l1, *l2, *l3;
    vector<int> t1, t2, t3;


    bitset<64> session_key;
    bitset<22> frame_counter;
    bitset<228> out_key_stream;

    void set_tap_bits();
    void set_keys_counters();

   public:
    a51();

    bool get_majority_vote();
    void print_registers(int round = 0);

    void clock_session_key();
    void clock_frame_counter();
    void clock_majority_vote();
};

#endif // GENERATOR_H_INCLUDED
