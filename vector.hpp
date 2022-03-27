/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a1111 <a1111@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:21:38 by a1111             #+#    #+#             */
/*   Updated: 2022/01/30 17:20:47 by a1111            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <string>
# include <stdexcept>
# include <vector>
# include <iostream>

# include "iterator.hpp"

namespace ft
{

template < typename T, typename Allocator = std::allocator<T> >
class vector
{
public:
	typedef T													value_type;
	typedef Allocator											allocator_type;
	
	typedef typename allocator_type::reference					reference;
	typedef typename allocator_type::const_reference			const_reference;
	typedef typename allocator_type::pointer					pointer;
	typedef typename allocator_type::const_pointer				const_pointer;
	
	typedef random_access_iterator<value_type> 					iterator;
	typedef random_access_iterator<const value_type> 			const_iterator;
	typedef reverse_iterator<const_iterator> 					const_reverse_iterator;
	typedef reverse_iterator<iterator> 							reverse_iterator;

	typedef std::ptrdiff_t										difference_type;
	typedef typename allocator_type::size_type					size_type;


	explicit vector(const allocator_type &alloc = allocator_type())
	: _alloc(alloc), _size(0), _arr(nullptr), _capacity(0) {}
	

	explicit vector(size_type count, const value_type &value = value_type(), const allocator_type &alloc = allocator_type())
	: _alloc(alloc), _size(count), _arr(_alloc.allocate(count)), _capacity(count)
	{
		for (size_type i = 0; i < count; i++)
			_alloc.construct(_arr + i, value);
	}
	

	template <typename InputIterator>
	vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const allocator_type &alloc = allocator_type()) 
	: _alloc(alloc), _size(last - first), _arr(_alloc.allocate(last - first)), _capacity(last - first)
	{
		for (size_type i = 0; i < _size; i++)
			_alloc.construct(_arr + i, *(first + i));
	}


	vector(const vector& cp)
	:  _alloc(cp._alloc), _arr(nullptr), _size(0), _capacity(0)
	{
		*this = cp;
	}

	~vector(void)
	{
		for (size_type i = 0; i < _size; i++)
			_alloc.destroy(_arr + i);
		_alloc.deallocate(_arr, _capacity);
	}

	vector& operator=(const vector& cp)
	{
		if (this != &cp)
		{
			this->clear();
			this->_alloc.deallocate(this->_arr, this->capacity());
			this->_arr = this->_alloc.allocate(cp.capacity());
			this->_size = cp.size();
			this->_capacity = cp.capacity();
			for (size_type i = 0; i < cp.size(); i++)
				this->_alloc.construct(_arr + i, cp[i]);
		}
		return (*this);
	}	

	iterator begin()
	{
		return (iterator(_arr));
	}
	const_iterator begin() const
	{
		return (const_iterator(_arr));
	}
	iterator end()
	{
		return (iterator(_arr + _size));
	}
	const_iterator end() const
	{
		return (const_iterator(_arr + _size));
	}


	reverse_iterator rbegin()
	{
		return (reverse_iterator(end()));
	}
	const_reverse_iterator rbegin() const
	{
		return (const_reverse_iterator(end()));
	}
	reverse_iterator rend()
	{
		return (reverse_iterator(begin()));
	}
	const_reverse_iterator rend() const
	{
		return (const_reverse_iterator(begin()));
	}


	
	size_type size(void) const
	{
		return (this->_size);
	}

	size_type max_size(void) const
	{
		return (this->_alloc.max_size());
	}

	void resize (size_type n, value_type val = value_type())
	{
		if (n < _size)
		{
			for (size_type i = n; i < _size; i++)
				_alloc.destroy(_arr + i);
		}
		else
		{
			if (n > _capacity) 
			{
				size_type tmpCap = n;
				if (n < _capacity * 2) 
					tmpCap = _capacity * 2;
				reserve(tmpCap);
			}
			for (size_type i = _size; i < n; i++) 
				_alloc.construct(_arr + i, val);
		}
		_size = n;
	};

	size_type capacity(void) const
	{
		return (this->_capacity);
	}


	bool empty(void) const
	{
		return (this->_size == 0);
	}

	void reserve(size_type n)
	{
		if (n > this->max_size())
			throw std::length_error("vector::reserve");
		else if (n <= this->_capacity)
			return ;
		pointer tmp = _alloc.allocate(n);
		for (size_type i = 0; i < this->_size; i++)
			_alloc.construct(tmp + i, _arr[i]);
		this->~vector();
		this->_capacity = n;
		this->_arr = tmp;
	}

	reference operator[](size_type n)
	{
		if (n >= _size)
			throw std::out_of_range("vector::distance: too big index");	
		return (this->_arr[n]);
	}
	const_reference operator[](size_type n) const
	{
		if (n >= _size)
			throw std::out_of_range("vector::distance: too big index");
		return (this->_arr[n]);
	}

    reference at(size_type n)
	{
		if (n >= _size)
			throw std::out_of_range("vector::distance: too big index");
		return (this->_arr[n]);
	}
	const_reference at(size_type n) const
	{
		if (n >= _size)
			throw std::out_of_range("vector::distance: too big index");
		return (this->_arr[n]);		
	}

    reference front(void)
	{
		return (*_arr);
	}
	const_reference front(void) const
	{
		return (*_arr);
	}
	
    reference back(void)
	{
		return (*(_arr + this->_size - 1));
	}
	
	const_reference back(void) const
	{
		return (*(_arr + this->_size - 1));
	}


	template <typename InputIterator>
	void assign(InputIterator first, InputIterator last)
	{
		if (last < first)
			throw (std::bad_alloc());

		difference_type		i = 0;
		difference_type		length = last - first;

		if (length <= this->_capacity)
		{
			for (;i < length; i++, first++)
				this->_arr[i] = *first;
			for (; i < this->_size; i++)
				this->_arr[i].~T();
			this->_size = length;
		}
		else if (length > this->_capacity)
		{
			this->~vector();
			T* tmp = new T[length];
			for (; i < length; i++, first++)
				tmp[i] = *first;
			this->_size = length;
			this->_capacity = length;
			this->_arr = tmp;
		}
	}

	void assign(int n, T const &val) 
	{
		if (n < 0)
			throw (std::bad_alloc());		
		int i = 0;
		if (n <= this->_capacity)
		{
			for (; i < n; i++)
				this->_arr[i] = val;
			for (; i < this->_size; i++)
				this->_arr[i].~T();
			this->_size = n;
		}		
		else if (n > this->_capacity)
		{
			this->~vector();
			T* tmp = new T[n];
			for (; i < n; i++)
				tmp[i] = val;
			this->_size = n;
			this->_capacity = n;
			this->_arr = tmp;
		}
	}

	void push_back(const value_type& val)
	{
		if (this->_size == this->_capacity)
		{
			if (this->_size * 2 > this->max_size())
				this->reserve(this->max_size());
			if (this->_size == 0)
				this->reserve(1);
			else
				this->reserve(this->_size * 2);
		}
		else if (this->empty())
			this->reserve(1);
		this->_size++;
		_alloc.construct(_arr + this->_size - 1, val);
	}

	void pop_back(void)
	{
		this->_size--;
		_alloc.destroy(_arr + this->_size - 1);
	}


	


	iterator insert(iterator position, const value_type& val)
	{				
		size_type n = position - _arr;
		insert(position, 1, val);
		return (_arr + n);
	}
	
	void    insert(iterator position, size_type n, const value_type& val)
	{
		difference_type	distance = std::distance(begin(), position);
		if (this->_size == 0)
			reserve(n);
		else if (this->_size + n > this->_capacity)
		{
			if (this->_size < n)
				reserve(this->_size + n); 
			else
				reserve(this->_capacity * 2); 
		}
		
		for (difference_type i = this->_size - 1; i >= distance; i--) 
			_alloc.construct(&_arr[i + n], _arr[i]);
		for (size_type i = 0; i < n; i++)
		{
			_alloc.construct(&_arr[distance], val);
			distance++;
		}
		this->_size += n;
	}

	template <typename InputIterator>
	void    insert(iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type = InputIterator()) 
	{
		difference_type	distance = std::distance(begin(), position);
		difference_type range = std::distance(first, last);
		size_type       n = static_cast<size_type>(range);
		if (this->_size == 0) 
			reserve(n);
		else if (this->_size + n > this->_capacity)
		{ 
			if (n > _size)
				reserve(this->_size + n);
			else
				reserve(this->_capacity * 2);
		}
		
		for (difference_type i = this->_size - 1; i >= distance; i--)
			_alloc.construct(&_arr[i + n], _arr[i]);
		for (size_type i = 0; i < n; i++)
		{
			_alloc.construct(&_arr[distance], *first);
			first++;
			distance++;
		}
		this->_size += n;
	}


	iterator erase (iterator position)
	{
		size_type i = position - begin();
		while (i < _size - 1)
		{
			_arr[i] = _arr[i + 1];
			i++;
		}
		_size--;
		return (position);
	}

		iterator erase(iterator first, iterator last)
		{
			size_type i = first - begin();
			iterator final(end());
			_size -= last - first;
			while (last != final)
			{
				_arr[i] = *last;
				i++;
				*last++;
			}
			return (first);
		}

		void swap(vector& x)
		{
			allocator_type tmp_alloc;
			pointer tmp_array;
			size_type tmp_size;
			size_type tmp_capacity;

			tmp_alloc = this->_alloc;
			tmp_array = this->_arr;
			tmp_size = this->_size;
			tmp_capacity = this->_capacity;
			
			this->_alloc = x._alloc;
			this->_arr = x._arr;
			this->_size = x._size;
			this->_capacity = x._capacity;
			
			x._alloc = tmp_alloc;
			x._arr = tmp_array;
			x._size = tmp_size;
			x._capacity = tmp_capacity;
		}




	void clear(void)
	{
		for (size_type i = 0; i < this->_size; i++)
			_alloc.destroy(_arr + i);
		this->_size = 0;
	}

	allocator_type get_allocator(void) const
	{
		return (this->_alloc);
	}
	
public:
	allocator_type	_alloc;
	size_type		_size;
	pointer			_arr;
	size_type		_capacity;


	friend void swap(vector &lhs, vector &rhs)
	{ lhs.swap(rhs); }


};


template <typename T, typename Alloc> 
bool operator ==(const vector<T, Alloc>& x, const vector<T, Alloc>& cp)
{
	return (x.size() == cp.size() && ft::equal(x.begin(), x.end(), cp.begin()));
}

template <typename T, typename Alloc> 
bool operator !=(const vector<T, Alloc>& x, const vector<T, Alloc>& cp)
{
	return (!(x == cp));
}

template <typename T, typename Alloc> 
bool operator <(const vector<T, Alloc>& x, const vector<T, Alloc>& cp)
{
	return (ft::lexicographical_compare(x.begin(), x.end(), cp.begin(), cp.end()));
}

template <typename T, typename Alloc> 
bool operator >(const vector<T, Alloc>& x, const vector<T, Alloc>& cp)
{
	return (cp < x);
}

template <typename T, typename Alloc>
bool operator >=(const vector<T, Alloc>& x, const vector<T, Alloc>& cp)
{
	return (!(x < cp));
}

template <typename T, typename Alloc>
bool operator <=(const vector<T, Alloc>& x, const vector<T, Alloc>& cp)
{
	return (!(cp < x));
}

template <typename T, typename Alloc>
void swap(vector<T, Alloc>& x, vector<T, Alloc>& cp)
{
	x.swap(cp);
}

};


#endif