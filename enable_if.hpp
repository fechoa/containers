/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enable_if.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: a1111 <a1111@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 18:18:26 by a1111             #+#    #+#             */
/*   Updated: 2022/01/26 10:48:54 by a1111            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENABLE_IF_HPP
# define ENABLE_IF_HPP

namespace ft
{

template <bool B, typename T = void>
struct enable_if {};

template <typename T>
struct enable_if<true, T> 
{
	typedef T type;
};
	
};

#endif