#ifndef __PARSER_H__
#define __PARSER_H__

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethangallucci <ethangallucci@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:21:32 by ethangalluc       #+#    #+#             */
/*   Updated: 2023/01/21 01:21:46 by ethangalluc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cstring>
#include <iostream>
#include <stdexcept>

enum OPT {
  NEW,
};

class Parser {
public:
  Parser(int argc, char** argv);
  OPT parse();

protected:
  int argc;
  char** argv;
};

Parser::Parser(int argc, char** argv) {
  this->argc = argc;
  this->argv = argv;
}

OPT Parser::parse() {
  if (!(argc > 1)) {
    throw std::runtime_error("Error: No arguments given");
  } else {
    if (strcmp(argv[1], "new") == 0) {
      return NEW;
    } else {
      throw std::runtime_error("Error: Invalid argument");
    }
  }
}

#endif // __PARSER_H__