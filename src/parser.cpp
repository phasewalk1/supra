#include "parser.hpp"

Parser::Parser(int argc, char** argv) {
  this->argc = argc;
  this->argv = argv;
}

OPT Parser::parse() {
  if (!(argc > 1)) {
    throw std::runtime_error("Error: No arguments given");
  } else {
    if (strcmp(argv[1], "new") == 0) {
      return NEW;
    } else if (strcmp(argv[1], "check") == 0) {
      return CHECK;
    } else {
      throw std::runtime_error("Error: Invalid argument");
    }
  }
}

toml::table Parser::get_config() {
  toml::table cfg;
  try {
    cfg = toml::parse_file("saleen.toml");
    std::cout << cfg << "\n";
  } catch (const toml::parse_error& err) {
    std::cerr << err.what() << '\n';
    throw std::runtime_error("Error: Invalid config file");
  }

  return cfg;
}