/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:35:11 by ldelmas           #+#    #+#             */
/*   Updated: 2022/08/23 16:43:18 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

#include <memory>
# include "../util/Utilities.hpp"

namespace ft
{
	template < class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
	class set
	{
		typedef T																												key_type;
		typedef T																												value_type;
		typedef Compare																											key_compare;
		typedef Alloc																											allocator_type;
		typedef typename allocator_type::reference																				reference;
		typedef typename allocator_type::const_reference																		const_reference;
		typedef typename allocator_type::pointer																				pointer;
		typedef typename allocator_type::const_pointer																			const_pointer;
		typedef	typename ft::tree_iterator<value_type, value_compare, red_black_node<value_type, value_compare> >				iterator;
		typedef typename ft::tree_iterator<const value_type, value_compare, red_black_node<const value_type, value_compare> >	const_iterator;
		typedef typename ft::reverse_iterator<iterator>																			reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>																	const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type																difference_type;
		typedef size_t																											size_t;

	};
}

#endif