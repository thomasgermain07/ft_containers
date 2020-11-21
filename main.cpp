/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 08:49:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/21 16:55:24 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include "templates/list.hpp"


void		test_func()
{
	ft::list<int>		f1;

	f1.push_back(2);
	f1.push_back(5);
	f1.push_back(12);

	ft::list<int>::iterator		it;
	ft::list<int>::iterator		it2;
	it = f1.begin();
	it2 = it;

	std::cout << "it = " << *it << "\nit2 = " << *it2 << std::endl;
	std::cout << "it value address = " << it.operator->() << std::endl;

}

void		test_real_func()
{
	std::list<int>		l1;
	l1.push_back(2);
	l1.push_back(5);
	l1.push_back(12);

	std::list<int>::iterator		it;
	it = l1.begin();
	std::cout << it.operator->() << std::endl;
}

int			main()
{

	test_func();
	std::cout << "\n-------------------------------------------------\n" << std::endl;
	test_real_func();




	// std::cout << "\nPrint leaks" << std::endl;
	// std::cin.get();
	// system("leaks a.out");

	return 0;
}