/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 15:17:36 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/15 15:49:10 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE
# define QUEUE

# include <iostream>
# include "list.hpp"

namespace		ft
{
	template<class T, class Container = ft::list<T> >
	class queue
	{
	public :
		typedef	T				value_type;
		typedef Container		container_type;
		typedef size_t			size_type;

		explicit			queue(const container_type& cntr = container_type()) : _cont(cntr) {}

		bool				empty() const { return _cont.empty(); }
		size_type			size() const { return _cont.size(); }

		value_type&			front() { return _cont.front(); }
		const value_type&	front() const { return _cont.front(); }

		value_type&			back() { return _cont.back(); }
		const value_type&	back() const { return _cont.back(); }

		void				push(const value_type& val) { _cont.push_back(val); }
		void				pop() { _cont.pop_front(); }

	private :
		container_type		_cont;

		template<class X, class Y>
		friend bool		operator==(const queue<X, Y>& lhs, const queue<X, Y>& rhs);
		template<class X, class Y>
		friend bool		operator<(const queue<X, Y>& lhs, const queue<X, Y>& rhs);
	};

	template<class T, class Container>
	bool			operator==(const queue<T, Container>& lhs, const queue<T, Container>& rhs) { return lhs._cont == rhs._cont; }
	template<class T, class Container>
	bool			operator<(const queue<T, Container>& lhs, const queue<T, Container>& rhs) { return lhs._cont < rhs._cont; }
	template<class T, class Container>
	bool			operator!=(const queue<T, Container>& lhs, const queue<T, Container>& rhs) { return !(lhs == rhs); }
	template<class T, class Container>
	bool			operator>(const queue<T, Container>& lhs, const queue<T, Container>& rhs) { return rhs < lhs; }
	template<class T, class Container>
	bool			operator>=(const queue<T, Container>& lhs, const queue<T, Container>& rhs) { return !(lhs < rhs); }
	template<class T, class Container>
	bool			operator<=(const queue<T, Container>& lhs, const queue<T, Container>& rhs) { return !(rhs < lhs); }
};

#endif