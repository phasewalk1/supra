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

#include "toml.hpp"
#include <cstring>
#include <iostream>
#include <stdexcept>

enum OPT {
  NEW,
  CHECK,
};

class Parser {
public:
  Parser(int argc, char** argv);
  OPT parse();
  toml::table get_config();

private:
  int argc;
  char** argv;
};

#endif // __PARSER_H__