/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethangallucci <ethangallucci@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:40:24 by kat               #+#    #+#             */
/*   Updated: 2023/01/21 21:49:20 by ethangalluc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"
#include "runner.hpp"

#include <cstring>

Parser::Parser() {
  this->argc = 0;
  this->argv = {};
}

/**
 * @brief Construct a new Parser:: Parser object
 *
 * @param argc(int): The number of arguments passed to the program
 * @param argv(char**): The arguments passed to the program
 */
Parser::Parser(int argc, char** argv) {
  this->argc = argc;
  this->argv = this->collect_argv(argv);
}

/**
 * @brief Collects the argv array into a vector
 *
 * @return std::vector<std::string>
 */
std::vector<std::string> Parser::collect_argv(char** argv) {
  std::vector<std::string> vec;
  for (int i = 0; i < this->argc; i++) {
    vec.push_back(argv[i]);
  }
  return vec;
}

/**
 * @brief Parses the first argument, e.g. the option to run the program in. ('check', 'new', etc.)
 * @dev Throws an error if no arguments are given or if the argument is invalid
 *
 * @return OPT: the option to run the program in
 */
OPT Parser::mode() {
  if (!(argc > 1)) {
    throw std::runtime_error("Error: No arguments given");
  }
  else {
    if (argv[1] == "new") {
      this->opt = OPT::NEW;
      return NEW;
    }
    else if (argv[1] == "check") {
      this->opt = OPT::CHECK;
      return CHECK;
    }
    else if (argv[1] == "test") {
      this->opt = OPT::TEST;
      return TEST;
    }
    else {
      throw std::runtime_error("Error: Invalid argument");
    }
  }
}

/**
 * @brief Validates the number of arguments for the given option
 *
 * @return (true) If argc is valid for the given option
 * @return (false) If argc is invalid for the given option
*/
bool Parser::ok() {
  switch (this->opt) {
  case OPT::NEW:
    return this->argc >= 3;
  case OPT::CHECK:
    return this->argc == 2;
  case OPT::TEST:
    return this->argc == 2;
  }
}

/**
 * @brief Checks if any flags are present in the arguments
 *
 * @return (true) If argv contains any flags
 * @return (false) If argv contains no flags
*/
bool Parser::has_one_flag() {
  switch (this->opt) {
  case OPT::NEW:
    return this->argc >= 4;
  case OPT::CHECK:
    return this->argc >= 3;
  case OPT::TEST:
    return this->argc >= 3;
  }
}

/**
 * @brief Checks if a specific flag is present in the arguments
 *
 * @param flag(std::string): The flag to check for
 * @return (true) If argv contains the flag
 * @return (false) If argv does not contain the flag
*/
bool Parser::has_flag(const std::string flag) {
  for (auto arg : this->argv) {
    if (arg == flag) {
      return true;
    }
  }
  return false;
}

/**
 * @brief Parses the manifest file into a toml object
 * @dev Throws an error if the manifest file is invalid or if it doesn't exist
 *
 * @return toml::table
 */
toml::table Parser::get_config() {
  toml::table cfg;
  try {
    cfg = toml::parse_file("supra.toml");
  }
  catch (const toml::parse_error& err) {
    std::cerr << err.what() << '\n';
    throw std::runtime_error("Error: Invalid config file");
  }

  return cfg;
}

/**
 * @brief Parses the package section into a Package object
 *
 * @param cfg(toml::table): The parsed manifest file
 * @return Package
 */
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

/**
 * @brief Parses the dependencies section into a vector of Dependency objects
 *
 * @param cfg(toml::table): The parsed manifest file
 * @return std::vector<Dependency>
 */
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

/**
 * @brief Print the dependencies to the console
 * @dev This is for debugging purposes only
 *
 * @param deps(std::vector<Dependency>): The dependencies to print
 */
inline void Parser::debug_deps(std::vector<Dependency> deps) {
  for (auto& dep : deps) {
    for (const auto& [key, value] : dep.dep) {
      std::cout << "DEP: " << key << "\tVERSION: " << value << std::endl;
    }
  }
}

/**
 * @brief Parses the tests section into a map of test names and paths
 *
 * @param cfg(toml::table): The parsed manifest file
 * @return std::map<std::string, std::string>
 */
std::map<std::string, std::string> Parser::to_tests(toml::table cfg) {
  std::map<std::string, std::string> tests;

  for (auto& [key, value] : *cfg["tests"].as_table()) {
    std::string key_string = std::string(key);
    std::string value_string = value.value_exact<std::string>().value();
    tests[key_string] = value_string;
  }

  return tests;
}

/**
 * @brief Parses the manifest file into a Manifest object
 * @dev Internally calls to_package() and to_deps()
 *
 * @param cfg(toml::table): The parsed manifest file
 * @return Manifest
 */
Manifest Parser::to_manifest(toml::table cfg) {
  Manifest manifest;

  Package pkg = to_package(cfg);
  std::vector<Dependency> deps = to_deps(cfg);
  std::map<std::string, std::string> tests = to_tests(cfg);

  manifest.package = pkg;
  manifest.deps = deps;
  manifest.tests = tests;

  return manifest;
}