/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a1111 <a1111@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/15 11:21:38 by a1111             #+#    #+#             */
/*   Updated: 2022/01/29 13:16:03 by a1111            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"
# include "iterator.hpp"
# include <iostream>

namespace ft
{
	
template < typename T, typename Container = ft::vector<T> >
class stack
{

public:
	typedef Container		container_type;
	typedef T				value_type;
	typedef std::size_t		size_type;


	explicit stack(const container_type& cont = container_type()): c(cont) {}
	
	stack& operator=(const stack& other)
	{
		if (this != &other)
			c = other.c;
		return (*this);
	}

	value_type& top(void)
	{
		return (this->c.back());
	}
	const value_type& top(void) const
	{
		return (this->c.back());
	}
	
	bool empty(void) const
	{
		return (this->c.empty());
	}
	size_type size(void) const
	{
		return (this->c.size());
	}

	void push(const value_type& value)
	{
		this->c.push_back(value);
	}
	void pop(void)
	{
		this->c.pop_back();
	}

	friend bool operator==(const stack<value_type,container_type>& lhs, const stack<value_type,container_type>& rhs)
	{
		return (lhs.c == rhs.c);
	}
	friend bool operator!= (const stack<value_type,container_type>& lhs, const stack<value_type,container_type>& rhs)
	{
		return (lhs.c != rhs.c);
	}
	friend bool operator<  (const stack<value_type,container_type>& lhs, const stack<value_type,container_type>& rhs)
	{
		return (lhs.c < rhs.c);
	}
	friend bool operator<= (const stack<value_type,container_type>& lhs, const stack<value_type,container_type>& rhs)
	{
		return (lhs.c <= rhs.c);
	}
	friend bool operator>  (const stack<value_type,container_type>& lhs, const stack<value_type,container_type>& rhs)
	{
		return (lhs.c > rhs.c);
	}
	friend bool operator>=  (const stack<value_type,container_type>& lhs, const stack<value_type,container_type>& rhs)
	{
		return (lhs.c >= rhs.c);
	}
	
protected:
	container_type	c;
};

};



#endif