/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 11:43:56 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/23 11:23:36 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST
# define LIST

# include <iostream>
# include <memory>
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
		typedef T 												value_type;
		typedef Alloc											allocator_type;
		typedef _node<value_type>*								node;
		typedef typename allocator_type::reference 				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef	ListIterator<value_type>						iterator;
		typedef ConstListIterator<value_type>					const_iterator;

					/* *** ************************ *** */
					/* *** Constructor / Destructor *** */
					/* *** ************************ *** */
		list() : head(NULL), tail(NULL), list_size(0), _null() { _end_node = _create_node(_null); }
		~list() { _clean_list(); }

					/* *** ************************ *** */
					/* *** 	   Member Functions		*** */
					/* *** ************************ *** */
		void				push_back(value_type _data)
		{
			head ? _insert_end(_create_node(_data)) : _first_insert(_create_node(_data));
			list_size++;
		}
		size_t				size() const { return list_size; }

		iterator			begin() { return iterator(head); }
		const_iterator		begin() const { std::cout << "here" << std::endl; return const_iterator(head); }
		iterator			end() { return iterator(_end_node); }
		const_iterator		end() const { return const_iterator(_end_node); }


	private :
					/* *** ************************ *** */
					/* *** 		 Variables			*** */
					/* *** ************************ *** */
		node					head;
		node					tail;
		node					_end_node;			// Voir comment enlever ca
		allocator_type			_allocator;
		size_t					list_size;
		value_type				_null;				// ca doit aussi degager

					/* *** ************************ *** */
					/* *** 	   Private Functions	*** */
					/* *** ************************ *** */
		node			_create_node(value_type _data)
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