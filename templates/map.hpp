/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 14:02:19 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/10 23:04:11 by thgermai         ###   ########.fr       */
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
		typedef std::pair<const Key, T>						value_type;
		typedef Alloc										allocator_type;
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef Compare										key_compare;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
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

		typedef ft::MapIterator<value_type, value_compare, Alloc>	iterator;

		typedef BinarySearchTree<value_type, value_compare, Alloc> 	tree;
		typedef BinaryNode<value_type, Alloc>*						node;

		explicit map(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _allocator(alloc), _compare(comp), bst(tree(_compare)) {}
		// template<class InputIterator>
		// map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : _compare(comp) {}
		map(const map& x) : _allocator(x._allocator), _compare(x._compare), bst(x.bst) {}
		~map() {}

		mapped_type			&operator[] (const key_type& k)
		{
			value_type			val(k, mapped_type());
			pointer				n = bst.find(val);

			if (!n)
				n = bst.add_node(val)->data;
			return n->second;
		}

		iterator			begin() { return iterator(bst.min(), &bst); }
		iterator			end() { return iterator(bst.get_end_node(), &bst); }

		size_type			size() const { return bst.size(); }
		size_type			max_size() const { return _allocator.max_size() / sizeof(node); }

		void				insert(const key_type& key, const mapped_type& val)
		{
			value_type		p(key, val);
			bst.add_node(p);
		}
		void				print() const // to del
		{
			bst.print();
		}
		key_compare			key_comp() const { return _compare.comp; }
		value_compare		value_comp() const { return _compare; }

		size_type			count(const key_type& k) const
		{
			if (bst.find(value_type(k, mapped_type())))
				return 1;
			return 0;
		}

		void				pred(const key_type& k) const
		{
			bst.predecessor(bst.find(value_type(k, mapped_type())));
		}

	private :
		allocator_type		_allocator;
		value_compare		_compare;
		tree				bst;
	};

}

#endif