/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapTest.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/17 18:29:14 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/21 02:05:43 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_header.hpp"
#include "../templates/map.hpp"
#include <map>
#include <vector>
#include <sstream>

std::string			bank_word[30] = { "interference", "goat", "ash", "president", "unfair", "liver", "earthquake", "ambiguity", "agile",
"wardrobe", "storm", "exploit", "hallway", "tablet", "absorption", "crown", "butterfly", "tin", "spin", "bullet", "outlet",
 "expertise", "we", "first-hand", "daughter", "rule", "warning", "tissue", "twist", "leader" };

template<class Iterator>
static std::string	display_it(const Iterator& it)
{
	std::stringstream		ss;
	ss << it->first << " " << it->second;
	return ss.str();
}

template<class T, class X>
static void			compare_with_real(std::string category, ft::map<T, X> const &l, std::map<T, X> const &l2)
{
	bool			error = false;
	std::cout << UNDERLINE << category << " test start" << RESET << std::endl;
	if (l.size() != l2.size())
	{
		std::cerr << WRONG << RED << " map size isn't the same" << RESET << std::endl;
		error = true;
	}
	typename ft::map<T, X>::const_iterator	it = l.begin();
	typename std::map<T, X>::const_iterator	it2 = l2.begin();
	while (!error && it != l.end())
	{
		if (*it != *it2)
		{
			std::cerr << WRONG << RED << " map element are different : " << display_it(it) << " | " << display_it(it2) << RESET << std::endl;
			error = true;
		}
		++it;
		++it2;
	}
	if (!error)

		std::cout << VALID << GREEN << BOLD << category << " test passed\n" << RESET << std::endl;
	else
	{
		print_map(l);
		print_map(l2);
		std::cerr << WRONG << RED << BOLD << category << " test failed" << RESET << std::endl;
	}
}

static void			test_constructor()
{
	print_small_header("-> Map constructors");
	ft::map<int, std::string>			l;
	std::map<int, std::string>			sl;
	compare_with_real("Empty constructor", l, sl);
	std::vector<std::pair<int, std::string> >	base;
	for (int i = 0; i < 15; ++i)
		base.push_back(std::pair<int, std::string>(i, bank_word[rand() % 29]));
	ft::map<int, std::string>			l2(base.begin(), base.end());
	std::map<int, std::string>			sl2(base.begin(), base.end());
	compare_with_real("Range constructor", l2, sl2);
	ft::map<int, std::string>			l3(l2);
	std::map<int, std::string>			sl3(sl2);
	compare_with_real("Copy constructor", l3, sl3);
	ft::map<int, std::string>			l4 = l3;
	std::map<int, std::string>			sl4 = sl3;
	compare_with_real("Operator = assignement", l4, sl4);
	std::cout << std::endl;
}

static void			begin_rbegin()
{
	print_small_header("-> Begin() rbegin()");
	ft::map<int, std::string>		l;
	std::map<int, std::string>		sl;
	for (int i = 0; i < 15; ++i)
	{
		std::string wrd = bank_word[rand() % 29];
		l[i] = wrd;
		sl[i] = wrd;
	}
	std::cout << "Create ft::map<int, std::string>::iterator it = begin() and compare with real" << std::endl;
	ft::map<int, std::string>::iterator			it = l.begin();
	std::map<int, std::string>::iterator		sit = sl.begin();
	if (*it != *sit)
		std::cerr << WRONG << BOLD << RED << " iterators value differents : " << display_it(it) << " | " << display_it(sit) << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " begin() test passed" << RESET << std::endl;
	std::cout << "Create ft::map<int, std::string>::reverse_iterator it = rbegin() and compare with real" << std::endl;
	ft::map<int, std::string>::reverse_iterator			rit = l.rbegin();
	std::map<int, std::string>::reverse_iterator		srit = sl.rbegin();
	if (*rit != *srit)
		std::cerr << WRONG << BOLD << RED << " iterators value differents : " << display_it(rit) << " | " << display_it(srit) << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " rbegin() test passed" << RESET << std::endl;
	std::cout << std::endl;
}

static void			end_rend()
{
	print_small_header("-> End() and rend()");
	ft::map<int, std::string>		l;
	std::map<int, std::string>		sl;
	for (int i = 0; i < 15; ++i)
	{
		std::string wrd = bank_word[rand() % 29];
		l[i] = wrd;
		sl[i] = wrd;
	}
	std::cout << "Create ft::map<int, std::string>::iterator it = end() and compare with real" << std::endl;
	ft::map<int, std::string>::iterator			it = l.end();
	std::map<int, std::string>::iterator		sit = sl.end();
	if (*it != *sit)
		std::cerr << WARNING << BOLD << YELLOW << " undefine behavior, dereferencing end() : " << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " end() test passed" << RESET << std::endl;
	std::cout << "Create ft::map<int, std::string>::reverse_iterator it = --rend() and compare with real" << std::endl;
	std::cout << "if using rend() without -- , cannot compare values        ^" << std::endl;
	ft::map<int, std::string>::reverse_iterator			rit = --l.rend();
	std::map<int, std::string>::reverse_iterator		srit = --sl.rend();
	if (*rit != *srit)
		std::cerr << WARNING << BOLD << YELLOW << " undefine behavior, dereferencing rend() : " << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " rend() test passed" << RESET << std::endl;
	std::cout << std::endl;
}

static void			capacity_test()
{
	print_small_header("-> Size() and empty()");
	ft::map<int, std::string>		l;
	std::map<int, std::string>		sl;
	if (l.empty() != sl.empty())
		std::cerr << WRONG << BOLD << RED << std::boolalpha << " Empty return error : " << l.empty() << " | " << sl.empty() << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " empty() test passed" << RESET << std::endl;
	for (int i = 0; i < 15; ++i)
	{
		std::string wrd = bank_word[rand() % 29];
		l[i] = wrd;
		sl[i] = wrd;
	}
	if (l.size() != sl.size())
		std::cerr << WRONG << BOLD << RED << " Different size : " << l.size() << " | " << sl.size() << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " size() test passed" << RESET << std::endl;
	l[63] = "salut";
	sl[63] = "salut";
	if (l.size() != sl.size())
		std::cerr << WRONG << BOLD << RED << " Different size : " << l.size() << " | " << sl.size() << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " size() test passed" << RESET << std::endl;
	if (l.empty() != sl.empty())
		std::cerr << WRONG << BOLD << RED << std::boolalpha << " Empty return error : " << l.empty() << " | " << sl.empty() << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " empty() test passed" << RESET << std::endl;
	std::cout << std::endl;
}

static void			operator_test()
{
	print_small_header("-> operator[]");
	ft::map<int, std::string>		l;
	std::map<int, std::string>		sl;
	for (int i = 0; i < 15; ++i)
	{
		std::string wrd = bank_word[rand() % 29];
		l[i] = wrd;
		sl[i] = wrd;
	}
	compare_with_real("Create a map using operator[]", l, sl);
	for (int i = 0; i < 3; ++i)
	{
		int		index = rand() % 14;
		if (l[index] == sl[index])
			std::cout << VALID << BOLD << GREEN << " l[" << index << "] == sl[" << index << "] : " << l[index] << " " << sl[index]  << RESET << std::endl;
		else
			std::cerr << WRONG << BOLD << RED << "Values are different" << RESET << std::endl;
	}
	std::cout << std::endl;
}

static void			insert_test1()
{
	print_small_header("-> insert() part 1");
	typedef std::pair<int, std::string>				value_type;
	typedef ft::map<int, std::string>::iterator		iterator;
	typedef std::map<int, std::string>::iterator	siterator;

	ft::map<int, std::string>		l;
	std::map<int, std::string>		sl;

	for (int i = 0; i < 15; ++i)
	{
		std::string wrd = bank_word[rand() % 29];
		int			index = rand() % 50;
		l[index] = wrd;
		sl[index] = wrd;
	}
	for (int i = 0; i < 3; ++i)
	{
		int index = rand() % 50;
		std::string word = bank_word[rand() % 29];
		std::pair<iterator, bool>		ret = l.insert(value_type(index, word));
		std::pair<siterator, bool>		sret = sl.insert(value_type(index, word));;
		if (ret.second)
			compare_with_real("test inserting new value", l, sl);
		else
		{
			std::cout << "value already exist and hasn't been added : checking iterator values :" << std::endl;
			if (*ret.first != *sret.first)
				std::cerr << WRONG << BOLD << RED << " iterators value differents : " << display_it(ret.first) << " | " << display_it(sret.first) << RESET << std::endl;
			else
				std::cout << VALID << BOLD << GREEN << " test passed" << RESET << std::endl;
			std::cout << std::endl;
		}
	}
	std::cout << std::endl;
}

static void			insert_test2()
{
	print_small_header("-> insert() part 2");
	typedef std::pair<int, std::string>				value_type;
	typedef ft::map<int, std::string>::iterator		iterator;
	typedef std::map<int, std::string>::iterator	siterator;

	ft::map<int, std::string>		l;
	std::map<int, std::string>		sl;

	std::vector<value_type>			base;
	for (int i = 0; i < 5; ++i)
	{
		int			index = rand() % 50;
		std::string wrd = bank_word[rand() % 29];
		base.push_back(value_type(index, wrd));
	}
	for (int i = 0; i < 15; ++i)
	{
		std::string wrd = bank_word[rand() % 29];
		int			index = rand() % 50;
		l[index] = wrd;
		sl[index] = wrd;
	}
	for (int i = 0; i < 3; ++i)
	{
		int index = rand() % 50;
		std::string word = bank_word[rand() % 29];
		iterator		ret = l.insert(l.begin(), value_type(index, word));
		siterator		sret = sl.insert(sl.begin(), value_type(index, word));
		if (*ret != *sret)
			std::cerr << WRONG << BOLD << RED << " iterators value differents : " << display_it(ret) << " | " << display_it(sret) << RESET << std::endl;
		compare_with_real("adding new values with l.begin()", l, sl);
	}
	l.insert(base.begin(), base.end());
	sl.insert(base.begin(), base.end());
	compare_with_real("adding new values from a vector of value_type", l, sl);
	std::cout << std::endl;
}

static void			erase_test()
{
	print_small_header("-> erase()");
	ft::map<int, std::string>		l;
	std::map<int, std::string>		sl;
	for (int i = 0; i < 15; ++i)
	{
		std::string wrd = bank_word[rand() % 29];
		l[i] = wrd;
		sl[i] = wrd;
	}
	ft::map<int, std::string>::iterator		it = l.begin();
	std::map<int, std::string>::iterator	sit = sl.begin();
	for (int i = 0; i < 3; ++i)
	{
		++it;
		++sit;
	}
	l.erase(it);
	sl.erase(sit);
	compare_with_real("erasing third elem with iterator", l, sl);
	l.erase(10);
	sl.erase(10);
	compare_with_real("erasing key_type 10", l, sl);
	l.erase(++l.begin(), --l.end());
	sl.erase(++sl.begin(), --sl.end());
	compare_with_real("erasing from ++being() to --end()", l, sl);
	std::cout << std::endl;
}

static void			swap_test()
{
	print_small_header("-> swap()");
	ft::map<int, std::string>		l;
	std::map<int, std::string>		sl;
	ft::map<int, std::string>		l2;
	std::map<int, std::string>		sl2;

	for (int i = 0; i < 15; ++i)
	{
		std::string wrd = bank_word[rand() % 29];
		std::string wrd2 = bank_word[rand() % 29];
		int			index = rand() % 50;
		int			index2 = rand() % 50;
		l[index] = wrd;
		sl[index] = wrd;
		l2[index2] = wrd2;
		sl2[index2] = wrd2;
	}
	compare_with_real("compare initial list", l, sl);
	l.swap(l2);
	sl.swap(sl2);
	compare_with_real("compare swapped list", l, sl);
	std::cout << std::endl;
}

static void			clear_test()
{
	print_small_header("-> clear()");
	ft::map<int, std::string>		l;
	std::map<int, std::string>		sl;

	for (int i = 0; i < 15; ++i)
	{
		std::string wrd = bank_word[rand() % 29];
		int			index = rand() % 50;
		l[index] = wrd;
		sl[index] = wrd;
	}
	l.clear();
	sl.clear();
	compare_with_real("compare after clear map", l, sl);
	std::cout << std::endl;
}

static void			operation_test1()
{
	typedef ft::map<int, std::string>::iterator		iterator;
	typedef std::map<int, std::string>::iterator	siterator;

	ft::map<int, std::string>		l;
	std::map<int, std::string>		sl;

	for (int i = 0; i < 15; ++i)
	{
		std::string wrd = bank_word[rand() % 29];
		l[i] = wrd;
		sl[i] = wrd;
	}
	print_small_header("-> find()");
	iterator			it = l.find(12);
	siterator			sit = sl.find(12);
	if (*it != *sit)
		std::cerr << WRONG << BOLD << RED << " iterators value differents : " << display_it(it) << " | " << display_it(sit) << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " find() with correct value test passed" << RESET << std::endl;
	it = l.find(652);
	if (it != l.end())
		std::cerr << WRONG << BOLD << RED << " iterators value differents : " << display_it(it) << " | " << display_it(sit) << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " find() with incorrect value test passed" << RESET << std::endl;
	std::cout << std::endl;

	print_small_header("-> count()");
	size_t		res = l.count(12);
	size_t		sres = sl.count(12);
	if (res!= sres)
		std::cerr << WRONG << BOLD << RED << " return value incorrect : " << res << " | " << sres << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " count() with correct value test passed" << RESET << std::endl;
	res = l.count(154);
	sres = sl.count(154);
	if (res!= sres)
		std::cerr << WRONG << BOLD << RED << " return value incorrect : " << res << " | " << sres << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " count() with incorrect value test passed" << RESET << std::endl;
	std::cout << std::endl;
}

static void			operation_test2()
{
	typedef ft::map<int, std::string>::iterator		iterator;
	typedef std::map<int, std::string>::iterator	siterator;

	ft::map<int, std::string>		l;
	std::map<int, std::string>		sl;

	for (int i = 0; i < 15; ++i)
	{
		std::string wrd = bank_word[rand() % 29];
		int index = rand() % 49;
		l[index] = wrd;
		sl[index] = wrd;
	}
	print_small_header("-> lower_bound()");

	iterator it;
	siterator sit;
	int index = 15;
	for (int i = 1; i < 4; ++i)
	{
		it = l.lower_bound(index);
		sit = sl.lower_bound(index);
		if (it == l.end() && sit == sl.end())
			std::cout << VALID << BOLD << GREEN << " lower_bound() with out of range key test passed" << RESET << std::endl;
		else if (*it != *sit)
			std::cerr << WRONG << BOLD << RED << " iterators value differents : " << display_it(it) << " | " << display_it(sit) << RESET << std::endl;
		else
			std::cout << VALID << BOLD << GREEN << " lower_bound() test passed" << RESET << std::endl;
		index += 22;
	}
	std::cout << std::endl;
	print_small_header("-> upper_bound()");
	index = 15;
	for (int i = 1; i < 4; ++i)
	{
		it = l.upper_bound(index);
		sit = sl.upper_bound(index);
		if (it == l.end() && sit == sl.end())
			std::cout << VALID << BOLD << GREEN << " upper_bound() with out of range key test passed" << RESET << std::endl;
		else if (*it != *sit)
			std::cerr << WRONG << BOLD << RED << " iterators value differents : " << display_it(it) << " | " << display_it(sit) << RESET << std::endl;
		else
			std::cout << VALID << BOLD << GREEN << " upper_bound() test passed" << RESET << std::endl;
		index += 22;
	}
	std::cout << std::endl;
}

void				MapTest()
{
	print_header("Map Tester :\n");
	test_constructor();
	begin_rbegin();
	end_rend();
	capacity_test();
	operator_test();
	insert_test1();
	insert_test2();
	erase_test();
	swap_test();
	clear_test();
	operation_test1();
	operation_test2();
	std::cout << "Press any key to go back to main menu" << std::endl;
	std::cin.get();
}
