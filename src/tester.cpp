/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TestBuilder.cpp                                         :+:      :+:    :+:
 */
/*                                                    +:+ +:+         +:+     */
/*   By: phasewalk1 <staticanne@skiff.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:40:17 by kat               #+#    #+#             */
/*   Updated: 2023/01/24 18:16:00 by phasewalk1       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/tester.hpp"

#include <filesystem>

namespace fs = std::filesystem;
using manif::Manifest;
using testing::TestBuilder;
using testing::TestWriter;

/******************************************************************************
 *                          TestBuilder  Impl                                 *
 ******************************************************************************/

/**
 * @brief Construct a new TestBuilder:: TestBuilder object
 * @dev Sets the TEST_DIR to the default value and the BUILD_CMD to the default
 * value
 */
TestBuilder::TestBuilder() {
  this->TEST_DIR = std::string("tests");
  this->BUILD_CMD = std::string("g++ -std=c++17 -o");
  this->logger = Logger();
}

/**
 * @brief Construct a new TestBuilder:: TestBuilder object
 * @dev Sets the TEST_DIR to the specified value and the BUILD_CMD to the
 * default value
 *
 * @param test_dir(std::string): The path to the tests/ directory
 */
TestBuilder::TestBuilder(std::string test_dir) {
  this->TEST_DIR = test_dir;
  this->BUILD_CMD = std::string("g++ -std=c++17 -o");
  this->logger = Logger();
}

/**
 * @brief Performs the setup for the TestBuilder
 * @dev Creates "build/tests/" directory if it doesn't exist
 */
void TestBuilder::setup() {
  this->logger.debug("Setting up TestBuilder...");
  this->test_builds();
}

/**
 * @visibility PROTECTED
 * @brief Gets the build command for a single test
 * @param test_path(std::string): The path to the test file
 * @return (std::string): The build command for the test
 */
std::string TestBuilder::get_build_cmd(const std::string test_path) {
  std::string build_path = "build/" + test_path + ".out";
  std::string build_cmd = this->BUILD_CMD + " " + build_path + " " + test_path;
  return build_cmd;
}

/**
 * @visibility PROTECTED
 * @brief Gets the run command for a single test
 * @param test_path(std::string): The path to the test file
 * @return (std::string): The run command for the test
 */
std::string TestBuilder::get_invoke_cmd(const std::string test_path) {
  std::string invoke_cmd = "build/" + test_path + ".out";
  return invoke_cmd;
}

/**
 * @brief Runs the tests in the tests/ directory
 * @dev Iterates through the tests/ directory and runs each test
 *
 * @return std::map<std::string, bool>: A map of test names and their results
 */
std::map<std::string, bool>
TestBuilder::run(std::vector<std::string> test_files) {
  std::map<std::string, bool> results;

  this->logger.debug("Running tests...");
  for (std::string file : test_files) {
    std::string path_to_test = "tests/" + file + ".cpp";
    int result = this->run_one(path_to_test);
    bool pass = result == true ? true : false;
    results[file] = pass;
  }

  return results;
}

/**
 * @brief Dumps the map of test results to the console
 *
 * @param results(std::map<std::string, bool>): A map of test names and their
 * results
 */
void TestBuilder::dump_results(std::map<std::string, bool> results) {
  std::cout << std::endl;
  std::cout << std::string(30, '*') << " TEST RESULTS " << std::string(30, '*')
            << '\n';
  for (auto const &[file, result] : results) {
    switch (result) {
    case true:
      this->logger.info("Test passed: " + file + ".cpp");
      break;
    case false:
      this->logger.error("Test failed: " + file + ".cpp");
      break;
    }
  }
}

/**
 * @brief Get a list of test files from the manifest (saleen.toml)
 *
 * @param manif(Manifest): The manifest (saleen.toml) object
 * @return std::vector<std::string>: A vector of test file paths
 */
std::vector<std::string> TestBuilder::get_test_files(Manifest manif) {
  // iterate through manif.tests and extract values
  // return vector of test files
  std::vector<std::string> test_files;

  this->logger.debug("Getting test files from manifest...");
  // iterate through manif.tests map and extract key-values
  for (auto it = manif.tests.begin(); it != manif.tests.end(); it++) {
    test_files.push_back(it->first);
  }

  return test_files;
}

/**
 * @brief Runs a single test file
 *
 * @param test_path(std::string): The path to the test file
 * @return true if the test passes
 * @return false if the test fails
 */
bool TestBuilder::run_one(std::string test_path) {
  if (fs::exists(test_path)) {
    std::string BUILD_CMD = this->get_build_cmd(test_path);
    // create the build/tests directory if it doesn't exist
    this->test_builds();
    // build test
    this->logger.debug("Building test:");
    std::cout << test_path << "\n";
    this->build_test(BUILD_CMD);
    // run test
    this->logger.debug("running test...");
    std::cout << test_path << "\n";
    std::string run_cmd = this->get_invoke_cmd(test_path);
    // run test
    bool passing = this->invoke_test(run_cmd);
    this->show_passing(test_path, passing);
    return passing;
  } else {
    throw std::runtime_error("Error: Test file does not exist");
  }
}

/**
 * @visibility PROTECTED
 * @brief Creates the build/tests directory if it doesn't exist
 */
void TestBuilder::test_builds() {
  if (!fs::exists("build/tests")) {
    fs::create_directory("build/tests");
  }
}

/**
 * @visibility PROTECTED
 * @brief Builds a test
 *
 * @param build_cmd(std::string): The build command for the test
 */
void TestBuilder::build_test(std::string build_cmd) {
  try {
    system(build_cmd.c_str());
  } catch (std::exception &e) {
    this->logger.error("Failed building test: " + std::string(e.what()));
  }
}

/**
 * @visibility PROTECTED
 * @brief Invokes a test
 *
 * @param invoke_cmd(std::string): The invoke command for the test
 * @return (true) if the test exits 0
 * @return (false) if the test exits 1 or any other value
 */
bool TestBuilder::invoke_test(std::string invoke_cmd) {
  int result = system(invoke_cmd.c_str());
  switch (result) {
  case 0:
    return true;
  default:
    return false;
  }
}

void TestBuilder::show_passing(const std::string test_path,
                               bool const passing) {
  switch (passing) {
  case true:
    this->logger.info(test_path + " --> " + "PASS");
    break;
  case false:
    this->logger.error(test_path + " --> " + "FAIL");
    break;
  }
}