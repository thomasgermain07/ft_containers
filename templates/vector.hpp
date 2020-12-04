/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:37:40 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/04 20:04:58 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR
# define VECTOR

# include <iostream>
# include "vectorIterator.hpp"

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
		typedef VectorIterator<value_type>					iterator;
		typedef ConstVectorIterator<value_type>				const_iterator;

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
		iterator					begin() { return iterator(_array); }
		iterator					end() { return iterator(_array + _size); }
		const_iterator				begin() const { return const_iterator(_array); }
		const_iterator				end() const { return const_iterator(_array + _size); }

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

		void						pop_back() { _delete_elem(_array + _size); }
		void						push_back(const value_type& val)
		{
			if (_size == _capacity)
				_extend_capacity();
			_add_elem(val);
		}
		// void						resize(size_type n, value_type val = value_type()) {} // Make insert first

		iterator					insert(iterator position, const value_type& val)
		{
			size_type _pos = _find_elem(position);

			if (_size == _capacity)
				_extend_capacity();
			_add_elem_at(_pos, val);
			return iterator(_array + _pos);
		}
		void						insert(iterator position, size_type n, const value_type& val)
		{
			size_type	_pos = _find_elem(position);

			while (n + _size > _capacity)
				_extend_capacity(_size + n);
			_add_elem_at(_pos, val, n);
		}

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
		void				_add_elem(const value_type& elem)
		{
			_allocator.construct(_array + _size, elem);
			++_size;
		}
		void				_add_elem_at(size_type index, const value_type& val, size_type n_elem = 1)
		{
			_move_back_from(index, n_elem);
			for (int i = 0; i < n_elem; ++i)
				_allocator.construct(_array + (index + i), val);
			_size += n_elem;
		}
		void				_delete_elem(pointer elem)
		{
			_allocator.destroy(elem);
			--_size;
		}
		void				_extend_capacity(size_type new_capacity = 0)
		{
			pointer			_new_array;

			if (!new_capacity)
				new_capacity = _capacity * 2;
			_new_array = _allocator.allocate(new_capacity);
			for (int i = 0; i < _size; ++i)
				_allocator.construct(_new_array + i, _array[i]);
			_delete_array();
			_capacity = new_capacity;
			_array = _new_array;
		}
		size_type				_find_elem(iterator position)
		{
			size_type			index = 0;
			for (iterator it = begin(); it != end(); ++it)
			{
				if (it == position)
					return index;
				++index;
			}
			return index;
		}
		void				_move_back_from(size_type index, size_type n = 1)
		{
			for (int _cpy = _size + n; _cpy > index; --_cpy)
				_allocator.construct(_array + _cpy, _array[_cpy - n]);
		}
	};
};

#endif