/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phasewalk1 <staticanne@skiff.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:39:12 by kat               #+#    #+#             */
/*   Updated: 2023/01/24 22:22:14 by phasewalk1       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/runner.hpp"

#include "cmd/fmt.hpp"
#include "cmd/init.hpp"
#include "cmd/tester.hpp"
#include "util/logger.hpp"
#include "util/parser.hpp"

using manif::Manifest;
using parsing::OPT;
using parsing::Parser;
using runner::Runner;
using testing::TestBuilder;

#define NEW_PATH_ARG_IDX 2
#define NEW_FLAG_ARG_IDX 3

Runner::Runner(std::vector<std::string> argv) {
  this->argc = argv.size();
  this->args = argv;
}

/**
 * @brief Switch on this->mode and run the program in the specified mode
 * @dev Throws an error if the mode is invalid or if the arguments are invalid
 */
void Runner::run(OPT mode) {
  std::string path;
  TestBuilder builder;
  std::tuple<TestBuilder, std::map<std::string, bool>> builder_and_results;

  switch (mode) {
  // ******* CHECK MODE *******
  case OPT::CHECK:
    this->check();
    break;
  // ******* NEW MODE *******
  case OPT::NEW:
    // ******* CREATE TEST MODE *******
    if (this->cparser.has_flags(std::vector<std::string>{"-t", "--test"})) {
      std::string name = this->args[NEW_FLAG_ARG_IDX];
      testing::TestWriter::write(name, false);
      break;
    }
    // ******* PURE NEW MODE *******
    else {
      std::tuple<std::string, bool, bool> deps = this->get_new_args();
      std::string path = std::get<0>(deps);
      bool force = std::get<1>(deps);
      bool with_benches = std::get<2>(deps);
      this->instantiate(path, force, with_benches);
      break;
    }
  // ******* TEST MODE *******
  case OPT::TEST:
    builder_and_results = this->test();
    builder = std::get<0>(builder_and_results);
    builder.dump_results(std::get<1>(builder_and_results));
    break;
  case OPT::FMT:
    fmt::Formatter fmt = fmt::Formatter();
    fmt.format();
    break;
  }
}

std::tuple<std::string, bool, bool> Runner::get_new_args() {
  std::string path = this->args[NEW_PATH_ARG_IDX];
  bool force, with_benches;
  if (this->cparser.has_one_flag()) {
    // Check if the --with-benches flag is set
    if (this->cparser.has_flags(
            std::vector<std::string>{"-b", "--with-benches"})) {
      with_benches = true;
    } else {
      with_benches = false;
    }
    if (this->cparser.has_flag("--force")) {
      force = true;
    } else {
      force = false;
    }
  } else {
    with_benches = false;
    force = false;
  }

  return std::make_tuple(path, force, with_benches);
}

/**
 * @brief Executes the 'new' command
 *
 * @param path(std::string): The path to the directory to create (relative to
 * the current directory
 * @param with_benches(bool): Whether or not to create benchmark directory
 * (default: false)
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
    toml::table cfg = this->mparser->get_config();
    Manifest manif = this->mparser->into_manifest(cfg);
    std::cout << "Manifest checks out!"
              << "\n";
  } catch (std::runtime_error &e) {
    std::cout << e.what() << std::endl;
  }
}

std::tuple<TestBuilder, std::vector<std::string>> Runner::setup_tester() {
  TestBuilder builder = TestBuilder();
  Manifest manif = this->mparser->into_manifest(this->mparser->get_config());
  std::vector<std::string> test_files = builder.get_test_files(manif);
  return std::make_tuple(builder, test_files);
}

std::tuple<TestBuilder, std::map<std::string, bool>> Runner::test() {
  std::tuple<TestBuilder, std::vector<std::string>> builder_and_args =
      this->setup_tester();
  TestBuilder builder = std::get<0>(builder_and_args);
  std::vector<std::string> test_files = std::get<1>(builder_and_args);
  std::map<std::string, bool> results = builder.run(test_files);
  return std::make_tuple(builder, results);
}