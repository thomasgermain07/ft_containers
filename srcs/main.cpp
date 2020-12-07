/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 08:49:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/08 00:21:21 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <algorithm>
#include "test_header.hpp"
#include <vector>
#include "../templates/vector.hpp"
#include "../templates/bst.hpp"

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
// void		exec_test(T &v)
// {

// }

void		test_func()
{
	typedef ft::BinaryNode<int>*		node;

	ft::BinarySearchTree<int>		bst;
	for (int i = 0; i < 500; ++i)
		bst.add_node(rand() % 200);
	std::cout << bst.size() << std::endl;
	bst.print();
	if (bst.find(42))
		std::cout << "found 42" << std::endl;
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
