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

// TODO: Add more options
// brief: Enumerate options, i.e. modes to run in
enum OPT {
  NEW,
  CHECK,
};

// brief: Package information
// dev: Use std::optional for optional fields
struct Package {
  std::string name;
  std::string version;
  std::optional<std::string> description;
  std::optional<std::vector<std::string>> authors;
};

// brief: Dependency information
// dev: A std::map is used to strongly type the key-value pairs, e.g.
// ["name"]:["version"]
struct Dependency {
  std::map<std::string, std::string> dep;
  std::string& operator[](const std::string& key) { return dep[key]; }
};

// brief: Manifest information
// dev: A manifest is a combination of a package, its metadata, and its
// dependencies
struct Manifest {
  Package package;
  std::vector<Dependency> deps;
};

// brief: In charge of various parsing tasks
// dev: Used for parsing runner mode, manifest file, and manifest file sections
class Parser {
public:
  // Constructor
  Parser(int argc, char** argv);
  // Parse the mode to run in
  OPT parse();
  // Parse the manifest into a toml::table
  toml::table get_config();
  // Parse the toml::table into a Manifest struct
  Manifest to_manifest(toml::table cfg);
  // Debug pring the listed dependencies within saleen.toml
  inline void debug_deps(std::vector<Dependency> deps);

private:
  // argument count: for the runner
  int argc;
  // argument vector: for the runner
  char** argv;

  // Parse the package section of the manifest file
  // dev: called by `to_manifest()`
  Package to_package(toml::table cfg);
  // Parse the dependencies section of the manifest file
  // dev: called by `to_manifest()`
  std::vector<Dependency> to_deps(toml::table cfg);
};

#endif // __PARSER_H__