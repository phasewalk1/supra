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
  } catch (const toml::parse_error& err) {
    std::cerr << err.what() << '\n';
    throw std::runtime_error("Error: Invalid config file");
  }

  return cfg;
}

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

inline void Parser::debug_deps(std::vector<Dependency> deps) {
  for (auto& dep : deps) {
    for (const auto& [key, value] : dep.dep) {
      std::cout << "DEP: " << key << "\tVERSION: " << value << std::endl;
    }
  }
}

Manifest Parser::to_manifest(toml::table cfg) {
  Manifest manifest;

  Package pkg = to_package(cfg);
  std::vector<Dependency> deps = to_deps(cfg);

  return manifest;
}