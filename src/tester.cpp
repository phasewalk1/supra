/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kat <kat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:40:17 by kat               #+#    #+#             */
/*   Updated: 2023/01/21 21:06:09 by kat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief Construct a new Tester:: Tester object
 * @dev Sets the TEST_DIR to the default value and the BUILD_CMD to the default value
 */
Tester::Tester() {
  this->TEST_DIR = std::string("tests");
  this->BUILD_CMD = std::string("g++ -std=c++17 -o");
  this->logger = Logger();
}

/**
 * @brief Construct a new Tester:: Tester object
 * @dev Sets the TEST_DIR to the specified value and the BUILD_CMD to the default value
 *
 * @param test_dir(std::string): The path to the tests/ directory
 */
Tester::Tester(std::string test_dir) {
  this->TEST_DIR = test_dir;
  this->BUILD_CMD = std::string("g++ -std=c++17 -o");
  this->logger = Logger();
}

/**
 * @brief Performs the setup for the tester
 * @dev Creates "build/tests/" directory if it doesn't exist
 */
void Tester::setup() {
  this->logger.debug("Setting up tester...");
  this->test_builds();
}

/**
 * @brief Gets the build command for a single test
 * @param test_path(std::string): The path to the test file
 * @return (std::string): The build command for the test
*/
std::string Tester::get_build_cmd(const std::string test_path) {
  std::string build_path = "build/" + test_path + ".out";
  std::string build_cmd = this->BUILD_CMD + " " + build_path + " " + test_path;
  return build_cmd;
}

/**
 * @brief Gets the run command for a single test
 * @param test_path(std::string): The path to the test file
 * @return (std::string): The run command for the test
*/
std::string Tester::get_invoke_cmd(const std::string test_path) {
  std::string invoke_cmd = "build/" + test_path + ".out";
  return invoke_cmd;
}

/**
 * @brief Runs the tests in the tests/ directory
 * @dev Iterates through the tests/ directory and runs each test
 *
 * @return std::map<std::string, bool>: A map of test names and their results
 */
std::map<std::string, bool> Tester::run(std::vector<std::string> test_files) {
  std::map<std::string, bool> results;

  this->logger.debug("Running tests...");
  for (std::string file : test_files) {
    std::string path_to_test = "tests/" + file + ".cpp";
    int result = this->run_one(path_to_test);
    bool pass = result == 0 ? true : false;
    results[file] = pass;
  }
  
  return results;
}

/**
 * @brief Dumps the map of test results to the console
 *
 * @param results(std::map<std::string, bool>): A map of test names and their results
 */
void Tester::dump_results(std::map<std::string, bool> results) {
  std::cout << std::endl;
  std::cout << std::string(30, '*') << " TEST RESULTS " << std::string(30, '*') << '\n';
  for (auto const& [file, result] : results) {
    switch (result) {
      case false:
        this->logger.info("Test passed: " + file + ".cpp");
        break;
      case true:
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
std::vector<std::string> Tester::get_test_files(Manifest manif) {
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
bool Tester::run_one(std::string test_path) {
  if (fs::exists(test_path)) {
    std::string BUILD_CMD = this->get_build_cmd(test_path);
    // create the build/tests directory if it doesn't exist
    this->test_builds();
    // build test
    this->logger.info("Building test:"); std::cout << test_path << "\n";
    this->build_test(BUILD_CMD);
    // run test
    this->logger.info("running test..."); std::cout << test_path << "\n";
    std::string run_cmd = this->get_invoke_cmd(test_path);
    // run test
    this->invoke_test(run_cmd);
  }
  else {
    throw std::runtime_error("Error: Test file does not exist");
  }
  return true;
}

/**
 * @brief Creates the build/tests directory if it doesn't exist
 */
void Tester::test_builds() {
  if(!fs::exists("build/tests")) {
    fs::create_directory("build/tests");
  }
}

/**
 * @brief Builds a test
 *
 * @param build_cmd(std::string): The build command for the test
 */
void Tester::build_test(std::string build_cmd) {
  try { system(build_cmd.c_str()); }
  catch (std::exception& e) {
    this->logger.error("Failed building test: " + std::string(e.what()));
  }
}

/**
 * @brief Invokes a test
 *
 * @param invoke_cmd(std::string): The invoke command for the test
 * @return (true) if the test exits 0
 * @return (false) if the test exits 1 or any other value
 */
bool Tester::invoke_test(std::string invoke_cmd) {
  try { 
    int result = system(invoke_cmd.c_str());
    switch (result) {
      case 0:
        this->logger.info("Test passed");
        return true;
      case 1:
        this->logger.error("Test failed: " + invoke_cmd + " returned 1");
        return false;
      default:
        this->logger.error("Test failed: " + invoke_cmd + " returned " + std::to_string(result));
        return false;
    }
  }
  catch (std::exception& e) {
    this->logger.error("Failed invoking test: " + std::string(e.what()));
  }
  return true;
}