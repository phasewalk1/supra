#include "init.hpp"
#include "parser.hpp"
#include <iostream>
#include <stdexcept>
#include <string>

#define NEW_MIN_ARGC 3

int main(int argc, char** argv) {
  Parser parser(argc, argv);
  OPT opt = parser.parse();
  // ********** NEW **********
  if (opt == OPT::NEW) {
    if (argc < NEW_MIN_ARGC) {
      throw std::runtime_error("Error: No path given");
    }
    else {
      Initializer init = Initializer(std::string(argv[2]));
      bool bench_mode;
      if (argc == NEW_MIN_ARGC) {
        bench_mode = false;
      }
      else {
        std::string flag = std::string(argv[3]);
        if (flag == "-b" || flag == "--make-bench") {
          bench_mode = true;
        }
        else {
          throw std::runtime_error("Error: Invalid flag");
        }
      }
      init.init_dir(bench_mode);
    }
  }
  // ********** CHECK **********
  else if (opt == OPT::CHECK) {
    toml::table cfg = parser.get_config();
    Manifest manifest = parser.to_manifest(cfg);

    return 0;
  }
}