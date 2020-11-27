/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 14:29:00 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/27 14:25:39 by thgermai         ###   ########.fr       */
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
	void		rprint(T const &list)
	{
		typename T::const_reverse_iterator 		it;
		for (it = list.rbegin(); it != list.rend(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << "list size : " << list.size() << std::endl;
	}

	template<class T>
	void		print(T const &list)
	{
		typename T::const_iterator 		it;
		for (it = list.begin(); it != list.end(); ++it)
			std::cout << *it << " ";
		std::cout << std::endl;
		std::cout << "list size : " << list.size() << std::endl;
}
}

#endif