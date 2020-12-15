/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 08:49:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/15 15:50:13 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <algorithm>
#include "test_header.hpp"
#include <queue>
#include <vector>
#include <list>
#include "../templates/queue.hpp"
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

template<class T>
class		comparator : public std::binary_function<T,T,bool>
{
public :
	comparator() {}
	bool 	operator()(const T &x, const T &y) const
	{
		return x > y;
	}
};

template<class T>
void		print_map(T const &m)
{
	typename T::const_iterator		it;
	for (it = m.begin(); it != m.end(); ++it)
		std::cout << it->first << " " << it->second << std::endl;
}

void		test_func()
{
	ft::queue<int>			s;
	ft::queue<int>			s2;

	if (s == s2)
		std::cout << "s == s2" << std::endl;
	std::cout << std::boolalpha << "s is empty : " << s.empty() << std::endl;

	s.push(15);
	s2.push(20);
	if (s != s2)
		std::cout << "s != s2" << std::endl;
	if (s < s2)
		std::cout << "s < s2" << std::endl;
	if (s2 > s)
		std::cout << "s2 > s" << std::endl;
	for (int i = 0; i < 15; ++i)
		s.push(rand() % 10);
	std::cout << "size : " << s.size() << std::endl;
	while (!s.empty())
	{
		std::cout << s.front() << " ";
		s.pop();
	}
	std::cout << std::endl;
}

void		test_real_func()
{
	std::queue<int>			s;
	std::queue<int>			s2;

	if (s == s2)
		std::cout << "s == s2" << std::endl;
	std::cout << std::boolalpha << "s is empty : " << s.empty() << std::endl;

	s.push(15);
	s2.push(20);
	if (s != s2)
		std::cout << "s != s2" << std::endl;
	if (s < s2)
		std::cout << "s < s2" << std::endl;
	if (s2 > s)
		std::cout << "s2 > s" << std::endl;
	for (int i = 0; i < 15; ++i)
		s.push(rand() % 10);
	std::cout << "size : " << s.size() << std::endl;
	while (!s.empty())
	{
		std::cout << s.front() << " ";
		s.pop();
	}
	std::cout << std::endl;
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
