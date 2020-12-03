/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:37:40 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/03 17:48:57 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR
# define VECTOR

# include <iostream>

namespace	ft
{
	template<class T, class Alloc = std::allocator<T> >
	class		vector
	{
	public :
		typedef T 											value_type;
		typedef Alloc										allocator_type;
		typedef	size_t										size_type;
		typedef typename allocator_type::reference 			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;

					/* *** ************************ *** */
					/* *** Constructor / Destructor *** */
					/* *** ************************ *** */
		explicit vector(const allocator_type& alloc = allocator_type()) { _init_array(); }
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) { _init_array(n, val); }
		// template <class InputIterator>
		// vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {} // A faire plus tard
		vector(const vector& x) { _init_array(); *this = x; }
		~vector() { _delete_array(); }
		vector						&operator=(const vector& x)
		{
			_delete_array();
			_init_array(x.capacity());
			_size = x.size();
			for (int i = 0; i < _size; ++i)
				_array[i] = x._array[i];
			return *this;
		}

					/* *** ************************ *** */
					/* *** 	   Member Functions		*** */
					/* *** ************************ *** */
		size_type					size() const { return _size; }
		size_type					capacity() const { return _capacity; }
		bool						empty() { return !_size; }
		size_type					max_size() { return _allocator.max_size(); }

		reference					operator[](size_type n) { return *(_array + n); }
		const_reference				operator[](size_type n) const { return *(_array + n); }

		reference					at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("vector");
			return *(_array + n);
		}
		const_reference				at(size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range("vector");
			return *(_array + n);
		}

		reference					front() { return operator[](0); }
		const_reference				front() const { return operator[](0); }

		reference					back() { return operator[](_size - 1); }
		const_reference				back() const { return operator[](_size - 1); }

	private :
		allocator_type				_allocator;
		pointer						_array;
		size_type					_size;
		size_type					_capacity;

					/* *** ************************ *** */
					/* *** 	   Private Functions	*** */
					/* *** ************************ *** */
		void				_init_array(size_type n = 0, value_type const &val = value_type())
		{
			_array = _allocator.allocate(n);
			for (size_t i = 0; i < n; ++i)
				_allocator.construct(_array + i, val);
			_size = n;
			_capacity = n;
		}
		void				_delete_array()
		{
			for (size_t i = 0; i < _size; ++i)
				_allocator.destroy(_array + i);
			_allocator.deallocate(_array, _capacity);
		}
	};
};

#endif