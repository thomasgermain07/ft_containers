/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 08:49:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/22 15:56:38 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include "templates/list.hpp"
#include "templates/listIterator.hpp"
#include "templates/structs.hpp"


void		test_func()
{
	ft::list<std::string>		f1;

	f1.push_back("Salut a toi");
	f1.push_back("Jeune entrepreneur");
	f1.push_back("Tu reve de devenir riche");
	f1.push_back("Alors met tout sur le 18");
	f1.push_back("end");

	ft::list<std::string>::const_iterator 		it = f1.begin();
	ft::list<std::string>::const_iterator 	it2;

	// it = f1.begin();
	// *it = "salut";
	// for (it = f1.begin(); it != f1.end(); ++it)
	// 	std::cout << *it << std::endl;
	// ++it;
	// std::cout << *it << std::endl;
}

void		test_real_func()
{
	std::list<std::string>		f1;

	std::cout << sizeof(f1) << std::endl;

	f1.push_back("Salut a toi");
	f1.push_back("Jeune entrepreneur");
	f1.push_back("Tu reve de devenir riche");
	f1.push_back("Alors met tout sur le 18");
	f1.push_back("end");

	std::list<std::string>::const_iterator it = f1.begin();
	std::string s2 = "salut";
	// *it = s2;
	for (it = f1.begin(); it != f1.end(); ++it)
		std::cout << *it << std::endl;
	if (it == f1.end())
		std::cout << "\t-> f1.end() reached" << std::endl;
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