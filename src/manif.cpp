/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manif.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethangallucci <ethangallucci@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 23:22:33 by ethangalluc       #+#    #+#             */
/*   Updated: 2023/01/21 23:41:45 by ethangalluc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/manif.hpp"
#include "extern/toml.hpp"

#include <iostream>

using manif::ManifParser;
using manif::Manifest;
using manif::Dependency;
using manif::Package;

Manifest ManifParser::into_manifest(toml::table cfg) {
  Package pkg = this->get_package(cfg);
  std::vector<Dependency> deps = this->get_deps(cfg);
  std::map<std::string, std::string> tests = this->get_tests(cfg);
  Manifest manif = { pkg, deps, tests };
  return manif;
}

toml::table ManifParser::get_config() {
  toml::table cfg;
  try { cfg = toml::parse_file("supra.toml"); }
  catch (const toml::parse_error& err) {
    std::cout << err.what() << std::endl;
    throw std::runtime_error("Invalid config file");
  }
  return cfg;
}

Package ManifParser::get_package(toml::table cfg) {
  Package pkg;
  std::string name = cfg["package"]["name"].value_exact<std::string>().value();
  std::string version = cfg["package"]["version"].value_exact<std::string>().value();
  std::optional<std::string> description = cfg["package"]["description"].value_exact<std::string>();
  pkg.name = name;
  pkg.version = version;
  pkg.description = description;
  return pkg;
}

std::vector<Dependency> ManifParser::get_deps(toml::table cfg) {
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

std::map<std::string, std::string> ManifParser::get_tests(toml::table cfg) {
  std::map<std::string, std::string> tests;
  for (auto& [key, value] : *cfg["tests"].as_table()) {
    std::string key_string = std::string(key);
    std::string value_string = value.value_exact<std::string>().value();
    tests[key_string] = value_string;
  }
  return tests;
}

inline void ManifParser::debug_deps(std::vector<Dependency> deps) {
  for (auto dep : deps) {
    for (const auto& [key, value] : dep.dep) {
      std::cout << key << " : " << value << std::endl;
    }
  }
}