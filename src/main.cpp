#include "new.hpp"
#include "parser.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

#define NEW_MIN_ARGC 3

int main(int argc, char** argv) {
  Parser parser(argc, argv);
  OPT opt = parser.parse();
  if (opt == NEW) {
    if (argc < NEW_MIN_ARGC) {
      throw std::runtime_error("Error: No path given");
    } else {
      Initializer init = Initializer(std::string(argv[2]));
      init.init_dir();
    }
  }
  return 0;
}