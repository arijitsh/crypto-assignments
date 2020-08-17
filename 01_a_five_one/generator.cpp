#include "generator.h"
#include "lfsr.h"

#include <cstdlib>

using namespace std;

a51::a51()
{
    set_tap_bits();
    l1 = new LFSR(19, 8, t1);
    l2 = new LFSR(22, 10, t2);
    l3 = new LFSR(23, 10, t3);
    set_keys_counters();
    if(verbosity > 0)print_registers();
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
    frame_counter = iframe_counter;
    if(verbosity > 0){
        cout << "c session key   : " << session_key << endl;
        cout << "c frame counter : " << frame_counter << endl;
    }
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
    if(verbosity > 0)
        cout << "c clocking with session key" << endl;
    for (int i = 0; i < 64; i++) {
        l1->clock_a_bit(session_key[i]);
        l2->clock_a_bit(session_key[i]);
        l3->clock_a_bit(session_key[i]);
        if(verbosity > 0) print_registers(i + 1);
    }
}

void a51::clock_frame_counter()
{
    if(verbosity > 0)
        cout << "c clocking with frame counter" << endl;
    for (int i = 0; i < 22; i++) {
        l1->clock_a_bit(frame_counter[i]);
        l2->clock_a_bit(frame_counter[i]);
        l3->clock_a_bit(frame_counter[i]);
        if(verbosity > 0) print_registers(i + 1);
    }
}

bool a51::get_majority_vote()
{
    int more_ones = 0;
    (l1->get_clocking_bit()) ? more_ones++ : more_ones--;
    (l2->get_clocking_bit()) ? more_ones++ : more_ones--;
    (l3->get_clocking_bit()) ? more_ones++ : more_ones--;

    return (more_ones > 0);
}

void a51::clock_majority_vote()
{
    bool outbit, majority;
    if(verbosity > 0)
        cout << "c clocking with majority votes" << endl;
    for (int i = 0; i < 228; i++) {
        majority = get_majority_vote();
        if (majority == l1->get_clocking_bit())
            l1->clock_a_bit(frame_counter[i]);
        if (majority == l2->get_clocking_bit())
            l2->clock_a_bit(frame_counter[i]);
        if (majority == l3->get_clocking_bit())
            l3->clock_a_bit(frame_counter[i]);
        if(verbosity > 0) print_registers(i + 1);
        outbit = l1->get_msb() ^ l2->get_msb() ^ l3->get_msb();
        out_key_stream <<= 1;
        outbit ? out_key_stream.set(0) : out_key_stream.reset(0);
    }
    cout << out_key_stream << endl;
}

void a51::print_registers(int round)
{
    cout << round << " ";
    l1->print_register();
    l2->print_register();
    l3->print_register();
    printf("\n");
}

int main(int argc, char** argv)
{

    a51 *G;
    int seed = 42;

    if(argc >= 2){ seed = stoi(argv[1]); }
    if(argc >= 3){ verbosity = stoi(argv[2]); }

    srand(seed);
    G = new a51();

    G->clock_session_key();
    G->clock_frame_counter();
    G->clock_majority_vote();
}
