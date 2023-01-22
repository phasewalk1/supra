#include "tester.hpp"
#include "parser.hpp"
#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief Construct a new Tester:: Tester object
 * @dev Sets the TEST_DIR to the default value and the BUILD_CMD to the default value
 */
Tester::Tester() {
  this->TEST_DIR = std::string("tests");
  this->BUILD_CMD = std::string("g++ -std=c++17 -o");
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
}

/**
 * @brief Runs the tests in the tests/ directory
 * @dev Iterates through the tests/ directory and runs each test
 *
 * @return std::map<std::string, bool>: A map of test names and their results
 *
 * TODO: Implement this func
 */
std::map<std::string, bool> Tester::run() {
  std::map<std::string, bool> results;
  return results;
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
 *
 * TODO: Implement the actual test checking, i.e. check if the test passes or fails and return the result
 */
bool Tester::run_test(std::string test_path) {
  // run test and return true if it passes
  // return false if it fails  
  if (fs::exists(test_path)) {
    std::string build_path = "build/" + test_path + ".out";
    std::string build_cmd = this->BUILD_CMD + " " + build_path + " " + test_path;
    // create the build/tests directory if it doesn't exist
    if (!fs::exists(build_path)) {
      fs::create_directory("build/tests");
    }
    std::cout << "building test...\n";

    // build test
    try { system(build_cmd.c_str()); }
    catch (std::exception& e) {
      std::cerr << e.what() << '\n';
      return false;
    }

    std::cout << "running test...\n";
    std::string run_cmd = "build/" + test_path + ".out";

    // run test
    try { system(run_cmd.c_str()); }
    catch (std::exception& e) {
      std::cerr << e.what() << '\n';
      return false;
    }
  }
  else {
    throw std::runtime_error("Error: Test file does not exist");
  }
  return true;
}