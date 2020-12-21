/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VectorTest.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/16 16:28:22 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/21 02:05:55 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <vector>
#include <iterator>
#include "../templates/vector.hpp"
#include "test_header.hpp"

template<class T>
static void			compare_with_real(std::string category, ft::vector<T> const &l, std::vector<T> const &l2)
{
	bool			error = false;
	std::cout << UNDERLINE << category << " test start" << RESET << std::endl;
	if (l.size() != l2.size())
	{
		std::cerr << WRONG << RED << " vector size isn't the same" << RESET << std::endl;
		error = true;
	}
	typename ft::vector<T>::const_iterator	it = l.begin();
	typename std::vector<T>::const_iterator	it2 = l2.begin();
	while (!error && it != l.end())
	{
		if (*it != *it2)
		{
			std::cerr << WRONG << RED << " vector element are different : " << *it << " | " << *it2 << RESET << std::endl;
			error = true;
		}
		++it;
		++it2;
	}
	if (!error)
		std::cout << VALID << GREEN << BOLD << category << " test passed\n" << RESET << std::endl;
	else
	{
		print(l);
		print(l2);
		std::cerr << WRONG << RED << BOLD << category << " test failed" << RESET << std::endl;
	}
}

template<class T>
static void			compare_capacity_with_real(std::string category, ft::vector<T> const &l, std::vector<T> const &l2)
{
	bool			error = false;
	std::cout << UNDERLINE << category << " test start" << RESET << std::endl;
	if (l.size() != l2.size())
	{
		std::cerr << WRONG << RED << " vector size isn't the same" << RESET << std::endl;
		error = true;
	}
	if (l.capacity() != l2.capacity())
	{
		std::cerr << WRONG << RED << " vector capacity isn't the same" << RESET << std::endl;
		error = true;
	}

	if (!error)
		std::cout << VALID << GREEN << BOLD << category << " test passed\n" << RESET << std::endl;
	else
		std::cerr << WRONG << RED << BOLD << category << " test failed" << RESET << std::endl;
}

static void			test_constructor()
{
	print_small_header("-> Vector constructors");
	ft::vector<int>			l;
	std::vector<int>		sl;
	compare_with_real("Empty constructor", l, sl);
	ft::vector<int>			l2((size_t)5, 42);
	std::vector<int>		sl2((size_t)5, 42);
	compare_with_real("vector of 5 42", l2, sl2);
	ft::vector<int>			l3(++l2.begin(), --l2.end());
	std::vector<int>		sl3(++sl2.begin(), --sl2.end());
	compare_with_real("Copy from range (++l2.begin() to --l2.end())", l3, sl3);
	ft::vector<int>			l4(l);
	std::vector<int>		sl4(sl);
	compare_with_real("Copy from l2", l4, sl4);
	std::cout << std::endl;
}

static void			assignment_test()
{
	print_small_header("-> Vector assignment");
	ft::vector<int>			l;
	std::vector<int>		sl;
	ft::vector<int>			l2((size_t)10, 42);
	std::vector<int>		sl2((size_t)10, 42);
	ft::vector<int>			cpy = l;
	std::vector<int>		scpy = sl;
	compare_with_real("Empty vector assignment", cpy, scpy);
	cpy = l2;
	scpy = sl2;
	compare_with_real("Normal vector assignment", cpy, scpy);
	std::cout << std::endl;
}

static void			begin_rbegin_test()
{
	print_small_header("-> begin() and rbegin()");
	ft::vector<int>		l;
	std::vector<int>	sl;
	l.push_back(5);
	sl.push_back(5);
	while (sl.back())
	{
		l.push_back(l.back() - 1);
		sl.push_back(sl.back() - 1);
	}
	std::cout << "Create ft::vector<int>::iterator it = begin() and compare with real" << std::endl;
	ft::vector<int>::iterator		it = l.begin();
	std::vector<int>::iterator		sit = sl.begin();
	if (*it != *sit)
		std::cerr << WRONG << BOLD << RED << " iterators value differents : " << *it << " | " << *sit << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " begin() test passed" << RESET << std::endl;
	std::cout << "Create ft::vector<int>::reverse_iterator it = ++rbegin() and compare with real" << std::endl;
	ft::vector<int>::reverse_iterator		rit = ++l.rbegin();
	std::vector<int>::reverse_iterator		srit = ++sl.rbegin();
	if (*rit != *srit)
		std::cerr << WRONG << BOLD << RED << " iterators value differents : " << *rit << " | " << *srit << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " rbegin() test passed" << RESET << std::endl;
	std::cout << std::endl;
}

static void			end_rend_test()
{
	print_small_header("-> end() and rend()");
	ft::vector<int>		l;
	std::vector<int>		sl;
	l.push_back(5);
	sl.push_back(5);
	while (sl.back())
	{
		l.push_back(l.back() - 1);
		sl.push_back(sl.back() - 1);
	}
	std::cout << "Create ft::vector<int>::iterator it = end() and compare with real" << std::endl;
	ft::vector<int>::iterator		it = l.end();
	std::vector<int>::iterator		sit = sl.end();
	if (*it != *sit)
		std::cerr << WARNING << BOLD << YELLOW << " undefine behavior, dereferencing end() : " << *it << " | " << *sit << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " end() test passed" << RESET << std::endl;
	std::cout << "Create ft::vector<int>::reverse_iterator it = rend() and compare with real" << std::endl;
	ft::vector<int>::reverse_iterator		rit = l.rend();
	std::vector<int>::reverse_iterator		srit = sl.rend();
	if (*rit != *srit)
		std::cerr << WARNING << BOLD << YELLOW << " undefine behavior, dereferencing rend() : " << *rit << " | " << *srit << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " rend() test passed" << RESET << std::endl;
	std::cout << std::endl;
}

static void			assign_test()
{
	print_small_header("-> Assign()");
	ft::vector<std::string>			l;
	std::vector<std::string>			sl;
	l.assign((size_t)10, "salut");
	sl.assign((size_t)10, "salut");
	compare_with_real("Assigned x10 'salut'", l, sl);
	ft::vector<std::string>			l2;
	std::vector<std::string>			sl2;
	l2.assign(++l.begin(), --l.end());
	sl2.assign(++sl.begin(), --sl.end());
	compare_with_real("Assigned from ++l.begin() to --l.end()", l2, sl2);
	std::cout << std::endl;
}

static void			push_pop_back_test()
{
	print_small_header("-> push_back(), pop_back() and back()");
	ft::vector<int>				l;
	std::vector<int>				sl;
	std::cout << "Creating vector by pushing back 10 and then pushing back() - 1 until back() == 0" << std::endl;
	l.push_back(10);
	sl.push_back(10);
	while (l.back())
		l.push_back(l.back() - 1);
	while (sl.back())
		sl.push_back(sl.back() - 1);
	compare_with_real("push_back() and back()", l, sl);
	std::cout << "Poping back 5 times for each vector" << std::endl;
	for (int i = 0; i < 5; ++i)
	{
		l.pop_back();
		sl.pop_back();
	}
	compare_with_real("pop_back()", l, sl);
	std::cout << std::endl;
}

static void			insert_test()
{
	ft::vector<int>		l;
	std::vector<int>		sl;

	print_small_header("-> insert()");
	l.insert(l.begin(), 42);
	sl.insert(sl.begin(), 42);
	compare_with_real("Insert 42 at begin of empty vector", l, sl);
	l.push_back(10);
	sl.push_back(10);
	while (l.back())
		l.push_back(l.back() - 1);
	while (sl.back())
		sl.push_back(sl.back() - 1);
	ft::vector<int>::iterator		it = l.begin();
	std::vector<int>::iterator	sit = sl.begin();
	for (int i = 0; i < 5; ++i)
	{
		++it;
		++sit;
	}
	l.insert(it, 42);
	sl.insert(sit, 42);
	compare_with_real("Insert 42 at 5th position", l, sl);
	l.insert(it, (size_t)5, 21);
	sl.insert(sit, (size_t)5, 21);
	compare_with_real("Insert x5 21 at 6th position", l, sl);
	std::cout << std::endl;
}

static void			erase_test()
{
	print_small_header("-> erase()");
	ft::vector<int>			l;
	std::vector<int>			sl;
	l.push_back(10);
	sl.push_back(10);
	while (l.back())
		l.push_back(l.back() - 1);
	while (sl.back())
		sl.push_back(sl.back() - 1);
	ft::vector<int>::iterator			it = l.begin();
	std::vector<int>::iterator			sit = sl.begin();
	for (int i = 0; i < 4; ++i)
	{
		++it;
		++sit;
	}
	l.erase(it);
	sl.erase(sit);
	compare_with_real("Erasing 4th element", l, sl);
	l.erase(l.begin(), l.end());
	sl.erase(sl.begin(), sl.end());
	compare_with_real("Erasing from begin() to end()", l, sl);
}

static void			swap_test()
{
	print_small_header("-> swap()");
	ft::vector<int>			l;
	ft::vector<int>			l2;
	std::vector<int>			sl;
	std::vector<int>			sl2;
	l.push_back(10);
	sl.push_back(10);
	while (l.back())
	{
		l.push_back(l.back() - 1);
		sl.push_back(sl.back() - 1);
	}
	l2.push_back(4);
	sl2.push_back(4);
	while (l2.back())
	{
		l2.push_back(l2.back() - 1);
		sl2.push_back(sl2.back() - 1);
	}
	l.swap(l2);
	sl.swap(sl2);
	compare_with_real("Swap l with l2", l, sl);
	swap(l2, l);
	swap(sl2, sl);
	compare_with_real("Swap with the external function l2, l", l2, sl2);
	std::cout << std::endl;
}

static void			resize_test()
{
	print_small_header("-> resize()");
	ft::vector<int>		l;
	std::vector<int>		sl;
	l.push_back(10);
	sl.push_back(10);
	while (l.back())
	{
		l.push_back(l.back() - 1);
		sl.push_back(sl.back() - 1);
	}
	l.resize(15);
	sl.resize(15);
	compare_with_real("resize to 15 default val", l, sl);
	l.resize(5);
	sl.resize(5);
	compare_with_real("resize to 5 default val", l, sl);
	l.resize(10, 42);
	sl.resize(10, 42);
	compare_with_real("resize to 10 with 42 val", l, sl);
	std::cout << std::endl;
}

static void			clear_test()
{
	print_small_header("-> clear()");
	ft::vector<int>		l;
	std::vector<int>		sl;
	l.push_back(10);
	sl.push_back(10);
	while (l.back())
	{
		l.push_back(l.back() - 1);
		sl.push_back(sl.back() - 1);
	}
	l.clear();
	sl.clear();
	compare_with_real("Clear a 11 elements vector", l, sl);
	l.clear();
	sl.clear();
	compare_with_real("Clear an empty vector", l, sl);
	std::cout << std::endl;
}

static void			operator_test()
{
	ft::vector<int>		l;
	std::vector<int>	sl;
	bool				error = false;

	print_small_header("-> operator[]");
	for (int i = 0; i < 15; i++)
	{
		int		rdm = rand() % 42;
		l.push_back(rdm);
		sl.push_back(rdm);
	}
	for (int i = 0; i < 5; ++i)
	{
		int index = rand() % (l.size() - 1);
		if (l[index] != sl[index])
			error = true;
	}
	if (error)
		std::cerr << WRONG << RED << BOLD << "Operator[] test failed" << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " Operator[] test passed" << RESET << std::endl;
	std::cout << std::endl;
}

static void			at_test()
{
	ft::vector<int>		l;
	std::vector<int>	sl;
	bool				error = false;

	print_small_header("-> at()");
	for (int i = 0; i < 15; i++)
	{
		int		rdm = rand() % 42;
		l.push_back(rdm);
		sl.push_back(rdm);
	}
	for (int i = 0; i < 5; ++i)
	{
		int index = rand() % (l.size() - 1);
		if (l.at(index) != sl.at(index))
			error = true;
	}
	if (error)
		std::cerr << WRONG << RED << BOLD << "at() test failed" << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " at() test passed" << RESET << std::endl;
	std::cout << "\nIndex out of range (should throw error)" << std::endl;
	try
	{
		l.at(20);
		std::cerr << WRONG << RED << BOLD << "at() out of index test failed" << RESET << std::endl;
	}
	catch (std::exception const &e)
	{
		std::cout << "exeption error msg : " << e.what() << std::endl;
		std::cout << VALID << BOLD << GREEN << " at() out of index test passed" << RESET << std::endl;
	}
	std::cout << std::endl;
}

static void			reserve_test()
{
	ft::vector<int>		l;
	std::vector<int>	sl;

	print_small_header("-> at()");
	for (int i = 0; i < 15; ++i)
	{
		l.push_back(42);
		sl.push_back(42);
	}
	l.reserve(10);
	sl.reserve(10);
	compare_capacity_with_real("Reserve smaller than size", l, sl);
	l.reserve(10);
	sl.reserve(10);
	compare_capacity_with_real("Reserve same than size", l, sl);
	l.reserve(20);
	sl.reserve(20);
	compare_capacity_with_real("Reserve bigger than size", l, sl);
	std::cout << std::endl;
}

void				VectorTest()
{
	print_header("Vector Tester :\n");
	test_constructor();
	assignment_test();
	begin_rbegin_test();
	end_rend_test();
	assign_test();
	push_pop_back_test();
	insert_test();
	erase_test();
	swap_test();
	resize_test();
	clear_test();
	operator_test();
	at_test();
	reserve_test();
	std::cout << "Press any key to go back to main menu" << std::endl;
	std::cin.get();
}