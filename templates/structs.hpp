/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 14:29:00 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/02 14:01:46 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS
# define STRUCTS

# include <iostream>

namespace	ft
{
	template<class T>
	struct 			_node
	{
		T				*data;
		_node			*next;
		_node			*prev;
	};
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
		return (a <= b);
	}
}

#endif