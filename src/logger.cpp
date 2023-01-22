/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kat <kat@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 19:40:33 by kat               #+#    #+#             */
/*   Updated: 2023/01/21 19:40:35 by kat              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logger.hpp"

// Defaults to lowest level of logging
Logger::Logger() {
  this->level = INFO;
}

Logger::Logger(LogLevel lvl) {
  this->level = lvl;
}

void Logger::error(const std::string message) {
  std::string err = "\033[1;31m[ERROR]: " + message + "\033[0m";
  std::cout << err << std::endl;
}

void Logger::warn(const std::string message) {
  std::string warn = "\033[1;33m[WARN]: " + message + "\033[0m";
  if (this->level <= 2) {
    std::cout << warn << std::endl;
  }
}

void Logger::debug(const std::string message) {
  std::string debug = "\033[1;34m[DEBUG]: " + message + "\033[0m";
  if (this->level <= 1) {
    std::cout << debug << std::endl;
  }
}

void Logger::info(const std::string message) {
  std::string info = "\033[1;32m[INFO]: " + message + "\033[0m";
  if (this->level <= 0) {
    std::cout << info << std::endl;
  }
  else {
    return;
  }
}