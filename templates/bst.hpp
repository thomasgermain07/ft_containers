/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 22:06:15 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/08 16:20:18 by thgermai         ###   ########.fr       */
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
			data = allocator.allocate(1);
			allocator.construct(data, val);
		}
		BinaryNode			&operator=(const BinaryNode &ref)
		{
			data = ref.data;
			left = ref.left;
			right = ref.right;
		}
		~BinaryNode()
		{
			allocator.destroy(data);
			allocator.deallocate(data, 1);
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
		allocator_type		allocator;
	};

	/* *** ************************************************************ *** */

	template<class T, class Alloc = std::allocator<T>, class value_compare = std::less<T> >
	class		BinarySearchTree
	{
	public :
		typedef T									value_type;
		typedef Alloc								allocator_type;
		typedef BinaryNode<T, Alloc>*				node;
		typedef size_t								size_type;
		typedef typename allocator_type::reference	reference;
		typedef typename allocator_type::pointer	pointer;

		BinarySearchTree(value_compare = value_compare()) : root(NULL), _size(0) {}
		BinarySearchTree(const BinarySearchTree &ref) { *this = ref; }
		BinarySearchTree			&operator=(const BinarySearchTree &ref)
		{
			if (root)
				delete_tree(root);
			root = ref.root->clone();
			_size = ref.size();
			return *this;
		}
		~BinarySearchTree() { delete_tree(root); }

		void				add_node(const value_type &val)
		{
			if (!root)
			{
				root = new BinaryNode<T, Alloc>(val);
				++_size;
			}
			else if (insert_node(root, new BinaryNode<T, Alloc>(val)))
				++_size;
		}

		size_type			size() const { return _size; }
		value_type			min() const { return *min_in_tree(root)->data; }
		value_type			max() const { return *max_in_tree(root)->data; }
		bool				empty() const { return !_size; }
		pointer				find(const value_type& val) const
		{
			node			n = find_in_tree(root, val);
			if (!n)
				return NULL;
			return n->data;
		}
		void				erase(const value_type& val) { delete_in_tree(root, val) ;}
		void				print() const { tree_visit(root); std::cout << std::endl; } // to delete
	private :
		node		root;
		size_type	_size;
		value_compare	_comp;

		bool				insert_node(node curr, node n)
		{
			if (*n->data == *curr->data)
			{
				delete n;
				return false;
			}
			if (*n->data < *curr->data)
			{
				if (curr->left)
					return insert_node(curr->left, n);
				else
					curr->left = n;
			}
			else if (*n->data > *curr->data)
			{
				if (curr->right)
					return insert_node(curr->right, n);
				else
					curr->right = n;
			}
			return true;
		}
		void				delete_tree(node curr)
		{
			if (!curr)
				return ;
			if (curr->left)
				delete_tree(curr->left);
			if (curr->right)
				delete_tree(curr->right);
			delete curr;
		}
		void				tree_visit(node curr) const // To deletet
		{
			if (curr->left)
				tree_visit(curr->left);
			std::cout << *curr->data << " ";
			if (curr->right)
				tree_visit(curr->right);
		}
		node				find_in_tree(const node curr, const value_type& val) const
		{
			if (*curr->data == val)
				return curr;
			else if (*curr->data > val)
			{
				if (curr->left)
					return find_in_tree(curr->left, val);
			}
			else if (*curr->data < val)
			{
				if (curr->right)
					return find_in_tree(curr->right, val);
			}
			return NULL;
		}
		node				delete_in_tree(node curr, const value_type& val)
		{
			if (!curr)
				return curr;
			if (val < *curr->data)
				curr->left = delete_in_tree(curr->left, val);
			else if (val > *curr->data)
				curr->right = delete_in_tree(curr->right, val);
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
				node		tmp = min_in_tree(curr->right);
				*curr->data = *tmp->data;
				curr->right = delete_in_tree(curr->right, val);
			}
			return curr;
		}
		node				min_in_tree(const node curr) const
		{
			if (curr->left)
				return min_in_tree(curr->left);
			return curr;
		}
		node				max_in_tree(const node curr) const
		{
			if (curr->right)
				return max_in_tree(curr->right);
			return curr;
		}
	};
};

#endif