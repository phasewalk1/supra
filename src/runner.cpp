#include "runner.hpp"
#include "init.hpp"
#include "parser.hpp"

#define NEW_MIN_ARGC 3

Runner::Runner(int argc, char** argv, OPT mode) {
  this->argc = argc;
  this->argv = argv;
  this->mode = mode;
}

void Runner::run() {
  switch (this->mode) {
  case OPT::NEW:
    if (this->argc < NEW_MIN_ARGC) {
      throw std::runtime_error("Error: No path given");
    } else {
      Initializer init = Initializer(std::string(this->argv[2]));
      bool bench_mode;
      if (this->argc == NEW_MIN_ARGC) {
        bench_mode = false;
      } else {
        std::string flag = std::string(this->argv[3]);
        if (flag == "-b" || flag == "--make-bench") {
          bench_mode = true;
        } else {
          throw std::runtime_error("Error: Invalid flag");
        }
      }
      init.init_dir(bench_mode);
    }
  case OPT::CHECK:
    Parser parser = Parser(this->argc, this->argv);
    toml::table cfg = parser.get_config();
    Manifest manifest = parser.to_manifest(cfg);

    return;
  }
}