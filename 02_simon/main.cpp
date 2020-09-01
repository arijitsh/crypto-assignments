#include "simon.h"
#include <cstdlib>
/*
 * --encrypt <filename>
 * --decrypt <filename>
 * --show-key
 * --help
 * --key <filename>
 * --seed <number>
 */


int main(int argc, char** argv)
{


    Simon *S;
    int seed = 42;

    if(argc >= 2){ seed = stoi(argv[1]); }
    if(argc >= 3){ verbosity = stoi(argv[2]); }

    srand(seed);
    S = new Simon();
    S->expand_key();
    S->encrypt(message);

}
