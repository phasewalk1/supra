/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phasewalk1 <staticanne@skiff.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:14:20 by phasewalk1        #+#    #+#             */
/*   Updated: 2023/01/22 15:56:42 by phasewalk1       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd/fmt.hpp"

#include <filesystem>
#include <regex>
namespace fs = std::filesystem;

void fmt::Formatter::format() {
  std::string fmtcmd = "find . -iname *.hpp -o -iname *.cpp | xargs -P 8 "
                       "-n 2 clang-format -style=LLVM -i";
  std::system(fmtcmd.c_str());
}