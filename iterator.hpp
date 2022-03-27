/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a1111 <a1111@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:29:12 by a1111             #+#    #+#             */
/*   Updated: 2022/01/29 15:50:59 by a1111            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <iostream>
# include <cstddef>
# include "iterator_traits.hpp"
# include "pair.hpp"
# include "enable_if.hpp"
# include "is_integral.hpp"
# include "algo.hpp"

namespace ft
{

template <typename T>
class random_access_iterator
{

public:
	typedef T									value_type;
	typedef value_type 							&reference;
	typedef const value_type 					&const_reference;
	typedef value_type 							*pointer;
	typedef const value_type					*const_pointer;
	typedef std::random_access_iterator_tag 	iterator_category;	
	typedef std::ptrdiff_t 						difference_type;

private:
	pointer	_pointer;

public:
	random_access_iterator(void)
	: _pointer(nullptr) {}

	random_access_iterator(const random_access_iterator& cp)
	{
		*this = cp;
	}
	
	random_access_iterator(pointer pt)
	: _pointer(pt) {}
	
	~random_access_iterator() {}

	random_access_iterator& operator=(const random_access_iterator& cp)
	{
		if (this != &cp)
			this->_pointer = cp._pointer;
		return (*this);
	}
	
	operator random_access_iterator<const value_type>(void) const
	{
		return (this->_pointer);
	}

	bool operator==(const random_access_iterator& cp) const
	{
		return (this->_pointer == cp._pointer);
	}

	bool operator!=(const random_access_iterator& cp) const
	{
		return (this->_pointer != cp._pointer);
	}

	bool operator<(const random_access_iterator& cp) const
	{
		return (this->_pointer < cp._pointer);
	}

	bool operator<=(const random_access_iterator& cp) const
	{
		return (this->_pointer <= cp._pointer);
	}

	bool operator>(const random_access_iterator& cp) const
	{
		return (this->_pointer > cp._pointer);
	}

	bool operator>=(const random_access_iterator& cp) const
	{
		return (this->_pointer >= cp._pointer);
	}

	reference operator*(void) const
	{
		return (*_pointer);
	}

	pointer operator->(void) const
	{
		return (_pointer);
	}
	
	random_access_iterator& operator++(void)
	{
		this->_pointer++;
		return (*this);
	}
	
	random_access_iterator operator++(int)
	{
		random_access_iterator tmp = *this;
		this->_pointer++;
		return (tmp);
	}
	
	random_access_iterator& operator--(void)
	{
		this->_pointer--;
		return (*this);
	}
	
	random_access_iterator operator--(int)
	{
		random_access_iterator tmp = *this;
		this->_pointer--;
		return (tmp);
	}

	random_access_iterator operator+(difference_type n) const
	{
		return (random_access_iterator(_pointer + n));
	}

	random_access_iterator operator-(difference_type n) const
	{
		return (random_access_iterator(_pointer - n));
	}
	
	difference_type operator-(const random_access_iterator& cp) const
	{
		return (_pointer - cp._pointer);
	}

	random_access_iterator& operator+=(int n)
	{
		this->_pointer += n;
		return (*this);
	}
	
	random_access_iterator& operator-=(int n)
	{
		this->_pointer -= n;
		return (*this);
	}
	
	reference operator[](difference_type n) const
	{
		return (*(_pointer + n));
	}
};

template <typename Iterator>
class reverse_iterator
{
public:
	typedef Iterator													iterator_type;
	typedef typename iterator_traits<Iterator>::value_type				value_type;
	typedef typename iterator_traits<Iterator>::reference				reference;
	
	typedef typename iterator_traits<Iterator>::pointer					pointer;
	
	typedef typename iterator_traits<Iterator>::iterator_category		iterator_category;
	typedef typename iterator_traits<Iterator>::difference_type			difference_type;

private:
	iterator_type	_it;

public:
	reverse_iterator(void)
	: _it(iterator_type()) {}

	explicit reverse_iterator(iterator_type it)
	: _it(it - 1) {}

	template <typename V>
	reverse_iterator(const reverse_iterator& cp)
	: _it(cp._it) {}

	iterator_type base(void) const
	{
		return (_it + 1);
	}

	reference operator*(void) const
	{
		return (*_it);
	}

	pointer operator->(void) const
	{
		return (&(*_it));
	}

	reverse_iterator operator+(difference_type n) const
	{
		return (reverse_iterator(base() - n));
	}

	reverse_iterator operator-(difference_type n) const
	{
		return (reverse_iterator(base() + n));
	}
	
	reverse_iterator& operator++(int)
	{
		reverse_iterator tmp = *this;
		--_it;
		return (tmp);
	}
	
	reverse_iterator& operator++(void)
	{
		--_it;
		return (*this);
	}
	
	reverse_iterator& operator--(int)
	{
		reverse_iterator tmp = *this;
		++_it;
		return (tmp);
	}
	
	reverse_iterator& operator--(void)
	{
		++_it;
		return (*this);
	}
	
	reverse_iterator& operator+=(difference_type n)
	{
		_it -= n;
		return (*this);
	}
	
	reverse_iterator& operator-=(difference_type n)
	{
		_it += n;
		return (*this);
	}

	reference operator[](difference_type n) const
	{
		return (*(_it - n));
	}	
};

template <typename I>
bool operator==(const reverse_iterator<I>& lhs, const reverse_iterator<I>& rhs)
{
	return (lhs.base() == rhs.base());
}

template <typename I>
bool operator!=(const reverse_iterator<I>& lhs, const reverse_iterator<I>& rhs)
{
	return (lhs.base() != rhs.base());
}

template <typename I>
bool operator<(const reverse_iterator<I>& lhs, const reverse_iterator<I>& rhs)
{
	return (lhs.base() > rhs.base());
}

template <typename I>
bool operator<=(const reverse_iterator<I>& lhs, const reverse_iterator<I>& rhs)
{
	return (lhs.base() >= rhs.base());
}

template <typename I>
bool operator>(const reverse_iterator<I>& lhs, const reverse_iterator<I>& rhs)
{
	return (lhs.base() < rhs.base());
}

template <typename I>
bool operator>=(const reverse_iterator<I>& lhs, const reverse_iterator<I>& rhs)
{
	return (lhs.base() <= rhs.base());
}

};

#endif