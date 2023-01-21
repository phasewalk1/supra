#include "parser.hpp"

// brief: Overloaded Parser constructor
// param: argc: int - number of arguments, argv: char** - array of arguments
// return: Parser - a Parser object
Parser::Parser(int argc, char** argv) {
  this->argc = argc;
  this->argv = argv;
}

// brief: Parses the first argument passed, i.e. the mode to run in
// return: OPT - the mode to run in
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

// brief: Parses the manifest .toml file
// return: toml::table - the parsed manifest file
toml::table Parser::get_config() {
  toml::table cfg;
  try {
    cfg = toml::parse_file("saleen.toml");
  } catch (const toml::parse_error& err) {
    std::cerr << err.what() << '\n';
    throw std::runtime_error("Error: Invalid config file");
  }

  return cfg;
}

// brief: Parses the package section of the manifest file
// param: cfg: toml::table - the parsed manifest file
// return: Package - the parsed package section
Package Parser::to_package(toml::table cfg) {
  Package pkg;

  std::string name = cfg["package"]["name"].value_exact<std::string>().value();
  std::string version =
      cfg["package"]["version"].value_exact<std::string>().value();
  std::optional<std::string> description =
      cfg["package"]["description"].value_exact<std::string>();

  pkg.name = name;
  pkg.version = version;
  pkg.description = description;

  return pkg;
}

// brief: Parses the dependencies section of the manifest file
// param: cfg: toml::table - the parsed manifest file
// return: std::vector<Dependency> - the parsed dependencies section
std::vector<Dependency> Parser::to_deps(toml::table cfg) {
  std::vector<Dependency> deps;

  for (auto& [key, value] : *cfg["deps"].as_table()) {
    Dependency dep;
    std::string key_string = std::string(key);
    std::string value_string = value.value_exact<std::string>().value();
    dep[key_string] = value_string;
    deps.push_back(dep);
  }

  return deps;
}

// brief: Prints the dependencies section of the manifest file
// param: deps: std::vector<Dependency> - the parsed dependencies section
// dev: This is a debug function
inline void Parser::debug_deps(std::vector<Dependency> deps) {
  for (auto& dep : deps) {
    for (const auto& [key, value] : dep.dep) {
      std::cout << "DEP: " << key << "\tVERSION: " << value << std::endl;
    }
  }
}

// brief: Parses the manifest file into a Manifest object
// param: cfg: toml::table - the parsed manifest file
// return: Manifest - the parsed manifest file
Manifest Parser::to_manifest(toml::table cfg) {
  Manifest manifest;

  Package pkg = to_package(cfg);
  std::vector<Dependency> deps = to_deps(cfg);

  return manifest;
}