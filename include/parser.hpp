#ifndef __PARSER_H__
#define __PARSER_H__

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethangallucci <ethangallucci@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:21:32 by ethangalluc       #+#    #+#             */
/*   Updated: 2023/01/21 01:21:46 by ethangalluc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "toml.hpp"
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vector>

enum OPT {
  NEW,
  CHECK,
};

struct Package {
  std::string name;
  std::string version;
  std::optional<std::string> description;
  std::optional<std::vector<std::string>> authors;
};

struct Dependency {
  std::map<std::string, std::string> dep;
  std::string& operator[](const std::string& key) { return dep[key]; }
};

struct Manifest {
  Package package;
  std::vector<Dependency> deps;
};

class Parser {
public:
  Parser(int argc, char** argv);
  OPT parse();
  toml::table get_config();
  Manifest to_manifest(toml::table cfg);
  inline void debug_deps(std::vector<Dependency> deps);

private:
  int argc;
  char** argv;

  Package to_package(toml::table cfg);
  std::vector<Dependency> to_deps(toml::table cfg);
};

#endif // __PARSER_H__