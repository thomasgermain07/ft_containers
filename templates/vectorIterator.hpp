/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectorIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thgermai <thgermai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 10:54:06 by thgermai          #+#    #+#             */
/*   Updated: 2020/12/07 16:59:44 by thgermai         ###   ########.fr       */
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
	class	ConstReverseVectorIterator;

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

		bool						operator==(VectorIterator const &ref) const { return _ptr == ref._ptr; }
		bool						operator!=(VectorIterator const &ref) const { return !(*this == ref); }

		VectorIterator				&operator++() { _ptr = (_ptr + 1); return *this; }
		VectorIterator				&operator--() { _ptr = (_ptr - 1); return *this; }
		VectorIterator				operator++(int) { VectorIterator tmp(*this); operator++(); return tmp; }
		VectorIterator				operator--(int) { VectorIterator tmp(*this); operator--(); return tmp; }

		VectorIterator				operator+(int n) { return VectorIterator(_ptr, n); }
		VectorIterator				operator-(int n) { return VectorIterator(_ptr, -n); }
		difference_type				operator-(VectorIterator const &ref) { return _ptr - ref._ptr; }

		bool						operator<(VectorIterator const &ref) const { return _ptr < ref._ptr; }
		bool						operator>(VectorIterator const &ref) const { return _ptr > ref._ptr; }
		bool						operator<=(VectorIterator const &ref) const { return _ptr <= ref._ptr; }
		bool						operator>=(VectorIterator const &ref) const { return _ptr >= ref._ptr; }

		VectorIterator				&operator+=(int n) { _ptr = _ptr + n; return *this; }
		VectorIterator				&operator-=(int n) { _ptr = _ptr - n; return *this; }

		reference_type				operator[](size_t n) const { return *(_ptr + n); }
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

		bool						operator==(ConstVectorIterator const &ref) const { return _ptr == ref._ptr; }
		bool						operator!=(ConstVectorIterator const &ref) const { return !(*this == ref); }

		ConstVectorIterator			&operator++() { _ptr = (_ptr + 1); return *this; }
		ConstVectorIterator			&operator--() { _ptr = (_ptr - 1); return *this; }
		ConstVectorIterator			operator++(int) { ConstVectorIterator tmp(*this); operator++(); return tmp; }
		ConstVectorIterator			operator--(int) { ConstVectorIterator tmp(*this); operator--(); return tmp; }

		ConstVectorIterator			operator+(int n) { return ConstVectorIterator(_ptr, n); }
		ConstVectorIterator			operator-(int n) { return ConstVectorIterator(_ptr, -n); }
		difference_type				operator-(ConstVectorIterator const &ref) { return _ptr - ref._ptr; }

		bool						operator<(ConstVectorIterator const &ref) const { return _ptr < ref._ptr; }
		bool						operator>(ConstVectorIterator const &ref) const { return _ptr > ref._ptr; }
		bool						operator<=(ConstVectorIterator const &ref) const { return _ptr <= ref._ptr; }
		bool						operator>=(ConstVectorIterator const &ref) const { return _ptr >= ref._ptr; }

		ConstVectorIterator			&operator+=(int n) { _ptr = _ptr + n; return *this; }
		ConstVectorIterator			&operator-=(int n) { _ptr = _ptr - n; return *this; }

		reference_type				operator[](size_t n) const { return *(_ptr + n); }
	private :
		pointer_type		_ptr;

		ConstVectorIterator(pointer_type ptr, int n) : _ptr(ptr + n) {}
	};

	template<typename T>
	class	ReverseVectorIterator
	{
	public :
		typedef VectorIterator<T>						iterator;
		typedef typename iterator::value_type			value_type;
		typedef typename iterator::iterator_category	iterator_category;
		typedef typename iterator::difference_type		difference_type;
		typedef typename iterator::pointer_type			pointer_type;
		typedef typename iterator::reference_type		reference_type;

		ReverseVectorIterator() {}
		ReverseVectorIterator(iterator base) : _base(base) {}
		ReverseVectorIterator(ReverseVectorIterator const &ref) { *this = ref; }
		ReverseVectorIterator			&operator=(ReverseVectorIterator const &ref) { _base = ref._base; return *this; }
		~ReverseVectorIterator() {}

		operator ConstReverseVectorIterator<T>() const { return ConstReverseVectorIterator<T>(_base); }

		pointer_type					operator->() const { iterator _tmp(_base); return (--_tmp).operator->(); }
		reference_type					operator*() const { iterator _tmp(_base); return (--_tmp).operator*(); }

		bool							operator==(ReverseVectorIterator const &ref) const { return _base == ref._base; }
		bool							operator!=(ReverseVectorIterator const &ref) const { return !(*this == ref); }

		ReverseVectorIterator			&operator++() { _base--; return *this; }
		ReverseVectorIterator			&operator--() { _base++; return *this; }
		ReverseVectorIterator			operator++(int) { ReverseVectorIterator tmp(*this); operator--(); return tmp; }
		ReverseVectorIterator			operator--(int) { ReverseVectorIterator tmp(*this); operator++(); return tmp; }

		bool							operator<(ReverseVectorIterator const &ref) const { return _base > ref._base; }
		bool							operator>(ReverseVectorIterator const &ref) const { return _base < ref._base; }
		bool							operator<=(ReverseVectorIterator const &ref) const { return _base >= ref._base; }
		bool							operator>=(ReverseVectorIterator const &ref) const { return _base <= ref._base; }

		iterator						base() const { return _base;}

	private :
		iterator		_base;
	};

	template<typename T>
	class	ConstReverseVectorIterator
	{
	public :
		typedef ConstVectorIterator<T>					iterator;
		typedef typename iterator::value_type			value_type;
		typedef typename iterator::iterator_category	iterator_category;
		typedef typename iterator::difference_type		difference_type;
		typedef typename iterator::pointer_type			pointer_type;
		typedef typename iterator::reference_type		reference_type;

		ConstReverseVectorIterator() {}
		ConstReverseVectorIterator(iterator base) : _base(base) {}
		ConstReverseVectorIterator(ConstReverseVectorIterator const &ref) { *this = ref; }
		ConstReverseVectorIterator			&operator=(ConstReverseVectorIterator const &ref) { _base = ref._base; return *this; }
		~ConstReverseVectorIterator() {}

		pointer_type						operator->() const { iterator _tmp(_base); return (--_tmp).operator->(); }
		reference_type						operator*() const { iterator _tmp(_base); return (--_tmp).operator*(); }

		bool								operator==(ConstReverseVectorIterator const &ref) const { return _base == ref._base; }
		bool								operator!=(ConstReverseVectorIterator const &ref) const { return !(*this == ref); }

		ConstReverseVectorIterator			&operator++() { _base--; return *this; }
		ConstReverseVectorIterator			&operator--() { _base++; return *this; }
		ConstReverseVectorIterator			operator++(int) { ConstReverseVectorIterator tmp(*this); operator--(); return tmp; }
		ConstReverseVectorIterator			operator--(int) { ConstReverseVectorIterator tmp(*this); operator++(); return tmp; }

		bool								operator<(ConstReverseVectorIterator const &ref) const { return _base > ref._base; }
		bool								operator>(ConstReverseVectorIterator const &ref) const { return _base < ref._base; }
		bool								operator<=(ConstReverseVectorIterator const &ref) const { return _base >= ref._base; }
		bool								operator>=(ConstReverseVectorIterator const &ref) const { return _base <= ref._base; }

		iterator							base() const { return _base;}

	private :
		iterator		_base;
	};
};



#endif