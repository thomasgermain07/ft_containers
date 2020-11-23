/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 11:43:56 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/23 17:19:13 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST
# define LIST

# include <iostream>
# include <memory>
# include <iterator>
# include "structs.hpp"
# include "listIterator.hpp"

namespace	ft
{
	template<class T, class Alloc = std::allocator<T> >
	class		list
	{
	public :
					/* *** ************************ *** */
					/* ***		   Typedef 			*** */
					/* *** ************************ *** */
		typedef T 											value_type;
		typedef Alloc										allocator_type;
		typedef	size_t										size_type;
		typedef _node<value_type>*							node;
		typedef typename allocator_type::reference 			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef	ListIterator<value_type>					iterator;
		typedef ConstListIterator<value_type>				const_iterator;
		typedef typename iterator::difference_type			difference_type;


					/* *** ************************ *** */
					/* *** Constructor / Destructor *** */
					/* *** ************************ *** */
		explicit list(const allocator_type &alloc = allocator_type()) : head(NULL), tail(NULL), list_size(0), _allocator(alloc) { _end_node = _create_node(value_type()); }
		explicit list(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : head(NULL), tail(NULL), list_size(n), _allocator(alloc)
		{
			_end_node = _create_node(value_type());
			if (n)
				_first_insert(_create_node(val));
			for (size_t i = 1; i < n; i++)
				_insert_end(_create_node(val));
		}
		template<class InputIterator>
		list(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) : head(NULL), tail(NULL), list_size(0), _allocator(alloc)
		{
			_end_node = _create_node(value_type());
			if (first != last)
				_first_insert(_create_node(*first));
			while (++first != last)
				_insert_end(_create_node(*first));
		}
		~list() { _clean_list(); }

					/* *** ************************ *** */
					/* *** 	   Member Functions		*** */
					/* *** ************************ *** */
		void				push_back(value_type const &_data)
		{
			head ? _insert_end(_create_node(_data)) : _first_insert(_create_node(_data));
			list_size++;
		}
		size_type			size() const { return list_size; }
		iterator			begin() { return iterator(head); } // ATTENTION SEG_FAULT WITH NULL
		const_iterator		begin() const { return const_iterator(head); } // ATTENTION SEG_FAULT WITH NULL
		iterator			end() { return iterator(_end_node); } // ATTENTION SEG_FAULT WITH NULL
		const_iterator		end() const { return const_iterator(_end_node); } // ATTENTION SEG_FAULT WITH NULL


	private :
					/* *** ************************ *** */
					/* *** 		 Variables			*** */
					/* *** ************************ *** */
		node					head;
		node					tail;
		node					_end_node;
		allocator_type			_allocator;
		size_type				list_size;

					/* *** ************************ *** */
					/* *** 	   Private Functions	*** */
					/* *** ************************ *** */
		node			_create_node(value_type const &_data)
		{
			node		n = new _node<value_type>;

			n->data = _allocator.allocate(sizeof(value_type));
			_allocator.construct(n->data, _data);
			n->next = NULL;
			n->prev = NULL;
			return n;
		}
		void			_insert_end(node n)
		{
			n->prev = tail;
			tail->next = n;
			tail = n;
			n->next = _end_node;
			_end_node->prev = tail;
		}
		void			_first_insert(node n)
		{
			head = n;
			tail = n;
			tail->next = _end_node;
			_end_node->next = head;
			head->prev = _end_node;
		}
		void			_clean_list() // A revoir je suis pas fan du if !list_size
		{
			node	current = head;

			if (!list_size)
			{
				_allocator.destroy(_end_node->data);
				_allocator.deallocate(_end_node->data, sizeof(value_type));
				delete _end_node;
				return ;
			}
			while (list_size + 1 > 0)
			{
				node next = current->next;
				_allocator.destroy(current->data);
				_allocator.deallocate(current->data, sizeof(value_type));
				delete current;
				current = next;
				list_size--;
			}
		}
	};
};

#endif