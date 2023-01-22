#ifndef __PARSER_H__
#define __PARSER_H__

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phasewalk1 <github.com/phasewalk1>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:21:32 by phasewalk1       #+#    #+#             */
/*   Updated: 2023/01/21 01:21:46 by phasewalk1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toml.hpp"

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vector>

/**
 * @brief: Options for the 'saleen' runner
 * @dev: Used to determine the mode to run in
 *
 * @fields:
 *     NEW: Create a new project, consisting of a manifest file, src/, and
 *          tests/ directories, and a Makefile
 *     CHECK: Check the manifest file for errors
 */
enum OPT {
  NEW,
  CHECK,
};

/**
 * @brief: Package metadata information
 * @dev: Used to serialize the package section of the manifest file
 *
 * @fields:
 *    name(std::string): The name of the package
 *    version(std::string): The version of the package
 *    description(std::optional<std::string>): A description of the package
 *    authors(std::optional<std::vector<std::string>>): A list of authors
 */
struct Package {
  std::string name;
  std::string version;
  std::optional<std::string> description;
  std::optional<std::vector<std::string>> authors;
};

/**
 * @brief: A dependency object for a package in the manifest file
 * @dev: Contains a std::map of package names to their version requirements
 *
 * @fields:
 *   dep(std::map<std::string, std::string>): A map of package names to their version
 */
struct Dependency {
  std::map<std::string, std::string> dep;
  std::string& operator[](const std::string& key) { return dep[key]; }
};

/**
 * @brief: A manifest object for a package
 * @dev: Serialized from the manifest file
 *
 * @fields:
 *  package(Package): The package section of the manifest file
 *  deps(std::vector<Dependency>): The deps section of the manifest file
 */
struct Manifest {
  Package package;
  std::vector<Dependency> deps;
};

/**
 * @brief: The Parser class
 * @dev: Used to parse the runner options and manifest file
 *
 * @fields:
 *   @private:
 *     argc(int): argument count: for the runner
 *     arg(char**): argument vector: for the runner
 */
class Parser {
public:
  // Constructor
  Parser();
  Parser(int argc, char** argv);
  // Convert argv to std::vector
  std::vector<std::string> collect_argv(char** argv);
  // Parse the mode to run in
  OPT parse();
  // Ensure arg count is valid for the mode
  bool valid_argc();
  // Parse the manifest into a toml::table
  toml::table get_config();
  // Parse the toml::table into a Manifest struct
  Manifest to_manifest(toml::table cfg);
  // Debug pring the listed dependencies within saleen.toml
  inline void debug_deps(std::vector<Dependency> deps);

  // Getters
  inline int get_argc() { return this->argc; }
  inline std::vector<std::string> get_argv() { return this->argv; }

private:
  // argument count: for the runner
  int argc;
  // argument vector: for the runner
  std::vector<std::string> argv;
  // Mode that was parsed from 'parse()'
  OPT opt;

  // Parse the package section of the manifest file
  // dev: called by `to_manifest()`
  Package to_package(toml::table cfg);
  // Parse the dependencies section of the manifest file
  // dev: called by `to_manifest()`
  std::vector<Dependency> to_deps(toml::table cfg);
};

#endif // __PARSER_H__