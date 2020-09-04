[![License: GPL](https://img.shields.io/badge/License-GPL-yellow.svg)](https://opensource.org/licenses/GPL-2.0)
# Cryptology - 1 Assignments

Author : Arijit Shaw.

Instructor : Arpita Maitra

Download and go to the repository :
```
git clone https://github.com/arijitsh/crypto-assignments.git
cd crypto-assignments
```

## Assignment - 2 : Simon and Speck ciphers

### Simon Cipher

Build and execute :
```
cd 02_block_ciphers
cmake -DSPECK=OFF -DSIMON=ON .
make
./simon --encrypt <plaintext file> --key <keyfile>
./simon --decrypt <ciphertext file> --key <keyfile>
```
A sample plaintext file `sample.txt` and a keyfile `key.txt` are included. During encryption and decryption, new files are generated with prefixes `en_` and `dec_` to existing filename. For example, when a file named `sample.txt` is encrypted, a file called `en_sample.txt` is generated, when a file named `en_sample.txt` is decrypted, a file called `dec_en_sample.txt` is generated.

Issue `--help` for more options. Use `--verb 1` or `--verb 2` to see encryption process. Use `--show-key` to see the key expansion.

### Speck Cipher

Build and execute :
```
cd 02_block_ciphers
cmake -DSPECK=ON -DSIMON=OFF .
make
./speck --encrypt <plaintext file> --key <keyfile>
./speck --decrypt <ciphertext file> --key <keyfile>
```

Instructions are same as Simon.

Simon 32/64 and Speck 32/64 is built in this process. Change parameters in `#defines` in `cipher.h` to build other versions.

## Assignment - 1 : Frequency Analysis
Source Code : `01_freqency_analysis.py`

Plot : `01_freqency_analysis.ipynb`

To run the code, execute :
```
python3 01_freqency_analysis.py
```

## Assignment - 1 : Permutations

Source Code : `01_permutaions.py`

To run the code, execute :
```
python3 01_permutaions.py
```

## Assignment - 1 : A5/1 keystream generator

Build and execute:
```
cd 01_a_five_one
cmake .
make
./afiveone 42 1
```

The command to execute is `./afiveone <seed> <verbosity>`. Seed is used to randomly generate the session key and frame counter. Verbosity = 0 shows only the keystream generated.
