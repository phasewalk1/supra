#ifndef __NEW_H__
#define __NEW_H__

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethangallucci <ethangallucci@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 01:57:29 by ethangalluc       #+#    #+#             */
/*   Updated: 2023/01/21 01:57:30 by ethangalluc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class Initializer {
public:
  Initializer(std::string path);
  void init_dir();

private:
  std::string path;
};

#endif // __NEW_H__