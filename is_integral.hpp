/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_integral.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a1111 <a1111@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:26:25 by a1111             #+#    #+#             */
/*   Updated: 2022/01/25 18:31:24 by a1111            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IS_INTEGRAL_HPP
# define IS_INTEGRAL_HPP

namespace ft
{
template <typename T>
struct is_integral
{
	typedef T value_type;
	static const bool value = false;	
};

template <>
struct is_integral<char>
{
	static const bool value = true;
};

template <>
struct is_integral<int>
{
	static const bool value = true;
};

template <>
struct is_integral<long>
{
	static const bool value = true;
};

template <>
struct is_integral<long long>
{
	static const bool value = true;
};

template <>
struct is_integral<short>
{
	static const bool value = true;
};

template <>
struct is_integral<unsigned char>
{
	static const bool value = true;
};

template <>
struct is_integral<unsigned int>
{
	static const bool value = true;
};

template <>
struct is_integral<unsigned long>
{
	static const bool value = true;
};

template <>
struct is_integral<unsigned long long>
{
	static const bool value = true;
};

template <>
struct is_integral<unsigned short>
{
	static const bool value = true;
};

template <>
struct is_integral<bool>
{
	static const bool value = true;
};

};

#endif