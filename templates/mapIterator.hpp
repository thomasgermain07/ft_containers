/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:10:23 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/27 02:45:30 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPITERATOR
# define MAPITERATOR

# include <iostream>
# include "bst.hpp"
# include "map.hpp"

namespace	ft
{
	template<class T, class value_compare, class Alloc>
	class			ConstMapIterator;

	template<class T, class value_compare, class Alloc>
	class			MapIterator
	{
	public :
		typedef T													value_type;
		typedef value_type*											pointer_type;
		typedef value_type&											reference_type;
		typedef BinaryNode<value_type>*								node;
		typedef std::bidirectional_iterator_tag						iterator_category;
		typedef std::ptrdiff_t										difference_type;
		typedef BinarySearchTree<value_type, value_compare, Alloc> 	tree;

		MapIterator() : _node(NULL), _tree(NULL) {}
		MapIterator(node n, tree* t) : _node(n), _tree(t) {}
		MapIterator(const MapIterator& ref) { *this = ref; }
		MapIterator				&operator=(const MapIterator& ref)
		{
			_node = ref._node;
			_tree = ref._tree;
			return *this;
		}
		~MapIterator() {}

		operator ConstMapIterator<T, value_compare, Alloc>() const { return ConstMapIterator<T, value_compare, Alloc>(_node, _tree); }

		pointer_type			operator->() const { return _node->data; }
		reference_type			operator*() const { return *_node->data; }

		MapIterator				&operator++() { _node = _tree->increm(_node); return *this; }
		MapIterator				operator++(int) { MapIterator _tmp(_node, _tree); _node = _tree->increm(_node); return _tmp; }
		MapIterator				&operator--() { _node = _tree->decrem(_node); return *this; }
		MapIterator				operator--(int) { MapIterator _tmp(_node, _tree); _node = _tree->decrem(_node); return _tmp; }

		bool					operator==(MapIterator const &ref) const { return _node->data == ref._node->data; }
		bool					operator!=(MapIterator const &ref) const { return !(*this == ref); }

	private :
		node			_node;
		tree			*_tree;
	};

	template<class T, class value_compare, class Alloc>
	class			ConstMapIterator
	{
	public :
		typedef T															value_type;
		typedef const value_type*											pointer_type;
		typedef const value_type&											reference_type;
		typedef BinaryNode<value_type>*										node;
		typedef std::bidirectional_iterator_tag								iterator_category;
		typedef std::ptrdiff_t												difference_type;
		typedef const BinarySearchTree<value_type, value_compare, Alloc> 	tree;

		ConstMapIterator() : _node(NULL), _tree(NULL) {}
		ConstMapIterator(node n, tree* t) : _node(n), _tree(t) {}
		ConstMapIterator(const ConstMapIterator& ref) { *this = ref; }
		ConstMapIterator			&operator=(const ConstMapIterator& ref)
		{
			_node = ref._node;
			_tree = ref._tree;
			return *this;
		}
		~ConstMapIterator() {}

		pointer_type				operator->() const { return _node->data; }
		reference_type				operator*() const { return *_node->data; }

		ConstMapIterator			&operator++() { _node = _tree->increm(_node); return *this; }
		ConstMapIterator			operator++(int) { ConstMapIterator _tmp(_node, _tree); _node = _tree->increm(_node); return _tmp; }
		ConstMapIterator			&operator--() { _node = _tree->decrem(_node); return *this; }
		ConstMapIterator			operator--(int) { ConstMapIterator _tmp(_node, _tree); _node = _tree->decrem(_node); return _tmp; }

		bool						operator==(ConstMapIterator const &ref) const { return _node->data == ref._node->data; }
		bool						operator!=(ConstMapIterator const &ref) const { return !(*this == ref); }

	private :
		node			_node;
		tree			*_tree;
	};

	template<class T, class value_compare, class Alloc>
	class			ConstReverseMapIterator;

	template<class T, class value_compare, class Alloc>
	class			ReverseMapIterator
	{
	public :
		typedef T													value_type;
		typedef MapIterator<T, value_compare, Alloc>				iterator;
		typedef typename iterator::pointer_type						pointer_type;
		typedef typename iterator::reference_type					reference_type;
		typedef typename iterator::iterator_category				iterator_category;
		typedef typename iterator::difference_type					difference_type;

		ReverseMapIterator() {}
		ReverseMapIterator(const iterator& it) : _it(it) {}
		ReverseMapIterator(const ReverseMapIterator& ref) { *this = ref; }
		ReverseMapIterator				&operator=(const ReverseMapIterator& ref)
		{
			_it = ref._it;
			return *this;
		}
		~ReverseMapIterator() {}

		operator ConstReverseMapIterator<T, value_compare, Alloc>() const { return ConstReverseMapIterator<T, value_compare, Alloc>(_it); }

		pointer_type			operator->() const { iterator _tmp(_it); return (--_tmp).operator->(); }
		reference_type			operator*() const { iterator _tmp(_it); return (--_tmp).operator*(); }

		ReverseMapIterator				&operator++() { --_it; return *this; }
		ReverseMapIterator				&operator--() { ++_it; return *this; }
		ReverseMapIterator				operator++(int) { ReverseMapIterator _tmp(*this); --_it; return _tmp; }
		ReverseMapIterator				operator--(int) { ReverseMapIterator _tmp(*this); ++_it; return _tmp; }

		bool					operator==(ReverseMapIterator const &ref) const { return _it == ref._it; }
		bool					operator!=(ReverseMapIterator const &ref) const { return !(*this == ref); }

	private :
		iterator		_it;
	};

	template<class T, class value_compare, class Alloc>
	class			ConstReverseMapIterator
	{
	public :
		typedef T													value_type;
		typedef ConstMapIterator<T, value_compare, Alloc>			iterator;
		typedef typename iterator::pointer_type						pointer_type;
		typedef typename iterator::reference_type					reference_type;
		typedef typename iterator::iterator_category				iterator_category;
		typedef typename iterator::difference_type					difference_type;

		ConstReverseMapIterator() {}
		ConstReverseMapIterator(const iterator& it) : _it(it) {}
		ConstReverseMapIterator(const ConstReverseMapIterator& ref) { *this = ref; }
		ConstReverseMapIterator			&operator=(const ConstReverseMapIterator& ref)
		{
			_it = ref._it;
			return *this;
		}
		~ConstReverseMapIterator() {}

		pointer_type					operator->() const { iterator _tmp = _it; return (--_tmp).operator->(); }
		reference_type					operator*() const { iterator _tmp = _it; return (--_tmp).operator*(); }

		ConstReverseMapIterator			&operator++() { --_it; return *this; }
		ConstReverseMapIterator			&operator--() { ++_it; return *this; }
		ConstReverseMapIterator			operator++(int) { ConstReverseMapIterator _tmp(*this); --_it; return _tmp; }
		ConstReverseMapIterator			operator--(int) { ConstReverseMapIterator _tmp(*this); ++_it; return _tmp; }

		bool		operator==(ConstReverseMapIterator const &ref) const { return _it == ref._it; }
		bool		operator!=(ConstReverseMapIterator const &ref) const { return !(*this == ref); }

	private :
		iterator		_it;
	};
}

#endif