
#ifndef __LOGGER_H__
#define __LOGGER_H__

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phasewalk1 <github.com/phasewalk1    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 18:32:31 by phasewalk1       #+#    #+#             */
/*   Updated: 2023/01/21 18:32:35 by phasewalk1      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#define CLOSE_COLOR "\033[0m"

// The logger only outputs messages of a certain level or higher
enum LogLevel {
  INFO = 0,
  DEBUG = 1,
  WARN = 2,
  ERROR = 3,
};

class Logger {
public:
  Logger();
  Logger(LogLevel lvl);
  virtual void error(const std::string msg);
  virtual void warn(const std::string msg);
  virtual void debug(const std::string msg);
  virtual void info(const std::string msg);
private:
  LogLevel level;
};

#endif // __LOGGER_H__