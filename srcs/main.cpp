/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 08:49:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/04 20:03:21 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <algorithm>
#include "test_header.hpp"
#include <vector>
#include "../templates/vector.hpp"

void		print_header(std::string msg)
{
	std::cout << BOLD << "\t\t" << UNDERLINE << BLUE << msg << RESET << std::endl;
}

void		print_small_header(std::string msg)
{
	std::cout << BOLD << BLUE << msg << RESET << std::endl;
}

void		print_msg(std::string msg)
{
	std::cout << msg << RESET << std::endl;
}
/* ----------------------------------------------------------------------------------------------------------- */
template<class T>
void		print_info(T const &vector)
{
	std::cout << "size : " << vector.size() << std::endl;
	std::cout << "capacity : " << vector.capacity() << std::endl;
}

void		test_func()
{
	ft::vector<int>		v(15);
	for (int i = 0; i < 15; ++i)
		v[i] = i;
	ft::vector<int>::iterator	it = v.begin();
	for (int i = 0; i < 5; ++i)
		++it;
	print(v);
	ft::vector<int>::iterator	it2 = v.insert(it, 42);
	print(v);
	print_info(v);
	std::cout << "ret value = " << *it2 << std::endl;
}

void		test_real_func()
{
	std::vector<int>		v(15);
	for (int i = 0; i < 15; ++i)
		v[i] = i;
	std::vector<int>::iterator	it = v.begin();
	advance(it, 5);
	std::vector<int>::iterator	it2 = v.insert(it, 42);
	print(v);
	print_info(v);
	std::cout << "ret value = " << *it2 << std::endl;
}



int			main()
{
	srand(time(NULL));


	// ListTest();

	test_func();
	std::cout << "\n-------------------------------------------------\n" << std::endl;
	test_real_func();
	std::cout << std::endl;

	std::cout << std::endl;

	std::cout << "Print leaks" << std::endl;
	std::cin.get();
	system("leaks a.out");

	return 0;
}
