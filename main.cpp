/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 08:49:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/28 16:40:45 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include "templates/list.hpp"
#include "templates/listIterator.hpp"
#include "templates/structs.hpp"

bool		is_greater(int a, int b)
{
	return (a < b);
}

void		test_func()
{
	ft::list<int> 		l;

	l.push_back(12);
	l.push_back(0);
	l.push_back(42);
	l.push_back(51);
	l.push_back(3);
	l.push_back(15);
	l.push_back(82);
	l.push_back(14);
	l.push_back(20);
	l.push_back(32);
	l.push_back(8);
	l.push_back(7);

	ft::print(l);
	l.unique(is_greater);
	ft::print(l);
}

void		test_real_func()
{
	std::list<int> 		l;

	l.push_back(12);
	l.push_back(0);
	l.push_back(42);
	l.push_back(51);
	l.push_back(3);
	l.push_back(15);
	l.push_back(82);
	l.push_back(14);
	l.push_back(20);
	l.push_back(32);
	l.push_back(8);
	l.push_back(7);

	ft::print(l);
	l.unique(is_greater);
	ft::print(l);
}

int			main()
{
	srand(time(NULL));
	test_func();
	std::cout << "\n-------------------------------------------------\n" << std::endl;
	test_real_func();
	std::cout << std::endl;

	std::cout << "Print leaks" << std::endl;
	std::cin.get();
	system("leaks a.out");

	return 0;
}
