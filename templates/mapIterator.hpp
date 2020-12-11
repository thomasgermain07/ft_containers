/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 15:10:23 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/11 15:14:06 by thgermai         ###   ########.fr       */
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
		MapIterator			&operator=(const MapIterator& ref)
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
		tree*			_tree;
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
		tree*			_tree;
	};
}

#endif