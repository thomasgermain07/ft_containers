/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 18:23:38 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/26 23:37:33 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "test_header.hpp"
#include "../templates/vector.hpp"
#include <vector>
#include <list>

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

// static void		main_menu()
// {
// 	print_header("Welcome in ft_container correction");
// 	while (1)
// 	{
// 		std::cout << std::endl;
// 		print_header("Choose a test : ");
// 		print_small_header("1 : List");
// 		print_small_header("2 : Vector");
// 		print_small_header("3 : Map");
// 		print_small_header("4 : Stack");
// 		print_small_header("5 : Queue");
// 		print_small_header("6 : Leave");
// 		int			index = 0;
// 		std::cin >> index;
// 		std::cin.clear();
// 		std::cin.ignore();
// 		switch (index)
// 		{
// 		case 1 :
// 			ListTest();
// 			break;
// 		case 2 :
// 			VectorTest();
// 			break;
// 		case 3 :
// 			MapTest();
// 			break;
// 		case 4 :
// 			StackTest();
// 			break;
// 		case 5 :
// 			QueueTest();
// 			break;
// 		case 6 :
// 			return 0;
// 		default:
// 			std::cout << "Wrong input start again" << std::endl;
// 			break;
// 		}
// 	}
// }

void		test_func()
{
	ft::vector<int>			v;
	v.push_back(20);
	while (v.back() - 1)
		v.push_back(v.back() - 1);

	std::cout << "capacity " << v.capacity() << " size " << v.size() << std::endl;
	print(v);

	v.erase(v.begin() + 6, v.begin() + 16);

	std::cout << "capacity " << v.capacity() << " size " << v.size() << std::endl;
	print(v);
}

int			main()
{
	srand(time(NULL));

	test_func();

	std::cin.get();
	system("leaks a.out");

	return 0;
}

/*
	capacity 32 size 10
	20 19 18 17 16 15 4 3 2 1
*/