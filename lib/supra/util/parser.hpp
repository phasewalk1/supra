#ifndef __PARSER_H__
#define __PARSER_H__

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phasewalk1 <github.com/phasewalk1>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:21:32 by phasewalk1       #+#    #+#             */
/*   Updated: 2023/01/21 01:21:46 by phasewalk1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../extern/toml.hpp"
#include "../util/manif.hpp"

#include <cstring>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace parsing {
/**
 * @brief: Options for the 'saleen' runner
 * @dev: Used to determine the mode to run in
 *
 * @fields:
 *     NEW: Create a new project, consisting of a manifest file, src/, and
 *          tests/ directories, and a Makefile
 *     CHECK: Check the manifest file for errors
 *     TEST: Run the tests in the tests/ directory
 */
  enum OPT {
    NEW,
    CHECK,
    TEST,
  };

  /**
   * @brief: The Parser class
   * @dev: Used to parse the runner options and manifest file
   *
   * @fields:
   *   @private:
   *     argc(int): argument count: for the runner
   *     arg(char**): argument vector: for the runner
   */
  class Parser {
  public:
    // Constructor
    Parser();
    Parser(int argc, char** argv);
    // Convert argv to std::vector
    std::vector<std::string> collect_argv(char** argv);
    // Parse the mode to run in
    OPT mode();
    // Ensure arg count is valid for the mode
    bool ok();
    // Check if the args contain at least one flag
    bool has_one_flag();
    // Check if the args contain a specific flag
    bool has_flag(const std::string flag);

    // Getters
    inline int get_argc() { return this->argc; }
    inline std::vector<std::string> get_argv() { return this->argv; }

  private:
    // argument count: for the runner
    int argc;
    // argument vector: for the runner
    std::vector<std::string> argv;
    // Mode that was parsed from 'parse()'
    OPT opt;
  };
} // namespace parsing

#endif // __PARSER_H__
