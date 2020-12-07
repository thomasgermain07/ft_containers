/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 08:49:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/07 17:00:40 by thgermai         ###   ########.fr       */
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

template<class T>
void		exec_test(T &v)
{
	v.push_back(15);
	while (v.back())
		v.push_back(v.back() - 1);
	v.insert(++v.begin(), 5, 42);
	v.pop_back();
	print(v);
	rprint(v);
}

void		test_func()
{
	ft::vector<int>		v;
	exec_test<ft::vector<int> >(v);
}

void		test_real_func()
{
	std::vector<int>		v;
	exec_test<std::vector<int> >(v);
}



int			main()
{
	srand(time(NULL));


	// ListTest();

	test_func();
	std::cout << "\n-------------------------------------------------\n" << std::endl;
	test_real_func();
	std::cout << "\n" << std::endl;

	std::cout << "Print leaks" << std::endl;
	std::cin.get();
	system("leaks a.out");

	return 0;
}
