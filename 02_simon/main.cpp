#include "simon.h"
#include <boost/program_options.hpp>
#include <boost/program_options/options_description.hpp>
#include <cstdlib>
#include <iostream>
/*
 * --encrypt <filename>
 * --decrypt <filename>
 * --show-key
 * --help
 * --key <filename>
 * --seed <number>
 */
using namespace std;

using std::cerr;
using std::cout;
using std::endl;
using std::exception;
using std::stoi;

namespace po = boost::program_options;

int main(int argc, char **argv) {

  int verbosity;
  Simon *S;
  int seed = 42;
  string filename, en_filename;

  try {

    po::options_description desc("Allowed options");
    desc.add_options()("help", "produce help message")(
        "encrypt", po::value<std::string>(), "file to encrypt")(
        "decrypt", po::value<std::string>(), "file to decrypt");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
      cout << desc << "\n";
      return 0;
    }

    if (vm.count("encrypt")) {
      cout << "Encrypting file : " << vm["encrypt"].as<std::string>() << ".\n";
      if (vm.count("decrypt")) {
        cout << "c encrypt OR decrypt, not both" << endl;
        assert(false);
      }
        filename = vm["encrypt"].as<std::string>();
        en_filename = "en";
        en_filename.append(filename);

    } else if (vm.count("decrypt")) {
      cout << "Encrypting file : " << vm["encrypt"].as<std::string>() << ".\n";
    }
  } catch (exception &e) {
    cerr << "error: " << e.what() << "\n";
    return 1;
  } catch (...) {
    cerr << "Exception of unknown type!\n";
    return 1;
  }

  srand(seed);
  S = new Simon();
  S->expand_key();
  S->encrypt(filename, en_filename);

}
