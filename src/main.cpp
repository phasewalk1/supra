/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethangallucci <ethangallucci@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:40:29 by kat               #+#    #+#             */
/*   Updated: 2023/01/21 21:49:40 by ethangalluc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.hpp"
#include "parser.hpp"
#include "runner.hpp"
#include "logger.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

/**
 * @brief Runs the program
 * @dev Throws an error if the number of arguments is invalid
 *
 * @param p(Parser&): The parser
 * @param args(std::vector<std::string>): The arguments
 */
void supra(Parser& p, std::vector<std::string> args) {
  // build a runner over the arguments
  Runner r(args);
  // parse the mode
  OPT mode = p.mode();
  // validate the arguments
  if (p.ok()) {
    // give the runner the parser
    r.set_parser(p);
    // run the program
    try {
      r.run(mode);
    }
    // catch supra runtime err
    catch (std::runtime_error& e) {
      std::cout << e.what() << std::endl;
    }
    // args invalid!
  }
  else {
    throw std::invalid_argument("Error: Invalid number of arguments");
  }
}

int main(int argc, char** argv) {
  // parse command line arguments
  Parser parser(argc, argv);
  std::vector<std::string> args = parser.get_argv();

  // run supra
  supra(parser, args);
}