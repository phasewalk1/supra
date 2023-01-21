#ifndef __INIT_H__
#define __INIT_H__

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethangallucci <ethangallucci@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:57:29 by ethangalluc       #+#    #+#             */
/*   Updated: 2023/01/21 02:43:24 by ethangalluc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <filesystem>
#include <fstream>
#include <string>

namespace fs = std::filesystem;

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