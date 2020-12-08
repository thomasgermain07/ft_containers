/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 08:49:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/08 23:42:50 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <algorithm>
#include "test_header.hpp"
#include <map>
#include "../templates/map.hpp"
#include "../templates/bst.hpp"
#include <utility>

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

// template<class T>
// class		comparator : public std::binary_function<T,T,bool>
// {
// public :
// 	comparator() {}
// 	bool 	operator()(const T &x, const T &y) const
// 	{
// 		return x > y;
// 	}
// };


void		test_func()
{
	ft::map<int, std::string>		m;

	m.insert(42, "best school");
	m.insert(10, "salut");
	m.insert(58, "Patrick Balkani");
	m.insert(22, "Michel vedette");

	m[44] = "Challa je suis un génie";

	m.print();

}


// void		test_real_func()
// {

// }

int			main()
{
	srand(time(NULL));


	// ListTest();

	test_func();
	std::cout << "\n-------------------------------------------------\n" << std::endl;
	// test_real_func();
	std::cout << "\n" << std::endl;

	std::cout << "Print leaks" << std::endl;
	std::cin.get();
	system("leaks a.out");

	return 0;
}
