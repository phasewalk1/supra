#ifndef __INIT_H__
#define __INIT_H__

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phasewalk1 <github.com/phasewalk1>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:57:29 by phasewalk1       #+#    #+#             */
/*   Updated: 2023/01/21 02:43:24 by phasewalk1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <filesystem>
#include <fstream>
#include <string>

// Alias for std::filesystem
namespace fs = std::filesystem;

/**
 * @brief: In charge of executing the 'new' command
 * @dev: Creates a new project directory, with a manifest file, src/, and tests/, and makefile
 *
 * @fields:
 *   @private:
 *     path(std::string): The path to the new project directory
 */
class Initializer {
public:
  Initializer(std::string path);
  void init_dir(bool bench_mode);
  void makefile();
  void make_git();

private:
  std::string path;
};

#endif // __INIT_H__