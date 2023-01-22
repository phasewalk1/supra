#ifndef __MANIF_H__
#define __MANIF_H__

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manif.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phasewalk1 <github.com/phasewalk1    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:53:34 by phasewalk1       #+#    #+#             */
/*   Updated: 2023/01/21 18:53:35 by phasewalk1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extern/toml.hpp"
#include <optional>

namespace manif {
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
    std::map<std::string, std::string> tests;
  };

  class ManifParser {
  public:
    toml::table get_config();
    Manifest into_manifest(toml::table cfg);
    virtual void debug_deps(std::vector<Dependency> deps);
  private:
    Package get_package(toml::table cfg);
    std::vector<Dependency> get_deps(toml::table cfg);
    std::map<std::string, std::string> get_tests(toml::table cfg);
  };

} // namespace manif

#endif // __MANIF_H__
