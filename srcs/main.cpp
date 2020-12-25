/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/22 18:23:38 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/25 01:09:58 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "test_header.hpp"
#include "../templates/list.hpp"
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
	std::vector<int>			v;
	v.push_back(6);
	while (v.back())
		v.push_back(v.back() - 1);

	ft::list<int>		lst;

	lst.assign(v.begin(), v.end());
	lst.pop_front();
	lst.push_front(42);
	lst.pop_back();
	lst.push_back(42);

	lst.insert(--lst.end(), v.begin(), v.end());
	lst.insert(lst.end(), 51);

	std::list<int>		slst;
	for (ft::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
		slst.push_back(*it);

	ft::list<int>::iterator			it = lst.begin();
	std::list<int>::iterator		sit = slst.begin();

	for (int i = 0; i < 4; ++i)
	{
		++it;
		++sit;
	}

	lst.erase(++lst.begin(), --lst.end());
	slst.erase(++slst.begin(), --slst.end());

	lst.resize(10, 42);
	slst.resize(10, 42);

	lst.resize(8);
	slst.resize(8);

	ft::list<int>			lst2;
	std::list<int>			slst2;

	lst2.push_back(5);
	slst2.push_back(5);

	while (lst2.back())
	{
		lst2.push_back(lst2.back() - 1);
		slst2.push_back(slst2.back() - 1);
	}

	it = lst2.begin();
	sit = slst2.begin();
	for (int i = 0; i < 4; ++i)
	{
		++it;
		++sit;
	}

	lst.splice(lst.end(), lst2, --lst2.end());
	slst.splice(slst.end(), slst2, --slst2.end());

	std::cout << "\nlst && slst" << std::endl;
	lst.print();
	print(slst);
	std::cout << "\nlst2 && slst2" << std::endl;
	lst2.print();
	print(slst2);


	lst.splice(lst.end(), lst2, lst2.begin(), lst2.end());
	slst.splice(slst.end(), slst2, slst2.begin(), slst2.end());


	lst.sort();
	slst.sort();

	lst.unique();
	slst.unique();

	lst2.assign(lst.begin(), lst.end());
	slst2.assign(slst.begin(), slst.end());

	lst.merge(lst2);
	slst.merge(slst2);

	lst.reverse();
	slst.reverse();

	std::cout << "\nlst && slst" << std::endl;
	lst.print();
	print(slst);
	std::cout << "\nlst2 && slst2" << std::endl;
	lst2.print();
	print(slst2);

	lst2.push_front(12);
}

int			main()
{
	srand(time(NULL));

	ListTest();
	test_func();

	std::cin.get();
	system("leaks a.out");

	return 0;
}
