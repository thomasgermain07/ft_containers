/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 10:54:06 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/04 15:33:18 by thgermai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORITERATOR
# define VECTORITERATOR

# include <iostream>
# include "vector.hpp"

namespace		ft
{
	template<typename T>
	class	ConstVectorIterator;

	template<typename T>
	class	VectorIterator
	{
	public :
		typedef T								value_type;
		typedef value_type*						pointer_type;
		typedef value_type&						reference_type;
		typedef std::random_access_iterator_tag	iterator_category;
		typedef std::ptrdiff_t					difference_type;

		VectorIterator() {}
		VectorIterator(pointer_type ptr) : _ptr(ptr) {}
		VectorIterator(VectorIterator const &ref) { *this = ref; }
		VectorIterator				&operator=(VectorIterator const &ref) { _ptr = ref._ptr; return *this; }
		~VectorIterator() {}

		operator ConstVectorIterator<T>() const { return ConstVectorIterator<T>(_ptr); }

		pointer_type				operator->() const { return _ptr; }
		reference_type				operator*() const { return *_ptr; }

		bool						operator==(VectorIterator const &ref) { return _ptr == ref._ptr; }
		bool						operator!=(VectorIterator const &ref) { return !(*this == ref); }

		VectorIterator				&operator++() { _ptr = (_ptr + 1); return *this; }
		VectorIterator				&operator--() { _ptr = (_ptr - 1); return *this; }
		VectorIterator				operator++(int) { VectorIterator tmp(*this); operator++(); return tmp; }
		VectorIterator				operator--(int) { VectorIterator tmp(*this); operator--(); return tmp; }

		VectorIterator				operator+(int n) { return VectorIterator(_ptr, n); }
		VectorIterator				operator-(int n) { return VectorIterator(_ptr, -n); }
		difference_type				operator-(VectorIterator const &ref) { return _ptr - ref._ptr; }

		bool						operator<(VectorIterator const &ref) { return _ptr < ref._ptr; }
		bool						operator>(VectorIterator const &ref) { return _ptr > ref._ptr; }
		bool						operator<=(VectorIterator const &ref) { return _ptr <= ref._ptr; }
		bool						operator>=(VectorIterator const &ref) { return _ptr >= ref._ptr; }

		VectorIterator				&operator+=(int n) { _ptr = _ptr + n; return *this; }
		VectorIterator				&operator-=(int n) { _ptr = _ptr - n; return *this; }

		reference_type				operator[](size_t n) { return *(_ptr + n); }
	private :
		pointer_type		_ptr;

		VectorIterator(pointer_type ptr, int n) : _ptr(ptr + n) {}
	};

	template<typename T>
	class	ConstVectorIterator
	{
	public :
		typedef T								value_type;
		typedef const value_type*				pointer_type;
		typedef const value_type&				reference_type;
		typedef std::random_access_iterator_tag	iterator_category;
		typedef std::ptrdiff_t					difference_type;

		ConstVectorIterator() {}
		ConstVectorIterator(pointer_type ptr) : _ptr(ptr) {}
		ConstVectorIterator(ConstVectorIterator const &ref) { *this = ref; }
		ConstVectorIterator				&operator=(ConstVectorIterator const &ref) { _ptr = ref._ptr; return *this; }
		~ConstVectorIterator() {}

		pointer_type				operator->() const { return _ptr; }
		reference_type				operator*() const { return *_ptr; }

		bool						operator==(ConstVectorIterator const &ref) { return _ptr == ref._ptr; }
		bool						operator!=(ConstVectorIterator const &ref) { return !(*this == ref); }

		ConstVectorIterator			&operator++() { _ptr = (_ptr + 1); return *this; }
		ConstVectorIterator			&operator--() { _ptr = (_ptr - 1); return *this; }
		ConstVectorIterator			operator++(int) { ConstVectorIterator tmp(*this); operator++(); return tmp; }
		ConstVectorIterator			operator--(int) { ConstVectorIterator tmp(*this); operator--(); return tmp; }

		ConstVectorIterator			operator+(int n) { return ConstVectorIterator(_ptr, n); }
		ConstVectorIterator			operator-(int n) { return ConstVectorIterator(_ptr, -n); }
		difference_type				operator-(ConstVectorIterator const &ref) { return _ptr - ref._ptr; }

		bool						operator<(ConstVectorIterator const &ref) { return _ptr < ref._ptr; }
		bool						operator>(ConstVectorIterator const &ref) { return _ptr > ref._ptr; }
		bool						operator<=(ConstVectorIterator const &ref) { return _ptr <= ref._ptr; }
		bool						operator>=(ConstVectorIterator const &ref) { return _ptr >= ref._ptr; }

		ConstVectorIterator			&operator+=(int n) { _ptr = _ptr + n; return *this; }
		ConstVectorIterator			&operator-=(int n) { _ptr = _ptr - n; return *this; }

		reference_type				operator[](size_t n) { return *(_ptr + n); }
	private :
		pointer_type		_ptr;

		ConstVectorIterator(pointer_type ptr, int n) : _ptr(ptr + n) {}
	};

};



#endif