#include "init.hpp"
#include "parser.hpp"
#include "runner.hpp"
#include "logger.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

#define NEW_MIN_ARGC 3

int main(int argc, char** argv) {
  // parse command line arguments
  Parser parser(argc, argv);
  std::vector<std::string> args = parser.get_argv();
  // initialize the runner
  Runner runner(args);
  runner.set_parser(parser);
  // run the program
  try {
    runner.run();
  }
  catch (std::runtime_error& e) {
    std::cout << e.what() << std::endl;
  }
}