/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_header.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 21:37:41 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/17 19:13:48 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_HEADER
# define TEST_HEADER

# include <iostream>

# define RESET "\e[0m"
# define BOLD "\e[1m"
# define UNDERLINE "\e[4m"
# define RED "\e[91m"
# define GREEN "\e[92m"
# define YELLOW "\e[93m"
# define BLUE "\e[34m"
# define VALID "✅"
# define WARNING "⚠️ "
# define WRONG "❌"

template<class T>
void		rprint(T const &cont)
{
	typename T::const_reverse_iterator 		it;
	for (it = cont.rbegin(); it != cont.rend(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "cont size : " << RESET << cont.size() << std::endl;
}

template<class T>
void		print(T const &cont)
{
	typename T::const_iterator 		it;
	for (it = cont.begin(); it != cont.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
	std::cout << "cont size : " << RESET << cont.size() << std::endl;
}

template<class T>
void		print_map(T const &cont)
{
	typename T::const_iterator 		it;
	for (it = cont.begin(); it != cont.end(); ++it)
		std::cout << it->first << " " << it->second << std::endl;
	std::cout << "cont size : " << RESET << cont.size() << std::endl;
}

void					print_header(std::string msg);
void					print_small_header(std::string msg);
void					print_msg(std::string msg);
void					ListTest();
void					VectorTest();
void					QueueTest();
void					StackTest();
void					MapTest();

#endif