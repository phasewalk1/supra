#ifndef __RUNNER_H__
#define __RUNNER_H__

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runner.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethangallucci <ethangallucci@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 13:00:13 by ethangalluc       #+#    #+#             */
/*   Updated: 2023/01/21 13:00:15 by ethangalluc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.hpp"

class Runner {
public:
  Runner(int argc, char** argv, OPT mode);
  virtual void run();

protected:
  int argc;
  char** argv;
  OPT mode;
};

#endif // __RUNNER_H__