/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 08:49:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/25 14:55:29 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include <vector>
#include "templates/list.hpp"
#include "templates/listIterator.hpp"
#include "templates/structs.hpp"

template<class T>
void		print(T list)
{
	typename T::const_iterator 		it;
	for (it = list.begin(); it != list.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "list size : " << list.size() << std::endl;
}

void		test_func()
{
	ft::list<int> 		l;

	l.push_back(9);
	while (l.back())
		l.push_back(l.back() - 1);

	ft::list<int>::const_reverse_iterator		rit;
	for (rit = l.rbegin(); rit != l.rend(); ++rit)
	{
		std::cout << *rit << " ";
		*rit = *rit - 1;
	}
	std::cout << std::endl;
	print(l);
}

void		test_real_func()
{
	std::list<int> 		l;

	l.push_back(9);
	while (l.back())
		l.push_back(l.back() - 1);

	std::list<int>::const_reverse_iterator		rit;
	for (rit = l.rbegin(); rit != l.rend(); ++rit)
	{
		std::cout << *rit << " ";
		*rit = *rit - 1;
	}
	std::cout << std::endl;
	print(l);
}

int			main()
{

	test_func();
	std::cout << "\n-------------------------------------------------\n" << std::endl;
	test_real_func();
	std::cout << std::endl;

	// std::cout << "Print leaks" << std::endl;
	// std::cin.get();
	// system("leaks a.out");

	return 0;
}