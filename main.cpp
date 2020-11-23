/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 08:49:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/23 13:17:20 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <list>
#include "templates/list.hpp"
#include "templates/listIterator.hpp"
#include "templates/structs.hpp"

void		test_func()
{
	ft::list<int>		f1;

	// f1.push_back("Salut a toi");
	// f1.push_back("Jeune entrepreneur");
	// f1.push_back("Tu reve de devenir riche");
	// f1.push_back("Alors met tout sur le 18");
	// f1.push_back("end");

	f1.push_back(2);
	f1.push_back(24);
	f1.push_back(42);

	ft::list<int>::iterator				n_it = f1.begin();
	ft::list<int>::const_iterator		it(n_it);
	for (it = f1.begin(); it != f1.end(); ++it)
		std::cout << *it << std::endl;
	if (it == f1.end())
		std::cout << "We reached _end_node" << std::endl;
}

void		test_real_func()
{
	std::list<int>		f1;

	f1.push_back(2);
	f1.push_back(24);
	f1.push_back(42);

	std::list<int>::const_iterator			const_it;
	for (const_it = f1.begin(); const_it != f1.end(); ++const_it)
		std::cout << *const_it << std::endl;
}

int			main()
{

	test_func();
	std::cout << "\n-------------------------------------------------\n" << std::endl;
	test_real_func();
	std::cout << std::endl;



	// std::cout << "Print leaks" << std::endl;
	// std::cin.get();
	// system("leaks a.out");

	return 0;
}