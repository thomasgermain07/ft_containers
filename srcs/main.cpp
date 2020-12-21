/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 08:49:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/21 02:09:03 by thgermai         ###   ########.fr       */
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

int			main()
{
	srand(time(NULL));
	print_header("Welcome in ft_container correction");
	while (1)
	{
		std::cout << std::endl;
		print_header("Choose a test : ");
		print_small_header("1 : List");
		print_small_header("2 : Vector");
		print_small_header("3 : Map");
		print_small_header("4 : Stack");
		print_small_header("5: Queue");
		print_small_header("6: Leave");
		int			index = 0;
		std::cin >> index;
		std::cin.clear();
		std::cin.ignore();
		switch (index)
		{
		case 1 :
			ListTest();
			break;
		case 2 :
			VectorTest();
			break;
		case 3 :
			MapTest();
			break;
		case 4 :
			StackTest();
			break;
		case 5 :
			QueueTest();
			break;
		case 6 :
			return 0;
		default:
			std::cout << "Wrong input start again" << std::endl;
			break;
		}
	}

	return 0;
}
