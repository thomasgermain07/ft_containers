/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 14:29:00 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/22 14:29:22 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS
# define STRUCTS

# include <iostream>

namespace	ft
{
	template<class T>
	struct 			_node
	{
		T				*data;
		_node			*next;
		_node			*prev;
	};
}

#endif