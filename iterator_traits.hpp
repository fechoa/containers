/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a1111 <a1111@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 22:29:12 by a1111             #+#    #+#             */
/*   Updated: 2022/01/31 19:58:24 by a1111            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP
# include <iterator>
namespace ft
{

template <typename Iterator>
class iterator_traits
{
public:
	typedef typename Iterator::difference_type			difference_type;
	typedef typename Iterator::value_type				value_type;
	typedef typename Iterator::pointer					pointer;
	typedef typename Iterator::reference				reference;
	typedef typename Iterator::iterator_category		iterator_category;
};

template <typename T>
class iterator_traits<T*>
{
public:
	typedef std::ptrdiff_t						difference_type;
	typedef T									value_type;
	typedef T*									pointer;
	typedef T&									reference;
	typedef std::random_access_iterator_tag		iterator_category;
};

template <typename T>
class iterator_traits<const T*>
{
public:
	typedef std::ptrdiff_t						difference_type;
	typedef T									value_type;
	typedef T*									pointer;
	typedef T&									reference;
	typedef std::random_access_iterator_tag		iterator_category;
};

};

#endif