/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 08:49:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/24 11:18:35 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include <vector>
#include "templates/list.hpp"
#include "templates/listIterator.hpp"
#include "templates/structs.hpp"

void		test_func()
{
	ft::list<int> 		l((size_t)10, 42);

	ft::list<int>::const_iterator		it;
	for (it = l.begin(); it != l.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void		test_real_func()
{
	std::list<const int>			f1((size_t)6, 42);
	int const		&ref = f1.front();

	std::list<const int>::const_iterator it;
	for (it = f1.begin(); it != f1.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

int			main()
{

	test_func();
	std::cout << "\n-------------------------------------------------\n" << std::endl;
	// test_real_func();
	std::cout << std::endl;

	// std::cout << "Print leaks" << std::endl;
	// std::cin.get();
	system("leaks a.out");

	return 0;
}