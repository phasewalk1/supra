#ifndef __LIB_H__
#define __LIB_H__

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethangallucci <ethangallucci@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 23:55:41 by ethangalluc       #+#    #+#             */
/*   Updated: 2023/01/21 23:55:42 by ethangalluc      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "util/manif.hpp"
#include "util/parser.hpp"
#include "util/runner.hpp"

namespace supra {
  using manif::Manifest;
  using manif::ManifParser;
  using manif::Dependency;
  using manif::Package;

  using parsing::Parser;
  using parsing::OPT;

  using runner::Runner;
}

#endif // __LIB_H__