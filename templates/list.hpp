/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 09:03:08 by thgermai          #+#    #+#             */
/*   Updated: 2020/11/21 16:54:48 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST
# define LIST

# include <iostream>
# include <memory>

namespace		ft
{
	template<class T, class Alloc = std::allocator<T> >
	class		list;
}

template<class T, class Alloc>
class		listIterator
{
	public:
		/* *** ************************ *** */
		/* *** ******* Type_def ******* *** */
		/* *** ************************ *** */

		typedef	T										value_type;
		typedef ft::list<T, Alloc>						__list_access;
		typedef typename __list_access::node_type		node;
		typedef	node*									node_ptr;
		typedef value_type*								pointer_type;
		typedef value_type&								reference_type;

		/* *** ************************ *** */
		/* *** Constructor / Destructor *** */
		/* *** ************************ *** */
		listIterator() { }
		listIterator(node_ptr _ptr) : ptr(_ptr) { }
		listIterator<value_type, Alloc>		&operator=(listIterator<value_type, Alloc> const &ref)
		{
			this->ptr = ref.ptr;
			return *this;
		}

		pointer_type		operator->() const
		{
			return this->ptr->data;
		}

		reference_type		operator*() const
		{
			return *this->ptr->data;
		}

	private :
		node_ptr		ptr;

};

template<class T, class Alloc>
class		ft::list
{
	public:
		/* *** ************************ *** */
		/* *** ******* Type_def ******* *** */
		/* *** ************************ *** */

		struct node;

		typedef node										node_type;

		typedef T 											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference 			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

		typedef listIterator<value_type, allocator_type>	iterator;

		/* *** ************************ *** */
		/* *** Constructor / Destructor *** */
		/* *** ************************ *** */

		list()
		{
			this->head = NULL;
			this->tail = NULL;
			this->size = 0;
		}

		~list()
		{
			node			*current = this->head;
			node			*next;
			// allocator_type		allocator;

			if (!current)
				return ;
			while (current)
			{
				next = current->next;
				// allocator.destroy(current->data);
				// allocator.deallocate(current->data, );
				delete current->data; // change With alloc when finish iterators
				delete current;
				current = next;
			}
		}

		/* *** ************************ *** */
		/* *** 		  Modifiers			*** */
		/* *** ************************ *** */

		void			push_back(value_type _data)
		{
			node		*n = new node(_data);

			if (!this->head)
			{
				this->head = n;
				this->tail = n;
				this->size += 1;
				return ;
			}
			this->tail->next = n;
			this->tail = n;
			this->size += 1;
		}

		iterator			begin() const
		{
			return iterator(head);
		}

		/* *** Doubly Linked List structure *** */
		struct 			node
		{
			node(value_type _data)
			{
				allocator_type		allocator;

				this->data = allocator.allocate(1);
				allocator.construct(this->data, _data);
				this->prev = NULL;
				this->next = NULL;
			}

			value_type		*data;
			node			*prev;
			node			*next;
		};

	private :
		node			*head;
		node			*tail;
		size_t			size;
};
#endif