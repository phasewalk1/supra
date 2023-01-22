/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phasewalk1 <staticanne@skiff.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:40:24 by kat               #+#    #+#             */
/*   Updated: 2023/01/22 15:21:37 by phasewalk1       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/parser.hpp"

#include <cstring>

#include "util/runner.hpp"

using parsing::OPT;
using parsing::Parser;

Parser::Parser() {
  this->argc = 0;
  this->argv = {};
}

/**
 * @brief Construct a new Parser:: Parser object
 *
 * @param argc(int): The number of arguments passed to the program
 * @param argv(char**): The arguments passed to the program
 */
Parser::Parser(int argc, char **argv) {
  this->argc = argc;
  this->argv = this->collect_argv(argv);
}

/**
 * @brief Collects the argv array into a vector
 *
 * @return std::vector<std::string>
 */
std::vector<std::string> Parser::collect_argv(char **argv) {
  std::vector<std::string> vec;
  for (int i = 0; i < this->argc; i++) {
    vec.push_back(argv[i]);
  }
  return vec;
}

/**
 * @brief Parses the first argument, e.g. the option to run the program in.
 * ('check', 'new', etc.)
 * @dev Throws an error if no arguments are given or if the argument is invalid
 *
 * @return OPT: the option to run the program in
 */
OPT Parser::mode() {
  if (!(argc > 1)) {
    throw std::runtime_error("Error: No arguments given");
  } else {
    if (argv[1] == "new") {
      this->opt = OPT::NEW;
      return NEW;
    } else if (argv[1] == "check") {
      this->opt = OPT::CHECK;
      return CHECK;
    } else if (argv[1] == "test") {
      this->opt = OPT::TEST;
      return TEST;
    } else if (argv[1] == "fmt") {
      this->opt = OPT::FMT;
      return FMT;
    } else {
      throw std::runtime_error("Error: Invalid argument");
    }
  }
}

/**
 * @brief Validates the number of arguments for the given option
 *
 * @return (true) If argc is valid for the given option
 * @return (false) If argc is invalid for the given option
 */
bool Parser::ok() {
  switch (this->opt) {
  case OPT::NEW:
    return this->argc >= 3;
  case OPT::CHECK:
    return this->argc == 2;
  case OPT::TEST:
    return this->argc == 2;
  case OPT::FMT:
    return this->argc == 2;
  }
}

/**
 * @brief Checks if any flags are present in the arguments
 *
 * @return (true) If argv contains any flags
 * @return (false) If argv contains no flags
 */
bool Parser::has_one_flag() {
  switch (this->opt) {
  case OPT::NEW:
    return this->argc >= 4;
  case OPT::CHECK:
    return this->argc >= 3;
  case OPT::TEST:
    return this->argc >= 3;
  }
}

/**
 * @brief Checks if a specific flag is present in the arguments
 *
 * @param flag(std::string): The flag to check for
 * @return (true) If argv contains the flag
 * @return (false) If argv does not contain the flag
 */
bool Parser::has_flag(const std::string flag) {
  for (auto arg : this->argv) {
    if (arg == flag) {
      return true;
    }
  }
  return false;
}