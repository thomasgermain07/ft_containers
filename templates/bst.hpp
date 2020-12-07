/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bst.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 22:06:15 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/08 00:19:28 by thgermai         ###   ########.fr       */
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

		pointer				data;
		node				left;
		node				right;
		allocator_type		allocator;
	};

	/* *** ************************************************************ *** */

	template<class T, class Alloc = std::allocator<T> >
	class		BinarySearchTree
	{
	public :
		typedef T									value_type;
		typedef Alloc								allocator_type;
		typedef BinaryNode<T, Alloc>*				node;
		typedef size_t								size_type;
		typedef typename allocator_type::pointer	pointer;

		BinarySearchTree() : root(NULL), _size(0) {}
		BinarySearchTree(const BinarySearchTree &ref) { *this = ref; }
		BinarySearchTree			&operator=(const BinarySearchTree &ref) { root = ref.root; }
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
		void				print() const { tree_visit(root); std::cout << std::endl; }
		pointer				find(const value_type& ref) const { return find_in_tree(root, ref); }

	private :
		node		root;
		size_type	_size;

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
			if (curr->left)
				delete_tree(curr->left);
			if (curr->right)
				delete_tree(curr->right);
			delete curr;
		}

		void				tree_visit(node curr) const
		{
			if (curr->left)
				tree_visit(curr->left);
			std::cout << *curr->data << " ";
			if (curr->right)
				tree_visit(curr->right);
		}

		pointer				find_in_tree(const node curr, const value_type& ref) const
		{
			if (*curr->data == ref)
				return curr->data;
			else if (*curr->data > ref)
			{
				if (curr->left)
					return find_in_tree(curr->left, ref);
			}
			else if (*curr->data < ref)
			{
				if (curr->right)
					return find_in_tree(curr->right, ref);
			}
			return NULL;
		}
	};
};

#endif