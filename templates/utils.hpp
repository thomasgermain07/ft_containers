/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 14:29:00 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/24 00:15:58 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS
# define UTILS

# include <iostream>

namespace	ft
{
	template<typename X>
	void					_swap(X &c, X &d)
	{
		X _tmp = c;
		c = d;
		d = _tmp;
	}
	template<class T>
	bool		basic_comp(T a, T b)
	{
		return (a < b);
	}
}

#endif