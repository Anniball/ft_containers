/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 14:27:02 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/20 12:58:13 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP

# include<cstddef>
# include"IteratorsTraits.hpp"

namespace ft
{
	template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	class iterator
	{
		public :
			typedef Category	iterator_category;
			typedef T			value_type;
			typedef Distance	difference_type;
			typedef Pointer		pointer;
			typedef Reference	reference;
	};
}

#endif