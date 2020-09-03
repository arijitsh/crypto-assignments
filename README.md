[![License: GPL](https://img.shields.io/badge/License-GPL-yellow.svg)](https://opensource.org/licenses/GPL-2.0)
# Cryptology - 1 Assignments

Author : Arijit Shaw.

Instructor : Arpita Maitra

Download and go to the repository :
```
git clone https://github.com/arijitsh/crypto-assignments.git
cd crypto-assignments
```

## Assignment - 2 : Simon cipher

Build and execute:
```
cd 02_simon
cmake .
make
./simon --encrypt <plaintext file> --key <keyfile>
./simon --decrypt <ciphertext file> --key <keyfile>
```
A sample plaintext file `sample.txt` and a keyfile `key.txt` is included. Issue `./simon --help` for more options. Use `--verb 1` or `--verb 2` to see the key expansion and encryption process.

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
