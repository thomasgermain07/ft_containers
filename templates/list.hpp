/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 11:43:56 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/24 11:20:51 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST
# define LIST

# include <iostream>
# include <memory>
# include <iterator>
# include <limits>
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
		explicit list(const allocator_type &alloc = allocator_type()) :
			head(_create_node(value_type())), tail(head), list_size(0), _allocator(alloc) {}
		explicit list(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) :
			head(_create_node(value_type())), tail(head), list_size(0), _allocator(alloc)
		{
			while (n-- > 0)
				push_back(val);
		}
		template<class InputIterator>
		list(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) :
			head(_create_node(value_type())), tail(head), list_size(0), _allocator(alloc) { _copy_range(first, last); }
		list(const list& x) : head(_create_node(value_type())), list_size(0), _allocator(allocator_type()) { *this = x; }
		list				&operator=(list const &ref)
		{
			_clear_list();
			_copy_range(ref.begin(), ref.end());
			return *this;
		}
		~list() { _clear_list(), _delete_node(head); }

					/* *** ************************ *** */
					/* *** 	   Member Functions		*** */
					/* *** ************************ *** */
		void				push_back(value_type const &_data)
		{
			head->next ? _insert_end(_create_node(_data, tail, head)) : _first_insert(_create_node(_data, head, head));
			list_size++;
		}
		iterator			begin() { return iterator(head->next); }
		//					rbegin(); Reverse Iterator need to be implemented
		const_iterator		begin() const { return const_iterator(head->next); }
		iterator			end() { return iterator(tail->next); }
		const_iterator		end() const { return const_iterator(tail->next); }
		//					rend(); Reverse Iterator need to be implemented

		bool				empty() const { return list_size == 0; }
		size_type			size() const { return list_size; }
		size_type			max_size() const { return std::numeric_limits<size_type>::max() / sizeof(node); }

		reference			front() { return *head->next->data; }
		const_reference		front() const { return *head->next->data; }
		reference			back() { return *tail->data; }
		const_reference		back() const { return *tail->data; }

		void				assign(size_type n, const value_type &val)
		{
			_clear_list();
			while (n-- > 0)
				push_back(val);
		}
		template<class InputIterator>
		void				assign(InputIterator first, InputIterator last)
		{
			_clear_list();
			_copy_range(first, last);
		}

	private :
					/* *** ************************ *** */
					/* *** 		 Variables			*** */
					/* *** ************************ *** */
		node					head;
		node					tail;
		allocator_type			_allocator;
		size_type				list_size;

					/* *** ************************ *** */
					/* *** 	   Private Functions	*** */
					/* *** ************************ *** */
		node			_create_node(value_type const &_data, node _prev = NULL, node _next = NULL)
		{
			node		n = new _node<value_type>;
			n->data = _allocator.allocate(sizeof(value_type));
			_allocator.construct(n->data, _data);
			n->next = _next;
			n->prev = _prev;
			return n;
		}
		void			_insert_end(node n)
		{
			tail->next = n;
			head->prev = n;
			tail = n;
		}
		void			_first_insert(node n)
		{
			head->next = n;
			head->prev = n;
			tail = n;
		}
		void			_clear_list()
		{
			node	current = head->next;
			if (!list_size)
				return ;
			while (current != head)
			{
				node next = current->next;
				_delete_node(current);
				current = next;
			}
			list_size = 0;
		}
		void			_delete_node(node n)
		{
			_allocator.destroy(n->data);
			_allocator.deallocate(n->data, sizeof(value_type));
			delete n;
		}
		template<class InputIterator>
		void			_copy_range(InputIterator first, InputIterator last)
		{
			while (first != last)
				push_back(*first++);
		}
	};
};

#endif