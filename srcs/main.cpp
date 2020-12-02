/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 08:49:25 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/01 14:49:37 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "test_header.hpp"

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

int			main()
{
	srand(time(NULL));


	ListTest();

	std::cout << std::endl;

	std::cout << "Print leaks" << std::endl;
	std::cin.get();
	system("leaks a.out");

	return 0;
}
