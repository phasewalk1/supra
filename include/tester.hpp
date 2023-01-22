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

#include "parser.hpp"
#include "logger.hpp"

/**
 * @brief The Tester class
 * @dev Used to run the tests in the tests/ directory
 *
 * @fields:
 *   @protected:
 *     TEST_DIR(std::string): The path to the tests/ directory
 *     BUILD_CMD(std::string): The command to build the test files
 */
class Tester {
public:
  Tester();
  Tester(std::string test_dir);
  std::map<std::string, bool> run();
  virtual std::vector<std::string> get_test_files(Manifest manif);
  virtual bool run_test(std::string test_path);
protected:
  std::string TEST_DIR;
  std::string BUILD_CMD;

  Logger logger;
};

#endif // __TESTER_H__