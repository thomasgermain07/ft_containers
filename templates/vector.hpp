/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:37:40 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/27 00:39:53 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR
# define VECTOR

# include <iostream>
# include "vectorIterator.hpp"
# include <iterator>

namespace	ft
{
	template<class T, class Alloc = std::allocator<T> >
	class		vector
	{
	public :
		typedef T 											value_type;
		typedef Alloc										allocator_type;
		typedef ptrdiff_t									difference_type;
		typedef	size_t										size_type;
		typedef typename allocator_type::reference 			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef VectorIterator<value_type>					iterator;
		typedef ConstVectorIterator<value_type>				const_iterator;
		typedef ReverseVectorIterator<value_type>			reverse_iterator;
		typedef ConstReverseVectorIterator<value_type>		const_reverse_iterator;

					/* *** ************************ *** */
					/* *** Constructor / Destructor *** */
					/* *** ************************ *** */
		explicit vector(const allocator_type& alloc = allocator_type()) : _allocator(alloc) { _init_array(); }
		explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type()) : _allocator(alloc) { _init_array(n, val); }
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) : _allocator(alloc) { _init_array(); assign(first, last); }
		vector(const vector& x) { _init_array(); *this = x; }
		vector						&operator=(const vector& x)
		{
			_delete_array();
			_init_array(x.capacity());
			_size = x.size();
			for (size_type i = 0; i < _size; ++i)
				_array[i] = x._array[i];
			return *this;
		}
		~vector() { _delete_array(); }

					/* *** ************************ *** */
					/* *** 	   Member Functions		*** */
					/* *** ************************ *** */
		iterator					begin() { return iterator(_array); }
		iterator					end() { return iterator(_array + _size); }
		const_iterator				begin() const { return const_iterator(_array); }
		const_iterator				end() const { return const_iterator(_array + _size); }

		reverse_iterator			rbegin() { return reverse_iterator(end()); }
		reverse_iterator			rend() { return reverse_iterator(begin()); }
		const_reverse_iterator		rbegin() const { return const_reverse_iterator(end()); }
		const_reverse_iterator		rend() const { return const_reverse_iterator(begin()); }

		size_type					size() const { return _size; }
		size_type					capacity() const { return _capacity; }
		bool						empty() const { return !_size; }
		size_type					max_size() const { return _allocator.max_size(); }
		reference					front() { return operator[](0); }
		const_reference				front() const { return operator[](0); }
		reference					back() { return operator[](_size - 1); }
		const_reference				back() const { return operator[](_size - 1); }
		void						clear() { _delete_elem(_size); }

		void						pop_back()
		{
			if (!_size)
				return ;
			_delete_elem();
		}
		void						push_back(const value_type& val)
		{
			if (_size == _capacity)
				_extend_capacity();
			_add_elem(val);
		}

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

		void						resize(size_type n, value_type val = value_type())
		{
			if (n < _size)
				_delete_elem(_size - n);
			else if (n > _size)
			{
				while (n > _capacity)
					_extend_capacity();
				_add_elem_at(_size, val, n - _size);
			}
		}
		void						reserve(size_type n)
		{
			if (n > max_size())
				throw std::length_error("allocator<T>::allocate(size_t n) 'n' exceeds maximum supported size");
			if (n > _capacity)
				_extend_capacity(n);
		}

		iterator					insert(iterator position, const value_type& val)
		{
			size_type	_pos = _find_elem(position);

			if (_size == _capacity)
				_extend_capacity();
			_add_elem_at(_pos, val);
			return iterator(_array + _pos);
		}
		void						insert(iterator position, size_type n, const value_type& val)
		{
			size_type	_pos = _find_elem(position);

			while (n + _size > _capacity)
				_extend_capacity();
			_add_elem_at(_pos, val, n);
		}
		template<class InputIterator>
		void						insert(iterator position, InputIterator first, InputIterator last)
		{
			size_type	_pos = _find_elem(position);
			size_type	_dist = _distance(first, last);

			if (_dist + _size > _capacity)
				_extend_capacity(_dist + _size);
			_add_range_at(_pos, first, last);
		}

		iterator					erase(iterator position)
		{
			size_type		_pos = _find_elem(position);

			if (position == --end())
			{
				pop_back();
				return position;
			}
			_delete_elem_at(_pos);
			_move_front_from(_pos);
			return iterator(_array + _pos);
		}
		iterator					erase(iterator first, iterator last)
		{
			size_type		_pos = _find_elem(first);
			size_type		_dist = _distance(first, last);

			_delete_elem_at(_pos, _dist);
			_move_front_from(_pos, _dist);
			return iterator(_array + _pos);
		}

		template<class InputIterator>
		void						assign(InputIterator first, InputIterator last)
		{
			size_type		_dist = _distance(first, last);

			if ( _dist > _capacity)
				_extend_capacity(_dist);
			_delete_elem(_size);
			_add_range_at(0, first, last);
		}
		void						assign(size_type n, const value_type& val)
		{
			if (n > _capacity)
				_extend_capacity(n);
			_delete_elem(_size);
			for (size_type i = 0; i < n; ++i)
				_add_elem(val);
		}
		void						swap(vector& x)
		{
			_swap(_size, x._size);
			_swap(_capacity, x._capacity);
			_swap(_array, x._array);
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
			for (size_type i = 0; i < n; ++i)
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
			for (size_type i = 0; i < n_elem; ++i)
				_allocator.construct(_array + (index + i), val);
			_size += n_elem;
		}
		template<class InputIterator>
		void				_add_range_at(size_type index, InputIterator first, InputIterator last)
		{
			size_type		_dist = _distance(first, last);

			_move_back_from(index, _dist);
			for (size_type i = 0; i < _dist; ++i)
				_allocator.construct(_array + (index + i), *first++);
			_size += _dist;
		}
		template<class InputIterator>
		size_type			_distance(InputIterator first, InputIterator last)
		{
			size_type		_dist = 0;

			while (first++ != last)
				++_dist;
			return _dist;
		}
		void				_delete_elem(size_type n = 1)
		{
			for (size_type i = 0; i < n; ++i)
			{
				_allocator.destroy(_array + (_size - i));
				--_size;
			}
		}
		void				_delete_elem_at(size_type index, size_type n = 1)
		{
			for (size_type i = 0; i < n; ++i)
			{
				_allocator.destroy(_array + (index + i));
				--_size;
			}
		}
		void				_extend_capacity(size_type new_capacity = 0)
		{
			pointer			_new_array;

			if (!_capacity && !new_capacity)
				new_capacity = 1;
			if (!new_capacity)
				new_capacity = _capacity * 2;
			_new_array = _allocator.allocate(new_capacity);
			for (size_type i = 0; i < _size; ++i)
				_allocator.construct(_new_array + i, _array[i]);
			for (size_type i = _size; i < new_capacity; ++i)
				_allocator.construct(_new_array + i, value_type());
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
			pointer			src = _array + index;
			pointer			dst = _array + index + n;

			for (int i = _size - index; i >= 0; --i)
				_allocator.construct(dst + i, src[i]);
		}
		void				_move_front_from(size_type index, size_type n = 1)
		{
			pointer			src = _array + index + n;
			pointer			dst = _array + index;
			int				sz = _size - index;

			for (int i = 0; i < sz; ++i)
				_allocator.construct(dst + i, src[i]);
		}
		template<class X>
		void				_swap(X &x, X &y)
		{
			X			_tmp = x;
			x = y;
			y = _tmp;
		}
	};
	template<class T, class Alloc>
	void					swap(vector<T, Alloc>& x, vector<T, Alloc>& y) { x.swap(y); }

	template<class T, class Alloc>
	bool					operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (size_t i = 0; i < lhs.size(); ++i)
			if (!(lhs[i] == rhs[i]))
				return false;
		return true;
	}
	template<class T, class Alloc>
	bool					operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) // A refaire : ref -> list.hpp
	{
		size_t		i = 0;
		while (i < lhs.size() && i < rhs.size())
		{
			if (lhs[i] != rhs[i])
				return lhs[i] < rhs[i];
			++i;
		}
		if (rhs.size() > i)
			return true;
		return false;
	}
	template<class T, class Alloc>
	bool					operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return !(lhs == rhs); }
	template<class T, class Alloc>
	bool					operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return rhs < lhs; }
	template<class T, class Alloc>
	bool					operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return !(rhs < lhs); }
	template<class T, class Alloc>
	bool					operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs) { return !(lhs < rhs); }
};

#endif