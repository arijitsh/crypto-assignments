#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include "ciphers.h"

using namespace std;

namespace po = boost::program_options;

int main(int argc, char **argv)
{
    Cipher *S = new Cipher();
    int seed = 42;
    string filename, en_filename, dec_filename, key_file;
    bool encrypt_mode = true;

#ifdef SIMON
    cout << "c This is Simon " << ROUNDS << "/" << KEYSIZE << endl;
#else
    cout << "c This is Speck " << ROUNDS << "/" << KEYSIZE << endl;
#endif

    try {
        po::options_description desc("Allowed options");
        desc.add_options()("help", "produce help message")("show-key", "show round keys")(
            "verb", po::value<int>(), "verbosity 1 or 2 : more details of encryption")(
            "key", po::value<std::string>(), "key file")("encrypt", po::value<std::string>(),
                                                         "file to encrypt")(
            "decrypt", po::value<std::string>(), "file to decrypt");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if (vm.count("help")) {
            cout << desc << "\n";
            return 0;
        }
        if (vm.count("verb")) {
            S->verb = vm["verb"].as<int>();
        }
        if (vm.count("show-key")) {
            S->show_key = true;
        }
        if (vm.count("encrypt")) {
            if (vm.count("decrypt")) {
                cout << "c encrypt OR decrypt, not both" << endl;
                return 0;
            }
            filename = vm["encrypt"].as<std::string>();
            en_filename = "en_";
            en_filename.append(filename);
            cout << "c encrypting file " << filename << " to " << en_filename << endl;
        } else if (vm.count("decrypt")) {
            filename = vm["decrypt"].as<std::string>();
            dec_filename = "dec_";
            dec_filename.append(filename);
            cout << "c decrypting file " << filename << " to " << dec_filename << endl;
            encrypt_mode = false;
        } else {
            cout << "c please mention a file to encrypt or decrypt." << endl;
            return 0;
        }

        if (vm.count("key")) {
            key_file = vm["key"].as<std::string>();
            cout << "c using key from file " << key_file << endl;
        } else {
            cout << "c please provide a key for encryption." << endl;
            return 0;
        }

    } catch (exception &e) {
        cerr << "c error: " << e.what() << "\n";
        return 1;
    } catch (...) {
        cerr << "c Exception of unknown type!\n";
        return 1;
    }

    srand(seed);
    S->read_key(key_file);
    S->expand_key();
    if (encrypt_mode)
        S->encrypt(filename, en_filename);
    else
        S->decrypt(filename, dec_filename);
}
