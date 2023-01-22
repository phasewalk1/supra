#ifndef __FMT_H__
#define __FMT_H__

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fmt.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phasewalk1 <staticanne@skiff.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:12:42 by phasewalk1        #+#    #+#             */
/*   Updated: 2023/01/22 15:12:43 by phasewalk1       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>

namespace fmt {
class Formatter {
public:
  virtual void format();
};
} // namespace fmt

#endif // __FMT_H__