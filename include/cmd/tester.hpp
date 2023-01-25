#ifndef __TESTER_H__
#define __TESTER_H__

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phasewalk1 <github.com/phasewalk1>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 17:33:29 by phasewalk1       #+#    #+#             */
/*   Updated: 2023/01/21 17:33:30 by phasewalk1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/logger.hpp"
#include "util/parser.hpp"

#include <filesystem>

/**
 * @brief The Tester class
 * @dev Used to run the tests in the tests/ directory
 *
 * @fields:
 *   @protected:
 *     TEST_DIR(std::string): The path to the tests/ directory
 *     BUILD_CMD(std::string): The command to build the test files
 */

namespace testing {
/****************************************************************************
 * TestBuilder
 /***************************************************************************/
class TestBuilder {
public:
  TestBuilder();
  TestBuilder(std::string test_dir);
  virtual void setup();
  std::map<std::string, bool> run(std::vector<std::string> test_files);
  virtual std::vector<std::string> get_test_files(manif::Manifest manif);
  virtual bool run_one(std::string test_path);
  virtual void dump_results(std::map<std::string, bool> results);
  virtual void show_passing(const std::string test_path, const bool passing);

protected:
  std::string TEST_DIR;
  std::string BUILD_CMD;
  Logger logger;

  virtual void test_builds();
  virtual std::string get_build_cmd(const std::string test_path);
  virtual void build_test(std::string build_cmd);
  virtual std::string get_invoke_cmd(const std::string test_path);
  virtual bool invoke_test(std::string invoke_cmd);
};

/****************************************************************************
 * SupraException
 /***************************************************************************/
class SupraException : public std::exception {
public:
  SupraException(std::string msg) { this->msg = msg; };
  virtual const char *what() const throw() { return this->msg.c_str(); };

private:
  std::string msg;
};

class SupraWriterException : public SupraException {
public:
  SupraWriterException(std::string msg) : SupraException(msg) {}
};

/****************************************************************************
 *                              SupraTest
 /***************************************************************************/
#define SUPRA_PASS 0
#define SUPRA_FAIL 1

inline std::string get_test_template(std::string name) {
  std::string temp = "// " + name + ".cpp\n\n";
  temp += "#include <iostream>\n#include <supra/tester.hpp>\n\n";
  temp += "// Define test behavior\nstd::optional<testing::SupraException> "
          "test() {};\n\n";
  temp += "// Run the test\nint main() {\n";
  temp += "  return 0;\n";
  temp += "}\n";
  return temp;
}

class TestWriter {
public:
  static inline void
  write(std::string name, bool init_stage = false,
        std::optional<std::string> tests_dir = std::nullopt) {
    std::string path = "tests/" + name + ".cpp";
    switch (init_stage) {
    case false:
      TestWriter::depth_of_manifest();
      if (TestWriter::ok(path)) {
        // create the tests directory if it doesn't exist
        if (!std::filesystem::exists("tests")) {
          std::filesystem::create_directory("tests");
        }
        // create the test file
        std::ofstream test_file;
        test_file.open(path);
        test_file << testing::get_test_template(name);
        test_file.close();
      } else {
        throw SupraWriterException("Test file already exists or is not empty");
      }
      break;
    case true:
      if (TestWriter::ok_init(tests_dir)) {
        std::string test_path = tests_dir.value() + "/" + name + ".cpp";
        std::ofstream test_file;
        test_file.open(test_path);
        test_file << testing::get_test_template(name);
        test_file.close();
      }
      break;
    }
  }

  static void depth_of_manifest();
  static bool ok(std::string path);
  static bool ok_init(std::optional<std::string> tests_dir);
};
} // namespace testing
#endif // __TESTER_H__