/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listIterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 12:08:50 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/22 15:58:09 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTITERATOR
# define LISTITERATOR

# include "structs.hpp"

namespace	ft
{
	template<typename T>
	class	listIterator
	{
	public :
		typedef T						value_type;
		typedef value_type*				pointer_type;
		typedef value_type&				reference_type;
		typedef _node<T>*				node;

		listIterator() {}
		listIterator(listIterator const &ref) {*this = ref;}
		listIterator(node _ptr) : ptr(_ptr) {}
		~listIterator() {}

					/* *** ************************ *** */
					/* *** 		  Operators 		*** */
					/* *** ************************ *** */
		listIterator		&operator=(listIterator const &ref)
		{
			ptr = ref.ptr;
			return *this;
		}
		pointer_type		operator->() const { return ptr->data; }
		reference_type		operator*() const { return *ptr->data; }
		bool				operator==(listIterator const &ref) const { return ptr->data == ref.ptr->data; }
		bool				operator!=(listIterator const &ref) const { return !(*this == ref); }
		listIterator		&operator++() { ptr = ptr->next; return *this; }
		listIterator		&operator--() { ptr = ptr->prev; return *this; }
		listIterator		operator++(int)
		{
			listIterator	tmp(*this);
			ptr = ptr->next;
			return tmp;
		}
		listIterator		operator--(int)
		{
			listIterator	tmp(*this);
			ptr = ptr->prev;
			return tmp;
		}
	private :
		node		ptr;
	};

	template<typename T>
	class	listIterator<const T>
	{
	public :
		typedef const T					value_type;
		typedef value_type *	const_pointer_type;
		typedef value_type &	const_reference_type;
		typedef _node<T>*			node;

		listIterator() { std::cout << "const constructor" << std::endl;}
		listIterator(listIterator<const T> const &ref) {std::cout << "const constructor" << std::endl; *this = ref; }
		listIterator(listIterator<T> const &ref) {std::cout << "constructor" << std::endl; *this = ref; }
		listIterator(node _ptr) : ptr(_ptr) {}
		~listIterator() {}

					/* *** ************************ *** */
					/* *** 		  Operators 		*** */
					/* *** ************************ *** */
		listIterator		&operator=(listIterator const &ref)
		{
			ptr = ref.ptr;
			return *this;
		}
		const_pointer_type 		operator->() const { return ptr->data; }
		const_reference_type 	operator*() const { return *ptr->data; }
		bool					operator==(listIterator const &ref) const { return ptr->data == ref.ptr->data; }
		bool					operator!=(listIterator const &ref) const { return !(*this == ref); }
		listIterator		&operator++() { ptr = ptr->next; return *this; }
		listIterator		&operator--() { ptr = ptr->prev; return *this; }
		listIterator		operator++(int)
		{
			listIterator	tmp(*this);
			ptr = ptr->next;
			return tmp;
		}
		listIterator		operator--(int)
		{
			listIterator	tmp(*this);
			ptr = ptr->prev;
			return tmp;
		}
	private :
		node		ptr;
	};
};

#endif