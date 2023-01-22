#include "runner.hpp"
#include "init.hpp"
#include "parser.hpp"

#define NEW_MIN_ARGC 3

/**
 * @brief Construct a new Runner:: Runner object
 *
 * @param argc(int): The number of arguments passed to the program
 * @param argv(char**): The arguments passed to the program
 * @param mode(OPT): The mode to run the program in
 */
Runner::Runner(int argc, char** argv, OPT mode) {
  this->argc = argc;
  this->argv = argv;
  this->mode = mode;
}

/**
 * @brief Switch on this->mode and run the program in the specified mode
 * @dev Throws an error if the mode is invalid or if the arguments are invalid
 *
 * TODO: Make this more readable
 */
void Runner::run() {
  switch (this->mode) {
  case OPT::NEW:
    if (this->argc < NEW_MIN_ARGC) {
      throw std::runtime_error("Error: No path given");
    }
    else {
      Initializer init = Initializer(std::string(this->argv[2]));
      bool bench_mode;
      if (this->argc == NEW_MIN_ARGC) {
        bench_mode = false;
      }
      else {
        std::string flag = std::string(this->argv[3]);
        if (flag == "-b" || flag == "--make-bench") {
          bench_mode = true;
        }
        else {
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