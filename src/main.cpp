/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kat <kat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:40:29 by kat               #+#    #+#             */
/*   Updated: 2023/01/21 20:04:11 by kat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.hpp"`
#include "parser.hpp"
#include "runner.hpp"
#include "logger.hpp"

#include <iostream>
#include <stdexcept>
#include <string>

void saleen(Parser& p, std::vector<std::string> args) {
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
    // catch saleen runtime err
    catch (std::runtime_error& e) {
      std::cout << e.what() << std::endl;
    }
    // args invalid!
  } else {
    throw std::invalid_argument("Error: Invalid number of arguments");
  }
}

int main(int argc, char** argv) {
  // parse command line arguments
  Parser parser(argc, argv);
  std::vector<std::string> args = parser.get_argv();
  
  // run saleen
  saleen(parser, args);
}