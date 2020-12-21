/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QueueTest.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 15:53:40 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/21 02:05:48 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_header.hpp"
#include "../templates/queue.hpp"
#include <queue>

static void		empty_test()
{
	print_small_header("-> Empty()");

	ft::queue<int>			q;
	std::queue<int>			rq;
	bool					error = false;

	if (q.empty() != rq.empty())
		error = true;
	q.push(15);
	rq.push(15);
	if (q.empty() != rq.empty())
		error = true;
	q.pop();
	rq.pop();
	if (q.empty() != rq.empty())
		error = true;
	if (error)
		std::cerr << WRONG << RED << BOLD << "Empty() test failed" << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " Empty() test passed" << RESET << std::endl;
	std::cout << std::endl;
}

static void		size_test()
{
	print_small_header("-> Size()");

	ft::queue<int>			q;
	std::queue<int>			rq;
	bool					error = false;

	if (q.size() != rq.size())
		error = true;
	for (int i = 0; i < 12; ++i)
	{
		q.push(42);
		rq.push(42);
	}
	if (q.size() != rq.size())
		error = true;
	for (int i = 0; i < 3; ++i)
	{
		q.pop();
		rq.pop();
	}
	if (q.size() != rq.size())
		error = true;
	if (error)
		std::cerr << WRONG << RED << BOLD << "Size() test failed" << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " Size() test passed" << RESET << std::endl;
	std::cout << std::endl;
}

static void		back_test()
{
	print_small_header("-> Back() Front()");

	ft::queue<int>			q;
	std::queue<int>			rq;
	bool					error = false;

	for (int i = 0; i < 10; ++i)
	{
		int rdm = rand() % 50;
		q.push(rdm);
		rq.push(rdm);
	}
	while (!q.empty())
	{
		if (q.back() != rq.back())
			error = true;
		if (q.front() != rq.front())
			error = true;
		q.pop();
		rq.pop();
	}
	if (error)
		std::cerr << WRONG << RED << BOLD << "Back() Front() test failed" << RESET << std::endl;
	else
		std::cout << VALID << BOLD << GREEN << " Back() Front() test passed" << RESET << std::endl;
	std::cout << std::endl;
}

void			QueueTest()
{
	print_header("Queue Tester :\n");
	empty_test();
	size_test();
	back_test();
	std::cout << "Press any key to go back to main menu" << std::endl;
	std::cin.get();
}
