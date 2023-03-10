#ifndef __RUNNER_H__
#define __RUNNER_H__

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phasewalk1 <github.com/phasewalk1>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 13:00:13 by phasewalk1       #+#    #+#             */
/*   Updated: 2023/01/21 13:00:15 by phasewalk1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/tester.hpp"
#include "util/logger.hpp"
#include "util/manif.hpp"
#include "util/parser.hpp"

using manif::ManifParser;
using parsing::OPT;
using parsing::Parser;
using testing::TestBuilder;

namespace runner {
/**
 * @brief: The main runner class for the 'saleen' program
 * @dev: Used to run the program in the specified mode
 *
 * @fields:
 *   @private:
 *     argc(int): The number of arguments passed to the program
 *     argv(char**): The arguments passed to the program
 *     mode(OPT): The mode to run the program in
 */
class Runner {
public:
  Runner(std::vector<std::string> args);
  inline void set_parser(const Parser parser) { this->cparser = parser; };
  inline void set_manif_parser(const ManifParser parser) {
    this->mparser = parser;
  }
  virtual void run(OPT mode);

private:
  Parser cparser;
  std::optional<ManifParser> mparser;
  std::vector<std::string> args;
  size_t argc;

  virtual void instantiate(std::string path, bool force, bool with_benches);
  virtual void check();
  virtual std::tuple<TestBuilder, std::vector<std::string>> setup_tester();
  virtual std::tuple<TestBuilder, std::map<std::string, bool>> test();
  std::tuple<std::string, bool, bool> get_new_args();
};
} // namespace runner

#endif // __RUNNER_H__