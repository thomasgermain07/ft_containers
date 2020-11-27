/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 08:49:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/27 16:15:29 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include "templates/list.hpp"
#include "templates/listIterator.hpp"
#include "templates/structs.hpp"

void		test_func()
{
	ft::list<int> 		l;
	ft::list<int>		l2;

	l.push_back(10);
	while (l.back() > 1)
	{
		l.push_back(l.back() - 1);
		l2.push_front(l.back() * 3);
	}

	l.splice(++l.begin(), l2, ++l2.begin(), --l2.end());
	ft::print(l);
	l.erase(++l.begin());
	ft::print(l);
}

void		test_real_func()
{
	std::list<int> 		l;
	std::list<int>		l2;

	l.push_back(10);
	while (l.back() > 1)
	{
		l.push_back(l.back() - 1);
		l2.push_front(l.back() * 3);
	}

	l.splice(++l.begin(), l2, ++l2.begin(), --l2.end());
	ft::print(l);
	l.erase(++l.begin());
	ft::print(l);
}

int			main()
{

	test_func();
	std::cout << "\n-------------------------------------------------\n" << std::endl;
	test_real_func();
	std::cout << std::endl;

	std::cout << "Print leaks" << std::endl;
	std::cin.get();
	system("leaks a.out");

	return 0;
}
