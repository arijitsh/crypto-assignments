#include "ciphers.h"

Cipher::Cipher()
{
#ifndef SIMON
#ifndef SPECK
    cout << "None of SPECK or SIMON selected, this is unlikely." << endl;
    assert(false);
#endif
#endif
}

void Cipher::read_key(string key_filename)
{
    std::fstream key_file;
    key_file.open(key_filename, std::fstream::in);
    for (int i = 0; i < KEYSIZE; i++) {
        assert(key_file.good());
        char c = key_file.get();
        bool read_bit = atoi(&c);
        key.set(i, read_bit);
    }
    key_file.close();
}

void Cipher::expand_key()
{
    bitset<WORDSIZE> roundkey, tmp, three = 3;

    int key_posision = 0;
    for (int i = 0; i < NUMKEYWORDS; i++) {
        for (int j = 0; j < WORDSIZE; j++) {
            roundkey.set(j, key[key_posision++]);
        }
#ifdef SIMON
        keys.push_back(roundkey);
#else
        if (i > 0)
            ls.push_back(roundkey);
        else
            keys.push_back(roundkey);
#endif
        if (show_key)
            cout << "c key for round " << i + 1 << " : " << roundkey << endl;
    }
#ifdef SIMON
    for (int i = NUMKEYWORDS; i < ROUNDS; i++) {
        tmp = keys[i - 1] >> 3;
        if (NUMKEYWORDS == 4) {
            tmp ^= keys[i - 3];
        }
        tmp = tmp ^ (tmp >> 1);
        roundkey = (keys[i - NUMKEYWORDS]) ^ tmp ^ three; //^ z[(i-M) % 62] // TODO : this is wrong
        if (verb > 0)
            cout << "c key for round " << i + 1 << " : " << roundkey << endl;
        keys.push_back(roundkey);
    }
#else
    bitset<WORDSIZE> k, l, bit_i;
    for (int i = 0; i < ROUNDS - 1; i++) {
        bit_i = i;
        l = binAdd(keys[i], rotl(ls[i], -ALPHA)) ^ bit_i;
        ls.push_back(l);
        k = rotl(keys[i], ALPHA) ^ ls[i + NUMKEYWORDS - 1];
        keys.push_back(k);
        if (show_key)
            cout << "c key for round " << i + 1 << " : " << roundkey << endl;
    }
#endif
}

void Cipher::encrypt(string filename, string en_filename)
{
    std::fstream plaintext_file, encrypted_file;

    plaintext_file.open(filename, std::fstream::in);
    encrypted_file.open(en_filename, std::fstream::out);

    char c = plaintext_file.get();
    int chars_added = 0;

    bitset<BLOCK> block, en_block;
    bitset<BLOCK> one_char;
    bitset<8> a_char;

    while (plaintext_file.good()) {
        one_char = c;
        block <<= 8;
        block |= one_char;
        chars_added++;

        if (chars_added == BLOCK / 8) {
            chars_added = 0;
            en_block = encrypt_a_block(block);
            if (verb > 0)
                cout << "c plaintext block : " << block << " ciphertext block : " << en_block
                     << endl;
            for (int i = 0; i < BLOCK / 8; i++) {
                for (int j = 0; j < 8; j++) {
                    a_char.set(j, en_block[i * 8 + j]);
                }
                unsigned long k = a_char.to_ulong();
                char c = static_cast<unsigned char>(k);
                encrypted_file << c;
            }
        }
        c = plaintext_file.get();
    }

    plaintext_file.close();
    encrypted_file.close();
}

bitset<BLOCK> Cipher::encrypt_a_block(bitset<BLOCK> block)
{
    for (int j = 0; j < BLOCK / 2; j++) {
        left.set(j, block[j]);
        right.set(j, block[j + BLOCK / 2]);
    }

    for (int i = 0; i < ROUNDS; i++) {
#ifdef SIMON
        tmp = left;
        left = right ^ (rotl(left, 1) & rotl(left, 8)) ^ rotl(left, 2) ^ keys[i];
        right = tmp;
#else
        left = binAdd(rotr(left, ALPHA), right) ^ keys[i];
        right = rotl(right, BETA) ^ left;
#endif
        if (verb > 1)
            cout << "c round " << i << " encrypts to " << right << " " << left << endl;
    }

    for (int j = 0; j < BLOCK / 2; j++) {
        en_block.set(j, left[j]);
        en_block.set(j + BLOCK / 2, right[j]);
    }

    return en_block;
}

void Cipher::decrypt(string filename, string dec_filename)
{
    std::fstream plaintext_file, decrypted_file;

    plaintext_file.open(filename, std::fstream::in);
    decrypted_file.open(dec_filename, std::fstream::out);

    char c = plaintext_file.get();
    int chars_added = 0;

    bitset<BLOCK> block;
    bitset<BLOCK> one_char;
    bitset<8> a_char;

    while (plaintext_file.good()) {
        one_char = c;
        for (int i = 8; i < BLOCK; i++) {
            one_char.set(i, 0);
        }
        one_char <<= 24;
        bitset<8> y = c;
        block >>= 8;
        block |= one_char;
        chars_added++;

        if (chars_added == BLOCK / 8) {
            chars_added = 0;
            en_block = decrypt_a_block(block);
            if (verb > 0)
                cout << "c plaintext block : " << block << " ciphertext block : " << en_block
                     << endl;
            std::string word("");
            for (int i = 0; i < BLOCK / 8; i++) {
                for (int j = 0; j < 8; j++) {
                    a_char.set(j, en_block[i * 8 + j]);
                }
                unsigned long k = a_char.to_ulong();
                char c = static_cast<unsigned char>(k);
                word += c;
            }
            decrypted_file << string(word.rbegin(), word.rend());
        }
        c = plaintext_file.get();
    }

    plaintext_file.close();
    decrypted_file.close();
}

bitset<BLOCK> Cipher::decrypt_a_block(bitset<BLOCK> block)
{
    for (int j = 0; j < BLOCK / 2; j++) {
        left.set(j, block[j]);
        right.set(j, block[j + BLOCK / 2]);
    }

    for (int i = 0; i < ROUNDS; i++) {
#ifdef SIMON
        tmp = right;
        right = left ^ (rotl(right, 1) & rotl(right, 8)) ^ rotl(right, 2) ^ keys[ROUNDS - i - 1];
        left = tmp;
#else
        right = rotr((left ^ right), BETA);
        left = rotl(substarct((left ^ keys[ROUNDS - i - 1]), right), ALPHA);
#endif
        if (verb > 1)
            cout << "c round " << i << " decrypts to " << right << " " << left << endl;
    }

    for (int j = 0; j < BLOCK / 2; j++) {
        en_block.set(j, left[j]);
        en_block.set(j + BLOCK / 2, right[j]);
    }

    return en_block;
}
