#include "parser.hpp"
#include "runner.hpp"
#include "init.hpp"

#define NEW_PATH_ARG_IDX 2
#define NEW_FLAG_ARG_IDX 3

Runner::Runner(std::vector<std::string> args) {
  this->argc = args.size();
  this->args = args;
}

/**
 * @brief Set the parser instance to use for this runner
 *
 * @param parser(Parser): The parser instance to use
 */
void Runner::set_parser(Parser parser) {
  this->parser = parser;
}

/**
 * @brief Switch on this->mode and run the program in the specified mode
 * @dev Throws an error if the mode is invalid or if the arguments are invalid
 *
 * TODO: Make this more readable
 */
void Runner::run() {
  // Determine the mode to run the program in
  OPT mode = this->parser.parse();
  // Check if the arguments are valid
  if (!(this->parser.valid_argc())) {
    throw std::runtime_error("Error: Invalid arguments");
  }
  else {
    switch (mode) {
    case OPT::CHECK:
      this->check();
      break;
    case OPT::NEW:
      std::string path = this->args[NEW_PATH_ARG_IDX];
      bool with_benches;
      if (this->argc == 4) {
        if (this->args[NEW_FLAG_ARG_IDX] == "-b" || this->args[NEW_FLAG_ARG_IDX] == "--with-benches") {
          with_benches = true;
        }
        else {
          throw std::runtime_error("Error: Invalid flag");
        }
      }
      else {
        with_benches = false;
      }
      this->instantiate(path, with_benches);
      break;
    }
  }
}

/**
 * @brief Executes the 'new' command
 *
 * @param path(std::string): The path to the directory to create (relative to the current directory
 * @param with_benches(bool): Whether or not to create benchmark directory (default: false)
 */
void Runner::instantiate(std::string path, bool with_benches) {
  Initializer init = Initializer(path);
  init.init_dir(with_benches);
}

/**
 * @brief Checks validity of the saleen.toml manifest file
 *
 */
void Runner::check() {
  try {
    toml::table cfg = this->parser.get_config();
    Manifest manif = this->parser.to_manifest(cfg);
    std::cout << "Manifest checks out!" << "\n";
  }
  catch (std::runtime_error& e) {
    std::cout << e.what() << std::endl;
  }
}