/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 14:36:00 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/15 15:12:51 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK
# define STACK

# include <iostream>
# include "list.hpp"
# include "vector.hpp"

namespace		ft
{
	template<class T, class Container = ft::list<T> >
	class stack
	{
	public :
		typedef T				value_type;
		typedef Container		container_type;
		typedef	size_t			size_type;

		explicit stack (const container_type& ctnr = container_type()) : _cont(ctnr) {}

		bool				empty() const { return _cont.empty(); }
		size_type			size() const { return _cont.size(); }

		value_type&			top() { return _cont.back(); }
		const value_type&	top() const { return _cont.back(); }

		void				push(const value_type& val) { _cont.push_back(val); }
		void				pop() { _cont.pop_back(); }

	private :
		container_type		_cont;

		template<class X, class Y>
		friend bool		operator==(const stack<X, Y>& lhs, const stack<X, Y>& rhs);
		template<class X, class Y>
		friend bool		operator<(const stack<X, Y>& lhs, const stack<X, Y>& rhs);
	};
	template<class T, class Container>
	bool			operator==(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs._cont == rhs._cont; }
	template<class T, class Container>
	bool			operator<(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return lhs._cont < rhs._cont; }
	template<class T, class Container>
	bool			operator!=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return !(lhs == rhs); }
	template<class T, class Container>
	bool			operator>(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return rhs < lhs; }
	template<class T, class Container>
	bool			operator>=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return !(lhs < rhs); }
	template<class T, class Container>
	bool			operator<=(const stack<T, Container>& lhs, const stack<T, Container>& rhs) { return !(rhs < lhs); }
};

#endif