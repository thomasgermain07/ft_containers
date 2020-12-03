/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ListTest.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:26:50 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/02 14:09:26 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <vector>
#include <iterator>
#include "../templates/list.hpp"
#include "../templates/listIterator.hpp"
#include "../templates/structs.hpp"
#include "test_header.hpp"

template<class T>
static void			compare_with_real(std::string category, ft::list<T> const &l, std::list<T> const &l2)
{
	bool			error = false;
	std::cout << UNDERLINE << category << " test start" << RESET << std::endl;
	if (l.size() != l2.size())
	{
		std::cerr << WRONG << RED << " list size isn't the same" << RESET << std::endl;
		error = true;
	}
	typename ft::list<T>::const_iterator		it = l.begin();
	typename std::list<T>::const_iterator	it2 = l2.begin();
	while (!error && it != l.end())
	{
		if (*it != *it2)
		{
			std::cerr << WRONG << RED << " list element are different : " << *it << " | " << *it2 << RESET << std::endl;
			error = true;
		}
		++it;
		++it2;
	}
	print(l); // to del
	print(l2); // to del
	if (!error)
		std::cout << VALID << GREEN << BOLD << category << " test passed\n" << RESET << std::endl;
	else
	{
		// print(l);
		// print(l2);
		std::cerr << WRONG << RED << BOLD << category << " test failed" << RESET << std::endl;
	}
}

static void			test_constructor()
{
	print_small_header("-> List constructors");
	ft::list<int>			l;
	std::list<int>			sl;
	compare_with_real("Empty constructor", l, sl);
	ft::list<int>			l2((size_t)5, 42);
	std::list<int>			sl2((size_t)5, 42);
	compare_with_real("List of 5 42", l2, sl2);
	ft::list<int>			l3(++l2.begin(), --l2.end());
	std::list<int>			sl3(++sl2.begin(), --sl2.end());
	compare_with_real("Copy from range (++l2.begin() to --l2.end())", l3, sl3);
	ft::list<int>			l4(l);
	std::list<int>			sl4(sl);
	compare_with_real("Copy from l2", l4, sl4);
	std::cout << std::endl;
}

static void			assignment_test()
{
	print_small_header("-> List assignment");
	ft::list<int>			l;
	std::list<int>			sl;
	ft::list<int>			l2((size_t)10, 42);
	std::list<int>			sl2((size_t)10, 42);
	ft::list<int>			cpy = l;
	std::list<int>			scpy = sl;
	compare_with_real("Empty list assignment", cpy, scpy);
	cpy = l2;
	scpy = sl2;
	compare_with_real("Normal list assignment", cpy, scpy);
	std::cout << std::endl;
}

static void			begin_rbegin_test()
{
	print_small_header("-> begin() and rbegin()");
	ft::list<int>		l;
	std::list<int>		sl;
	l.push_back(5);
	sl.push_back(5);
	while (sl.back())
	{
		l.push_back(l.back() - 1);
		sl.push_back(sl.back() - 1);
	}
	std::cout << "Create ft::list<int>::iterator it = begin() and compare with real" << std::endl;
	ft::list<int>::iterator		it = l.begin();
	std::list<int>::iterator		sit = sl.begin();
	if (*it != *sit)
		std::cerr << WRONG << BOLD << RED << " iterators value differents : " << *it << " | " << *sit << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " begin() test passed" << RESET << std::endl;
	std::cout << "Create ft::list<int>::reverse_iterator it = rbegin() and compare with real" << std::endl;
	ft::list<int>::reverse_iterator		rit = l.rbegin();
	std::list<int>::reverse_iterator		srit = sl.rbegin();
	if (*rit != *srit)
		std::cerr << WRONG << BOLD << RED << " iterators value differents : " << *rit << " | " << *srit << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " rbegin() test passed" << RESET << std::endl;
	std::cout << std::endl;
}

static void			end_rend_test()
{
	print_small_header("-> end() and rend()");
	ft::list<int>		l;
	std::list<int>		sl;
	l.push_back(5);
	sl.push_back(5);
	while (sl.back())
	{
		l.push_back(l.back() - 1);
		sl.push_back(sl.back() - 1);
	}
	std::cout << "Create ft::list<int>::iterator it = end() and compare with real" << std::endl;
	ft::list<int>::iterator		it = l.end();
	std::list<int>::iterator		sit = sl.end();
	if (*it != *sit)
		std::cerr << WARNING << BOLD << YELLOW << " undefine behavior, dereferencing end() : " << *it << " | " << *sit << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " end() test passed" << RESET << std::endl;
	std::cout << "Create ft::list<int>::reverse_iterator it = rend() and compare with real" << std::endl;
	ft::list<int>::reverse_iterator		rit = l.rend();
	std::list<int>::reverse_iterator		srit = sl.rend();
	if (*rit != *srit)
		std::cerr << WARNING << BOLD << YELLOW << " undefine behavior, dereferencing rend() : " << *rit << " | " << *srit << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " rend() test passed" << RESET << std::endl;
	std::cout << std::endl;
}

static void			empty_size_test()
{
	print_small_header("-> empty() and size()");
	ft::list<int>			l;
	std::list<int>			l2;
	std::cout << "testing empty and size on empty list" << std::endl;
	if (l.size() != l2.size())
		std::cerr << WRONG << BOLD << RED << " differents size between l and l2 : " << l.size() << " | " << l2.size() << RESET << std::endl;
	else if (l.empty() != l2.empty())
		std::cerr << WRONG << BOLD << RED << " empty() didn't return true" << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " empty() size() on empty list test passed" << RESET << std::endl;
	std::cout << "testing empty and size on a 15 element list" << std::endl;
	l.assign((size_t)15, 42);
	l2.assign((size_t)15, 42);
	if (l.size() != l2.size())
		std::cerr << WRONG << BOLD << RED << " differents size between l and l2 : " << l.size() << " | " << l2.size() << RESET << std::endl;
	else if (l.empty() != l2.empty())
		std::cerr << WRONG << BOLD << RED << " empty() didn't return false" << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " empty() size() on a 15 element list test passed" << RESET << std::endl;
	std::cout << std::endl;
}

static void			assign_test()
{
	print_small_header("-> Assign()");
	ft::list<std::string>			l;
	std::list<std::string>			sl;
	l.assign((size_t)10, "salut");
	sl.assign((size_t)10, "salut");
	compare_with_real("Assigned x10 'salut'", l, sl);
	ft::list<std::string>			l2;
	std::list<std::string>			sl2;
	l2.assign(++l.begin(), --l.end());
	sl2.assign(++sl.begin(), --sl.end());
	compare_with_real("Assigned from ++l.begin() to --l.end()", l2, sl2);
	std::cout << std::endl;
}

static void			push_pop_front_test()
{
	print_small_header("-> push_front(), pop_front() and front()");
	ft::list<int>				l;
	std::list<int>				sl;
	std::cout << "Creating list by pushing front 10 and then pushing front() - 1 until front() == 0" << std::endl;
	l.push_front(10);
	sl.push_front(10);
	while (l.front())
		l.push_front(l.front() - 1);
	while (sl.front())
		sl.push_front(sl.front() - 1);
	compare_with_real("push_front() and front()", l, sl);
	std::cout << "Poping front 5 times for each list" << std::endl;
	for (int i = 0; i < 5; ++i)
	{
		l.pop_front();
		sl.pop_front();
	}
	compare_with_real("pop_front()", l, sl);
	std::cout << std::endl;
}

static void			push_pop_back_test()
{
	print_small_header("-> push_back(), pop_back() and back()");
	ft::list<int>				l;
	std::list<int>				sl;
	std::cout << "Creating list by pushing back 10 and then pushing back() - 1 until back() == 0" << std::endl;
	l.push_back(10);
	sl.push_back(10);
	while (l.back())
		l.push_back(l.back() - 1);
	while (sl.back())
		sl.push_back(sl.back() - 1);
	compare_with_real("push_back() and back()", l, sl);
	std::cout << "Poping back 5 times for each list" << std::endl;
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
	ft::list<int>		l;
	std::list<int>		sl;

	print_small_header("-> insert()");
	l.insert(l.begin(), 42);
	sl.insert(sl.begin(), 42);
	compare_with_real("Insert 42 at begin of empty list", l, sl);
	l.push_back(10);
	sl.push_back(10);
	while (l.back())
		l.push_back(l.back() - 1);
	while (sl.back())
		sl.push_back(sl.back() - 1);
	ft::list<int>::iterator		it = l.begin();
	std::list<int>::iterator	sit = sl.begin();
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
	ft::list<int>			l;
	std::list<int>			sl;
	l.push_back(10);
	sl.push_back(10);
	while (l.back())
		l.push_back(l.back() - 1);
	while (sl.back())
		sl.push_back(sl.back() - 1);
	ft::list<int>::iterator			it = l.begin();
	std::list<int>::iterator			sit = sl.begin();
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
	ft::list<int>			l;
	ft::list<int>			l2;
	std::list<int>			sl;
	std::list<int>			sl2;
	l.push_back(10);
	sl.push_back(10);
	while (l.back())
	{
		l.push_back(l.back() - 1);
		sl.push_back(sl.back() - 1);
	}
	l2.push_front(4);
	sl2.push_front(4);
	while (l2.front())
	{
		l2.push_front(l2.front() - 1);
		sl2.push_front(sl2.front() - 1);
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
	ft::list<int>		l;
	std::list<int>		sl;
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
	ft::list<int>		l;
	std::list<int>		sl;
	l.push_back(10);
	sl.push_back(10);
	while (l.back())
	{
		l.push_back(l.back() - 1);
		sl.push_back(sl.back() - 1);
	}
	l.clear();
	sl.clear();
	compare_with_real("Clear a 11 elements list", l, sl);
	l.clear();
	sl.clear();
	compare_with_real("Clear an empty list", l, sl);
	std::cout << std::endl;
}

static void			splice_test()
{
	print_small_header("-> splice()");
	ft::list<int>		l;
	ft::list<int>		l2;
	std::list<int>		sl;
	std::list<int>		sl2;
	l.push_back(10);
	l2.push_front(5);
	sl.push_back(10);
	sl2.push_front(5);
	while (l.back())
	{
		l.push_back(l.back() - 1);
		sl.push_back(sl.back() - 1);
	}
	while (l2.front())
	{
		l2.push_front(l2.front() - 1);
		sl2.push_front(sl2.front() - 1);
	}
	ft::list<int>::iterator			it = l.begin();
	std::list<int>::iterator		sit = sl.begin();
	for (int i = 0; i < 3; ++i)
	{
		++it;
		++sit;
	}
	ft::list<int>		l3(l);
	std::list<int>		sl3(sl);
	l.splice(it, l2);
	sl.splice(sit, sl2);
	compare_with_real("splice l2 at 3rd elem of l", l, sl);
	ft::list<int>::iterator			it2 = l3.begin();
	std::list<int>::iterator		sit2 = sl3.begin();
	for (int i = 0; i < 3; ++i)
	{
		++it2;
		++sit2;
	}
	l.splice(it, l3, it2);
	sl.splice(sit, sl3, sit2);
	compare_with_real("splice 4th element of l3 at 3rd place of l", l, sl);
	l.splice(l.begin(), l3, l3.begin(), l3.end());
	sl.splice(sl.begin(), sl3, sl3.begin(), sl3.end());
	compare_with_real("splice l3 from begin() to end() at l.begin()", l, sl);
	std::cout << std::endl;
}

static void			remove_test()
{
	print_small_header("-> remove()");
	ft::list<int>		l;
	std::list<int>		sl;
	l.push_back(10);
	sl.push_back(10);
	while (l.back())
	{
		l.push_back(l.back() - 1);
		l.insert(--l.end(), 42);
		sl.push_back(sl.back() - 1);
		sl.insert(--sl.end(), 42);
	}
	l.remove(42);
	sl.remove(42);
	compare_with_real("removed all 42 from the list", l, sl);
	std::cout << std::endl;
}

static bool 		comp(int a)
{
	return (a - 2 > 5);
}

static void			remove_if_test()
{
	print_small_header("-> remove_if()");
	ft::list<int>		l;
	std::list<int>		sl;
	l.push_back(10);
	l.push_back(9);
	l.push_back(6);
	l.push_back(4);
	l.push_back(12);
	l.push_back(1);
	sl.push_back(10);
	sl.push_back(9);
	sl.push_back(6);
	sl.push_back(4);
	sl.push_back(12);
	sl.push_back(1);
	l.remove_if(comp);
	sl.remove_if(comp);
	compare_with_real("removed with comp func", l, sl);
	std::cout << std::endl;
}

static bool			comp2(int a, int b)
{
	return a < b;
}

static void			unique_sort_merge_reverse_test()
{
	print_small_header("-> sort(), merge(), unique() and reverse()");
	ft::list<int>		l;
	std::list<int>		sl;
	ft::list<int>		l2;
	std::list<int>		sl2;
	for (int i = 0; i < 30; ++i)
	{
		l.push_back(rand() % 10);
		sl.push_back(l.back());
		l2.push_back(rand() % 20);
		sl2.push_back(l2.back());
	}
	l.sort();
	sl.sort();
	compare_with_real("sorted l with default comp", l, sl);
	l2.sort(comp2);
	sl2.sort(comp2);
	compare_with_real("sorted l2 with comp2 func", l2, sl2);
	l.merge(l2);
	sl.merge(sl2);
	compare_with_real("merge l2 into l2", l, sl);
	l.unique();
	sl.unique();
	compare_with_real("called unique on l to delete multiple elements", l, sl);
	l.reverse();
	sl.reverse();
	compare_with_real("reversed l", l, sl);
	std::cout << std::endl;
}

void				ListTest()
{
	print_header("List Tester :\n");
	test_constructor();
	assignment_test();
	begin_rbegin_test();
	end_rend_test();
	empty_size_test();
	assign_test();
	push_pop_front_test();
	push_pop_back_test();
	insert_test();
	erase_test();
	swap_test();
	resize_test();
	clear_test();
	splice_test();
	remove_test();
	remove_if_test();
	unique_sort_merge_reverse_test();
}