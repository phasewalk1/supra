#include "new.hpp"
#include "parser.hpp"
#include <iostream>
#include <string>

int main(int argc, char** argv) {
  Parser parser(argc, argv);
  OPT opt = parser.parse();
  if (opt == NEW) {
    Initializer init = Initializer(std::string("test"));
    init.init_dir();
  }
  return 0;
}