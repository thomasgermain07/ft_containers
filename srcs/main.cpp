/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 08:49:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/10 23:33:21 by thgermai         ###   ########.fr       */
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
	ft::map<int, std::string>		m;

	m[44] = "Challa je suis un génie";
	m[15] = "bonsoir";
	m[8] = "bonsoir ici";
	m[17] = "salut toi";
	m.insert(42, "best school");
	m.insert(10, "salut");
	m.insert(58, "Patrick Balkani");
	m.insert(22, "Michel vedette");
	m[50] = "Je m'aime";
	m[53] = "Je m'aime encore plus";
	m[63] = "final";

	ft::map<int, std::string>::iterator		it;
	for (it = m.begin(); it != m.end(); ++it)
		std::cout << it->first << " " << it->second << std::endl;
}

void		test_real_func()
{
	typedef std::pair<int, std::string>	p;

	std::map<int, std::string>		m;

	m[15] = "bonsoir";
	m[8] = "bonsoir ici";
	m[17] = "salut toi";
	m.insert(p(42, "best school"));
	m.insert(p(10, "salut"));
	m.insert(p(58, "Patrick Balkani"));
	m.insert(p(22, "Michel vedette"));
	m[44] = "Challa je suis un génie";
	m[50] = "Je m'aime";
	m[53] = "Je m'aime encore plus";
	m[63] = "final";

	std::map<int, std::string>::iterator		it;
	for (it = m.begin(); it != m.end(); ++it)
		std::cout << it->first << " " << it->second << std::endl;
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
