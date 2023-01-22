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

#include "parser.hpp"
#include "tester.hpp"

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
  void set_parser(Parser parser);
  virtual void run(OPT mode);

private:
  Parser parser;
  std::vector<std::string> args;
  size_t argc;

  virtual void instantiate(std::string path, bool force, bool with_benches);
  virtual void check();
  virtual std::tuple<Tester, std::vector<std::string>> setup_tester();
};

#endif // __RUNNER_H__