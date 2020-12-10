/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 22:06:15 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/10 23:37:00 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BST
# define BST

# include <iostream>
# include <fstream>
# include <memory>

namespace	ft
{
	template<class T, class Alloc = std::allocator<T> >
	struct		BinaryNode
	{
		typedef T									value_type;
		typedef Alloc								allocator_type;
		typedef BinaryNode<T, Alloc>*				node;
		typedef typename allocator_type::pointer	pointer;
		typedef typename allocator_type::reference	reference;

		BinaryNode(const value_type &val) : left(NULL), right(NULL)
		{
			allocator_type		alloc;

			data = alloc.allocate(1);
			alloc.construct(data, val);
		}
		BinaryNode			&operator=(const BinaryNode &ref)
		{
			data = ref.data;
			left = ref.left;
			right = ref.right;
		}
		~BinaryNode()
		{
			allocator_type		alloc;

			alloc.destroy(data);
			alloc.deallocate(data, 1);
		}

		pointer				operator->() const { return data; }
		reference			operator*() const { return *data; }

		node				clone() const
		{
			node			n = new BinaryNode<T, Alloc>(*data);
			if (left)
				n->left = left->clone();
			if (right)
				n->right = right->clone();
			return n;
		}

		pointer				data;
		node				left;
		node				right;
	};

	/* *** ************************************************************ *** */

	template<class T, class value_compare = std::less<T>, class Alloc = std::allocator<T> >
	class		BinarySearchTree
	{
	public :
		typedef T									value_type;
		typedef Alloc								allocator_type;
		typedef BinaryNode<T, Alloc>*				node;
		typedef size_t								size_type;
		typedef typename allocator_type::reference	reference;
		typedef typename allocator_type::pointer	pointer;

		BinarySearchTree() : root(NULL), _size(0), _comp(value_compare()) { _set_end_node();}
		BinarySearchTree(const value_compare& comp) : root(NULL), _size(0), _comp(comp) { _set_end_node(); }
		BinarySearchTree(const BinarySearchTree &ref)
			: root(NULL), _size(ref.size()), _comp(ref._comp) { *this = ref; }
		BinarySearchTree			&operator=(const BinarySearchTree &ref)
		{
			if (root)
				_delete_tree(root);
			if (ref.root)
				root = ref.root->clone();
			return *this;
		}
		~BinarySearchTree() { _delete_tree(root); delete _end_node; }

		node				min() const
		{
			if (!_size)
				return _end_node;
			return _min(root);
		}
		node				max() const
		{
			if (!_size)
				return _end_node;
			return _max(root);
		}
		size_type			size() const { return _size; }
		bool				empty() const { return !_size; }
		void				erase(const value_type& val) { _delete(root, val); }
		node				get_end_node() const { return _end_node; }
		node				add_node(const value_type &val)
		{
			node n = new BinaryNode<T, Alloc>(val);

			if (!root)
			{
				root = n;
				++_size;
			}
			else if (_insert(root, n))
				++_size;
			return n;
		}
		pointer				find(const value_type& val) const
		{
			node			n = _find(root, val);
			if (!n)
				return NULL;
			return n->data;
		}
		node				predecessor(pointer ptr) const
		{
			node			pred = NULL;
			node			n;
			if (!ptr || ptr == root->data)
				return NULL;
			if ((n = _get_node(root, ptr)))
			 	pred = _predecessor(root, n);
			return pred;
		}
		node				increm(node n)
		{
			if (n == _end_node)
				return _end_node->left;
			return _increm(predecessor(n->data), n);
		}
		node				decrem(node n)
		{
			if (n == _end_node)
				return _max(root);
			return _decrem(predecessor(n->data), n);
		}
	private :
		node			root;
		size_type		_size;
		value_compare	_comp;
		node			_end_node;

		node				_increm(node pred, node n)
		{
			if (n == _max(root))
				return _end_node;
			if (n->right)
				return _min(n->right);
			else if (_comp(*pred->data, *n->data))
				return _increm(predecessor(pred->data), n);
			return pred;
		}
		node				_decrem(node pred, node n)
		{
			if (n == _min(root))
				return NULL;
			if (n->left)
				return _max(n->left);
			else if (_comp(*n->data, *pred->data))
				return _decrem(predecessor(pred->data), n);
			return pred;
		}
		void				_set_end_node()
		{
			_end_node = new BinaryNode<value_type, Alloc>(value_type());
		}
		bool				_insert(node curr, node n)
		{
			if (!_comp(*n->data, *curr->data) && !_comp(*curr->data, *n->data)) // Equal
			{
				delete n;
				return false;
			}
			if (_comp(*n->data, *curr->data))
			{
				if (curr->left)
					return _insert(curr->left, n);
				else
					curr->left = n;
			}
			else if (_comp(*curr->data, *n->data))
			{
				if (curr->right)
					return _insert(curr->right, n);
				else
				{
					curr->right = n;
					_end_node->right = n;
				}
			}
			return true;
		}
		void				_delete_tree(node curr)
		{
			if (!curr)
				return ;
			if (curr->left)
				_delete_tree(curr->left);
			if (curr->right)
				_delete_tree(curr->right);
			delete curr;
		}
		node				_find(const node curr, const value_type& val) const
		{
			if (!curr)
				return NULL;
			if (!_comp(val, *curr->data) && !_comp(*curr->data, val)) // Equal
				return curr;
			else if (_comp(val, *curr->data))
			{
				if (curr->left)
					return _find(curr->left, val);
			}
			else if (_comp(*curr->data, val))
			{
				if (curr->right)
					return _find(curr->right, val);
			}
			return NULL;
		}
		node				_delete(node curr, const value_type& val)
		{
			if (!curr)
				return curr;
			if (_comp(val, *curr->data)) // Less
				curr->left = _delete(curr->left, val);
			else if (_comp(*curr->data, val)) // More
				curr->right = _delete(curr->right, val);
			else
			{
				if (!curr->left)
				{
					node	tmp = curr->right;
					delete curr;
					return tmp;
				}
				else if (!curr->right)
				{
					node	tmp = curr->left;
					delete curr;
					return tmp;
				}
				node		tmp = _min(curr->right);
				*curr->data = *tmp->data;
				curr->right = _delete(curr->right, val);
			}
			return curr;
		}
		node				_min(const node curr) const
		{
			if (curr->left)
				return _min(curr->left);
			return curr;
		}
		node				_max(const node curr) const
		{
			if (curr->right)
				return _max(curr->right);
			return curr;
		}
		node				_get_node(const node curr, const pointer ptr) const
		{
			if (curr->data == ptr)
				return curr;
			else if (_comp(*ptr, *curr->data))
			{
				if (curr->left)
					return _get_node(curr->left, ptr);
			}
			else if (curr->right)
				return _get_node(curr->right, ptr);
			return NULL;
		}
		node				_predecessor(const node curr, const node n) const
		{
			if (curr->right == n || curr->left == n)
				return curr;
			else if (_comp(*n->data, *curr->data))
			{
				if (curr->left)
					return _predecessor(curr->left, n);
			}
			else if (curr->right)
				return _predecessor(curr->right, n);
			return NULL;
		}
	};
};

#endif