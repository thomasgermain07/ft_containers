/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listIterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 12:08:50 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/23 17:23:35 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTITERATOR
# define LISTITERATOR

# include "structs.hpp"
# include <cstddef>

namespace	ft
{
	template<typename T>
	class	ConstListIterator;

	template<typename T>
	class	ListIterator
	{
	public :
		typedef T								value_type;
		typedef value_type*						pointer_type;
		typedef value_type&						reference_type;
		typedef _node<value_type>*				node;
		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef std::ptrdiff_t					difference_type;

		ListIterator() {}
		ListIterator(ListIterator const &ref) {*this = ref;}
		ListIterator(node _ptr) : ptr(_ptr) {}
		~ListIterator() {}

		operator ConstListIterator<T>() const { return ConstListIterator<T>(ptr); }

		ListIterator			&operator=(ListIterator const &ref) { ptr = ref.ptr; return *this; }
		pointer_type			operator->() const { return ptr->data; }
		reference_type			operator*() const { return *ptr->data; }
		bool					operator==(ListIterator const &ref) const { return ptr->data == ref.ptr->data; }
		bool					operator!=(ListIterator const &ref) const { return !(*this == ref); }
		ListIterator			&operator++() { ptr = ptr->next; return *this; }
		ListIterator			&operator--() { ptr = ptr->prev; return *this; }
		ListIterator			operator++(int) { ListIterator	tmp(*this); ++(*this); return tmp; }
		ListIterator			operator--(int) { ListIterator	tmp(*this); --(*this); return tmp; }

	protected :
		node		ptr;
	};

	template<typename T>
	class	ConstListIterator
	{
	public :
		typedef T								value_type;
		typedef const value_type&				reference_type;
		typedef const value_type*				pointer_type;
		typedef _node<value_type>*				node;
		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef std::ptrdiff_t					difference_type;

		ConstListIterator() {}
		ConstListIterator(node _ptr) : ptr(_ptr) {}
		ConstListIterator(ConstListIterator const &ref) : ptr(ref.ptr) {}
		~ConstListIterator() {} ;

		ConstListIterator		&operator=(ConstListIterator const &ref) { ptr = ref.ptr; return *this;}
		pointer_type			operator->() const { return ptr->data; }
		reference_type			operator*() const { return *ptr->data; }
		bool					operator==(ConstListIterator const &ref) const { return ptr->data == ref.ptr->data; }
		bool					operator!=(ConstListIterator const &ref) const { return !(*this == ref); }
		ConstListIterator		&operator++() { ptr = ptr->next; return *this; }
		ConstListIterator		&operator--() { ptr = ptr->prev; return *this; }
		ConstListIterator		operator++(int) { ConstListIterator	tmp(*this); ptr = ptr->next; return tmp; }
		ConstListIterator		operator--(int) { ConstListIterator	tmp(*this); ptr = ptr->prev; return tmp; }

	protected :
			node	ptr;
	};
};

#endif