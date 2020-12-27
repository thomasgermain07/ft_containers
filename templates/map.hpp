/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:02:19 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/27 02:10:26 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP
# define MAP

# include <iostream>
# include <memory>
# include <functional>
# include <utility>
# include "bst.hpp"
# include "mapIterator.hpp"

namespace	ft
{
	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T> > >
	class map
	{
	public :
		typedef Alloc										allocator_type;
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef std::pair<const key_type, mapped_type>		value_type;
		typedef Compare										key_compare;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ptrdiff_t									difference_type;
		typedef size_t										size_type;

		class	value_compare : public std::binary_function<value_type,value_type,bool>
		{
			friend class map;
		protected :
			value_compare(Compare c) : comp(c) {}
			Compare			comp;
		public :
			typedef bool			result_type;
			typedef value_type		first_argument_type;
			typedef value_type		second_argument_type;
			bool			operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};

		typedef MapIterator<value_type, value_compare, Alloc>				iterator;
		typedef ConstMapIterator<value_type, value_compare, Alloc>			const_iterator;
		typedef	ReverseMapIterator<value_type, value_compare, Alloc>		reverse_iterator;
		typedef	ConstReverseMapIterator<value_type, value_compare, Alloc>	const_reverse_iterator;

		typedef BinarySearchTree<value_type, value_compare, Alloc> 	tree;
		typedef BinaryNode<value_type, Alloc>*						node;

		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _allocator(alloc), _compare(comp), bst(tree(_compare)) {}
		template<class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _allocator(alloc), _compare(comp), bst(tree(_compare)) { insert(first, last); }
		map(const map& x) : _allocator(x._allocator), _compare(x._compare), bst(x.bst) {}
		map					&operator=(const map& x)
		{
			bst = x.bst;
			_compare = x._compare;
			return *this;
		}
		~map() {}

		mapped_type			&operator[] (const key_type& k)
		{
			value_type			val(k, mapped_type());
			node				n = bst.find(val);

			if (!n)
				n = bst.add_node(val).first;
			return n->data->second;
		}
					/* *** ************************ *** */
					/* *** 	   Member Functions		*** */
					/* *** ************************ *** */

		iterator			begin() { return iterator(bst.min(), &bst); }
		const_iterator		begin() const { return const_iterator(bst.min(), &bst); }
		iterator			end() { return iterator(bst.get_end_node(), &bst); }
		const_iterator		end() const { return const_iterator(bst.get_end_node(), &bst); }

		reverse_iterator		rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator	rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator		rend() { return reverse_iterator(begin()); }
		const_reverse_iterator	rend() const { return const_reverse_iterator(begin()); }

		size_type			size() const { return bst.size(); }
		bool				empty() const { return bst.empty(); }
		size_type			max_size() const { return _allocator.max_size() / sizeof(node); }

		std::pair<iterator, bool>		insert(const value_type& val)
		{
			std::pair<node, bool>		p = bst.add_node(val);
			return std::pair<iterator, bool>(iterator(p.first, &bst), p.second);
		}
		iterator						insert(iterator position, const value_type& val)
		{
			(void)position;
			return insert(val).first;
		}
		template<class InputIterator>
		void							insert(InputIterator first, InputIterator end)
		{
			while (first != end)
				bst.add_node(*first++);
		}

		void				erase(iterator position) { bst.erase(*position); }
		void				erase(iterator first, iterator last)
		{
			key_type		_stop_key = last->first;

			while (first->first != _stop_key)
			{
				iterator		tmp = first;
				key_type		_kt = (++tmp)->first;
				bst.erase(*first);
				first = find(_kt);
			}
		}
		size_type			erase(const key_type& k)
		{
			size_type		_save = bst.size();

			if (!bst.size())
				return 0;
			bst.erase(value_type(k, mapped_type()));
			return _save - bst.size();
		}

		key_compare			key_comp() const { return _compare.comp; }
		value_compare		value_comp() const { return _compare; }

		iterator			find(const key_type& k)
		{
			node			n = bst.find(value_type(k, mapped_type()));
			if (n)
				return iterator(n, &bst);
			return end();
		}
		const_iterator		find(const key_type& k) const
		{
			node			n = bst.find(value_type(k, mapped_type()));
			if (n)
				return const_iterator(n, &bst);
			return end();
		}

		iterator			lower_bound(const key_type& k)
		{
			iterator		it = begin();
			value_type		val = value_type(k, mapped_type());

			while (it != end())
			{
				if (!_compare(*it, val))
					return it;
				++it;
			}
			return it;
		}
		const_iterator		lower_bound(const key_type& k) const
		{
			const_iterator	it = begin();
			value_type		val = value_type(k, mapped_type());

			while (it != end())
			{
				if (!_compare(*it, val))
					return it;
				++it;
			}
			return it;
		}

		iterator			upper_bound(const key_type& k)
		{
			iterator		it = begin();
			value_type		val = value_type(k, mapped_type());

			while (it != end())
			{
				if (_compare(val, *it))
					return it;
				++it;
			}
			return it;
		}
		const_iterator		upper_bound(const key_type& k) const
		{
			const_iterator	it = begin();
			value_type		val = value_type(k, mapped_type());

			while (it != end())
			{
				if (_compare(val, *it))
					return it;
				++it;
			}
			return it;
		}

		std::pair<iterator, iterator>					equal_range(const key_type& k)
		{
			return std::pair<iterator, iterator>(lower_bound(k), upper_bound(k));
		}
		std::pair<const_iterator, const_iterator>		equal_range(const key_type& k) const
		{
			return std::pair<const_iterator, const_iterator>(lower_bound(k), upper_bound(k));
		}

		size_type			count(const key_type& k) const
		{
			if (bst.find(value_type(k, mapped_type())))
				return 1;
			return 0;
		}

		void				clear() { bst.clear(); }
		void				swap(map& x) { bst.swap(x.bst); }

	private :
		allocator_type		_allocator;
		value_compare		_compare;
		tree				bst;
	};
	template<class Key, class T, class Compare, class Alloc>
	bool				operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		typename ft::map<Key, T, Compare, Alloc>::const_iterator		lit = lhs.begin();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator		rit = rhs.begin();
		while (lit != lhs.end())
		{
			if (*lit++ != *rit++)
				return false;
		}
		return true;
	}
	template<class Key, class T, class Compare, class Alloc>
	bool				operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		typename ft::map<Key, T, Compare, Alloc>::const_iterator		lit = lhs.begin();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator		rit = rhs.begin();
		while (lit != lhs.end() && rit != rhs.end())
		{
			if (*lit != *rit)
				return *lit < *rit;
			++lit;
			++rit;
		}
		if (rit != rhs.end())
			return true;
		return false;
	}
	template<class Key, class T, class Compare, class Alloc>
	bool				operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return !(lhs == rhs); }
	template<class Key, class T, class Compare, class Alloc>
	bool				operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return rhs < lhs; }
	template<class Key, class T, class Compare, class Alloc>
	bool				operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return !(lhs < rhs); }
	template<class Key, class T, class Compare, class Alloc>
	bool				operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs) { return !(rhs < lhs); }
}

#endif