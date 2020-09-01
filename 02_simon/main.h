#include <cstdlib>

bitset<64> set_keys_counters() {
  bitset<64> rnd;
  uint64_t irnd = rand();
  irnd <<= 16;
  irnd += rand();
  irnd <<= 16;
  irnd += rand();
  irnd <<= 16;
  irnd += rand();
  session_key = irnd;
  uint64_t iframe_counter = rand();
  iframe_counter <<= 16;
  iframe_counter += rand();
  frame_counter = iframe_counter;
  // if(verbosity > 0){
  //     cout << "c session key   : " << session_key << endl;
  //     cout << "c frame counter : " << frame_counter << endl;
  // }
  return rnd;
}
