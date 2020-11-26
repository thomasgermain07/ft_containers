/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 08:49:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/26 10:15:56 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include <vector>
#include <iterator>
#include "templates/list.hpp"
#include "templates/listIterator.hpp"
#include "templates/structs.hpp"

template<class T>
void		print(T const &list)
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
	ft::list<int>		l2;

	l.push_back(10);
	while (l.back() > 1)
	{
		l.push_back(l.back() - 1);
		l2.push_front(l.back() * 3);
	}
	print(l);
	print(l2);
	ft::list<int>::iterator		it = l.begin();
	for (int i = 0; i < 5; i++)
		++it;
	l.splice(it, l2);
	print(l);
	print(l2);
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
	print(l);
	print(l2);

	std::list<int>::iterator		it = l.begin();
	for (int i = 0; i < 5; i++)
		++it;
	l.splice(it, l2);
	print(l);
	print(l2);
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