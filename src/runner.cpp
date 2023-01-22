/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethangallucci <ethangallucci@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:39:12 by kat               #+#    #+#             */
/*   Updated: 2023/01/21 21:55:40 by ethangalluc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/parser.hpp"
#include "util/runner.hpp"
#include "cmd/init.hpp"
#include "cmd/tester.hpp"

#define NEW_PATH_ARG_IDX 2
#define NEW_FLAG_ARG_IDX 3

Runner::Runner(std::vector<std::string> argv) {
  this->argc = argv.size();
  this->args = argv;
}

/**
 * @brief Set the parser instance to use for this runner
 *
 * @param parser(Parser): The parser instance to use
 */
void Runner::set_parser(Parser parser) {
  this->parser = parser;
}

/**
 * @brief Switch on this->mode and run the program in the specified mode
 * @dev Throws an error if the mode is invalid or if the arguments are invalid
 */
void Runner::run(OPT mode) {
  std::string path;
  switch (mode) {
  // ******* CHECK MODE *******
  case OPT::CHECK:
    this->check();
    break;
  // ******* NEW MODE *******
  case OPT::NEW:
    // Get the path to the new project
    path = this->args[NEW_PATH_ARG_IDX];
    bool force, with_benches;
    if (this->parser.has_one_flag()) {
      // Check if the --with-benches flag is set
      if (this->parser.has_flag("-b") || this->parser.has_flag("--with-benches")) {
        with_benches = true;
      }
      else {
        with_benches = false;
      }
      if (this->parser.has_flag("--force")) {
        force = true;
      }
      else {
        force = false;
      }
    }
    else {
      with_benches = false;
      force = false;
    }
    // Create the new project
    this->instantiate(path, force, with_benches);
    break;
  // ******* TEST MODE *******
  case OPT::TEST:
    std::tuple<Tester, std::vector<std::string>> tester_and_args = this->setup_tester();
    Tester tester = std::get<0>(tester_and_args);
    std::vector<std::string> test_files = std::get<1>(tester_and_args);
    std::map<std::string, bool> results = tester.run(test_files);
    tester.dump_results(results);
  }
}

/**
 * @brief Executes the 'new' command
 *
 * @param path(std::string): The path to the directory to create (relative to the current directory
 * @param with_benches(bool): Whether or not to create benchmark directory (default: false)
 */
void Runner::instantiate(std::string path, bool force, bool with_benches) {
  Initializer init = Initializer(path, force);
  init.spinup(with_benches);
}

/**
 * @brief Checks validity of the saleen.toml manifest file
 *
 */
void Runner::check() {
  try {
    toml::table cfg = this->parser.get_config();
    Manifest manif = this->parser.to_manifest(cfg);
    std::cout << "Manifest checks out!" << "\n";
  }
  catch (std::runtime_error& e) {
    std::cout << e.what() << std::endl;
  }
}

std::tuple<Tester, std::vector<std::string>>Runner::setup_tester() {
  Tester tester = Tester();
  Manifest manif = this->parser.to_manifest(this->parser.get_config());
  std::vector<std::string> test_files = tester.get_test_files(manif);
  return std::make_tuple(tester, test_files);
}