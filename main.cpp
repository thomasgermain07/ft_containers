/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 08:49:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/23 17:29:15 by thgermai         ###   ########.fr       */
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
	// std::vector<int>	v(5, 5);
	// v.push_back(12);
	ft::list<int>		f1((size_t)0, 15);

	// f1.push_back("Salut a toi");
	// f1.push_back("Jeune entrepreneur");
	// f1.push_back("Tu reve de devenir riche");
	// f1.push_back("Alors met tout sur le 18");

	ft::list<int>::const_iterator		it;

	for (it = f1.begin(); it != f1.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void		test_real_func()
{
	std::list<int>		f1;
	std::list<int>::iterator	end = f1.begin();
	f1.push_back(12);
	f1.push_back(12);
	f1.push_back(12);
	std::list<int>::iterator	it;
	for (it = f1.begin(); it != end; ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

int			main()
{

	// test_func();
	std::cout << "\n-------------------------------------------------\n" << std::endl;
	test_real_func();
	std::cout << std::endl;



	// std::cout << "Print leaks" << std::endl;
	// std::cin.get();
	// system("leaks a.out");

	return 0;
}