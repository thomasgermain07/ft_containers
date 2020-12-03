/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 11:43:56 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/03 16:01:56 by thgermai         ###   ########.fr       */
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
		typedef ReverseListIterator<value_type>				reverse_iterator;
		typedef ConstReverseListIterator<value_type>		const_reverse_iterator;
		typedef typename iterator::difference_type			difference_type;

					/* *** ************************ *** */
					/* *** Constructor / Destructor *** */
					/* *** ************************ *** */
		explicit list(const allocator_type &alloc = allocator_type()) :
			head(_create_node(value_type())), tail(head), list_size(0), _allocator(alloc)  { _link_node(head, tail, tail); }
		explicit list(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) :
			head(_create_node(value_type())), tail(head), list_size(0), _allocator(alloc)
		{
			 _link_node(head, tail, tail);
			while (n-- > 0)
				push_back(val);
		}
		template<class InputIterator>
		list(InputIterator first, InputIterator last, const allocator_type &alloc = allocator_type()) :
			head(_create_node(value_type())), tail(head), list_size(0), _allocator(alloc) { _copy_range(first, last); }
		list(const list& x) : head(_create_node(value_type())), tail(head), list_size(0), _allocator(allocator_type()) {  _link_node(head, tail, tail); *this = x; }
		list				&operator=(list const &ref)
		{
			if (!ref.size())
				return *this;
			_clear_list();
			_copy_range(ref.begin(), ref.end());
			return *this;
		}
		~list() { _clear_list(), _delete_node(head); }

					/* *** ************************ *** */
					/* *** 	   Member Functions		*** */
					/* *** ************************ *** */
		iterator				begin() { return iterator(head->next); }
		const_iterator			begin() const { return const_iterator(head->next); }
		iterator				end() { return iterator(head); }
		const_iterator			end() const { return const_iterator(head); }

		reverse_iterator		rbegin() { return reverse_iterator(iterator(head)); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(const_iterator(head)); }
		reverse_iterator		rend() { return reverse_iterator(iterator(head->next)); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(const_iterator(head->next)); }

		bool					empty() const { return list_size == 0; }
		size_type				size() const { return list_size; }
		size_type				max_size() const { return std::numeric_limits<size_type>::max() / sizeof(node); }

		reference				front() { return *head->next->data; }
		const_reference			front() const { return *head->next->data; }
		reference				back() { return *tail->data; }
		const_reference			back() const { return *tail->data; }

		void					assign(size_type n, const value_type &val)
		{
			_clear_list();
			while (n-- > 0)
				push_back(val);
		}
		template<class InputIterator>
		void					assign(InputIterator first, InputIterator last)
		{
			_clear_list();
			_copy_range(first, last);
		}
		void					push_back(value_type const &_value)
		{
			list_size ? _insert_end(_create_node(_value, tail, head)) : _first_insert(_create_node(_value, head, head));
			++list_size;
		}
		void					pop_back()
		{
			if (empty())
				return ;
			_unlink_node(tail);
			_delete_node(tail);
			tail = head->prev;
			--list_size;
		}
		void					push_front(value_type const &_value)
		{
			list_size ? _insert_begin(_create_node(_value, head, head->next)) : _first_insert(_create_node(_value, head, head));
			++list_size;
		}
		void					pop_front()
		{
			if (empty())
				return ;
			node		_tmp = head->next;
			_unlink_node(head->next);
			_delete_node(_tmp);
			--list_size;
		}
		iterator				insert(iterator position, const value_type& val)
		{
			node			n = _create_node(val);
			if (position == begin())
				empty() ? _first_insert(_link_node(n, head, head)) : _insert_begin(_link_node(n, head, head->next));
			else if (position == end())
				empty() ? _first_insert(_link_node(n, head, head)) : _insert_end(_link_node(n, tail, head));
			else
				_insert_before(n, position);
			++list_size;
			return iterator(n);
		}
		void					insert(iterator position, size_type n, const value_type& val)
		{
			while (n--)
				position = insert(position, val);
		}
		template<typename InputIterator>
		void					insert(iterator position, InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert(position, *first);
				++first;
			}
		}
		iterator				erase(iterator position)
		{
			iterator		_ret = position;
			++_ret;
			if (position == begin())
				pop_front();
			else if (position == end())
				pop_back();
			else
				_delete_pos(position);
			return _ret;
		}
		iterator				erase(iterator first, iterator last)
		{
			while (first != last)
				first = erase(first);
			return last;
		}
		void					resize(size_type n, value_type val = value_type())
		{
			int		_n = n - size();
			if (_n > 0)
				insert(end(), static_cast<size_type>(_n), val);
			else if (_n < 0)
				while (_n++)
					pop_back();
		}
		void					clear() { _clear_list(); }
		void					swap(list& c)
		{
			ft::_swap(head, c.head);
			ft::_swap(tail, c.tail);
			ft::_swap(list_size, c.list_size);
		}
		void					splice(iterator position, list& x) { splice(position, x, x.begin(), x.end()); }
		void					splice(iterator position, list& x, iterator i)
		{
			if (i == x.end())
				return ;
			splice(position, x, i, ++i);
		}
		void					splice(iterator position, list& x, iterator first, iterator last)
		{
			node			_first_n = x._find_node(first);
			node			_last_n = x._find_node(last)->prev;

			if (!_first_n || !_last_n)
				return ;
			size_type		dist = _distance_node(_first_n, _last_n) + 1;
			_unlink_range(_first_n, _last_n);
			_insert_range(_first_n, _last_n, position);
			list_size += dist;
			x.list_size -= dist;
		}
		void					remove(const value_type& val)
		{
			for (iterator it = begin(); it != end(); ++it)
				if (*it == val)
					erase(it);
		}
		template<class Predicate>
		void					remove_if(Predicate pred)
		{
			for (iterator it = begin(); it != end(); ++it)
				if (pred(*it))
					erase(it);
		}
		void					unique()
		{
			for (iterator it = begin(); it != end(); ++it)
			{
				iterator		next = it;
				while (*++next == *it)
					erase(next);
			}
		}
		template<class BinaryPredicate>
		void					unique(BinaryPredicate binary_pred)
		{
			iterator			prev = begin();
			iterator			current = prev;
			while (++current != end())
			{
				if (binary_pred(*prev, *current))
				{
					erase(current);
					current = prev;
				}
				else
					prev = current;
			}
		}
		void					sort()
		{
			node			curr = head->next;
			while (curr->next != head)
			{
				node		next = curr->next;
				if (*next->data < *curr->data)
				{
					_swap_node(next, curr);
					curr = head;
				}
				curr = curr->next;
			}
		}
		template<class Compare>
		void					sort(Compare comp)
		{
			node 			curr = head->next;
			while (curr->next != head)
			{
				node		next = curr->next;
				if (comp(*next->data, *curr->data))
				{
					_swap_node(curr, next);
					curr = head;
				}
				curr = curr->next;
			}
		}
		void					merge(list& x)
		{
			merge(x, basic_comp<value_type>);
		}
		template<class Compare>
		void					merge(list& x, Compare comp)
		{
			iterator			it;
			iterator			xit = x.begin();
			if (&x == this)
				return ;
			for (it = begin(); it != end(); ++it)
			{
				xit = x.begin();
				while (xit != x.end() && comp(*xit, *it))
				{
					_transfer_node(x._find_node(xit), it);
					xit = x.begin();
				}
			}
			while (xit != x.end())
			{
				_transfer_node(x._find_node(xit), it);
				xit = x.begin();
			}
			list_size += x.size();
			x.list_size = 0;
		}
		void					reverse()
		{
			node			start = head->next;
			node			end = head->prev;
			for (int i = 0; i < list_size / 2; ++i)
			{
				_swap_node(start, end);
				start = start->next;
				end = end->prev;
			}
		}
	private :
		node					head;
		node					tail;
		allocator_type			_allocator;
		size_type				list_size;

		node					_create_node(value_type const &_value, node _prev = NULL, node _next = NULL)
		{
			node		n = new _node<value_type>;
			n->data = _allocator.allocate(sizeof(value_type));
			_allocator.construct(n->data, _value);
			n->next = _next;
			n->prev = _prev;
			return n;
		}
		void					_insert_begin(node n)
		{
			head->next->prev = n;
			head->next = n;
		}
		void					_insert_end(node n)
		{
			tail->next = n;
			head->prev = n;
			tail = n;
		}
		void					_insert_before(node n, iterator position)
		{
			node		_tmp = _find_node(position);
			if (!_tmp)
				return ;
			_link_node(n, _tmp->prev, _tmp);
			_tmp->prev->next = n;
			_tmp->prev = n;
		}
		void					_insert_range(node begin, node end, iterator position)
		{
			node			_tmp = _find_node(position);
			if (!_tmp)
				return ;
			_link_node(_tmp->prev, _tmp->prev->prev, begin);
			_link_node(begin, _tmp->prev, begin->next);
			_link_node(end, end->prev, _tmp);
			_link_node(_tmp, end, _tmp->next);
		}
		void					_first_insert(node n)
		{
			head->next = n;
			head->prev = n;
			tail = n;
		}
		void					_clear_list()
		{
			node	current = head->next;
			if (empty())
				return ;
			while (current != head)
			{
				node next = current->next;
				_delete_node(current);
				current = next;
			}
			list_size = 0;
			_first_insert(head);
		}
		node					_link_node(node n, node _prev, node _next)
		{
			n->prev = _prev;
			n->next = _next;
			return n;
		}
		void					_unlink_node(node n)
		{
			n->prev->next = n->next;
			n->next->prev = n->prev;
		}
		void					_swap_node(node n1, node n2)
		{
			pointer			_tmp = n1->data;
			n1->data = n2->data;
			n2->data = _tmp;
		}
		void					_transfer_node(node n, iterator position)
		{
			_unlink_node(n);
			_insert_before(n, position);
		}
		void					_unlink_range(node start, node end)
		{
			start->prev->next = end->next;
			end->next->prev = start->prev;
		}
		void					_delete_node(node n)
		{
			_allocator.destroy(n->data);
			_allocator.deallocate(n->data, sizeof(value_type));
			delete n;
		}
		node					_find_node(iterator it)
		{
			node				n = head->next;
			while (n != head)
			{
				if (iterator(n) == it)
					return n;
				n = n->next;
			}
			if (iterator(n) == it)
				return n;
			return NULL;
		}
		size_type				_distance_node(node begin, node end)
		{
			size_type		dist = 0;
			if (begin == end)
				return dist;
			while (begin != end)
			{
				++dist;
				begin = begin->next;
			}
			return dist;
		}
		template<class InputIterator>
		void					_copy_range(InputIterator first, InputIterator last)
		{
			while (first != last)
				push_back(*first++);
		}
		void					_delete_pos(iterator position)
		{
			node			n = _find_node(position);
			if (!n)
				return ;
			_unlink_node(n);
			_delete_node(n);
			--list_size;
		}
	};

	template<class T, class Alloc>
	bool				operator==(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		typename ft::list<T, Alloc>::const_iterator		lit = lhs.begin();
		typename ft::list<T, Alloc>::const_iterator		rit = rhs.begin();
		while (lit != lhs.end())
		{
			if (*lit++ != *rit++)
				return false;
		}
		return true;
	}
	template<class T, class Alloc>
	bool				operator<(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return lhs.size() < rhs.size();
		typename ft::list<T, Alloc>::const_iterator		lit = lhs.begin();
		typename ft::list<T, Alloc>::const_iterator		rit = rhs.begin();
		while (lit != lhs.end())
		{
			if (*lit != *rit)
				return *lit < *rit;
			++lit;
			++rit;
		}
		return false;
	}
	template<class T, class Alloc>
	bool				operator!=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		return !(lhs == rhs);
	}
	template<class T, class Alloc>
	bool				operator>(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		return rhs < lhs;
	}
	template<class T, class Alloc>
	bool				operator>=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}
	template<class T, class Alloc>
	bool				operator<=(const list<T, Alloc>& lhs, const list<T, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}
	template<class T, class Alloc>
	void				swap(list<T, Alloc>& x, list<T, Alloc>& y)
	{
		x.swap(y);
	}
};

#endif