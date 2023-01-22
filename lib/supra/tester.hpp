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

/**
 * @brief The Tester class
 * @dev Used to run the tests in the tests/ directory
 *
 * @fields:
 *   @protected:
 *     TEST_DIR(std::string): The path to the tests/ directory
 *     BUILD_CMD(std::string): The command to build the test files
 */

namespace tester {
class Tester {
public:
  Tester();
  Tester(std::string test_dir);
  virtual void setup();
  std::map<std::string, bool> run(std::vector<std::string> test_files);
  virtual std::vector<std::string> get_test_files(manif::Manifest manif);
  virtual bool run_one(std::string test_path);
  virtual void dump_results(std::map<std::string, bool> results);

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

class SupraException : public std::exception {
public:
  SupraException(std::string msg) { this->msg = msg; };
  virtual const char *what() const throw() { return this->msg.c_str(); };

private:
  std::string msg;
};
};     // namespace tester
#endif // __TESTER_H__