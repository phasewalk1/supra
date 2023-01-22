#ifndef __RUNNER_H__
#define __RUNNER_H__

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethangallucci <ethangallucci@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 13:00:13 by ethangalluc       #+#    #+#             */
/*   Updated: 2023/01/21 13:00:15 by ethangalluc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"

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
  virtual void run();

private:
  Parser parser;
  std::vector<std::string> args;
  size_t argc;

  void instantiate(std::string path, bool with_benches);
  void check();
};

#endif // __RUNNER_H__