/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:42:08 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/08 14:56:31 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_HPP
# define UTILITIES_HPP

#include "../iter/IteratorsTraits.hpp"

namespace ft
{
	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type	distance(InputIterator first, InputIterator last)
	{
		if (iterator_traits<InputIterator>::iterator_category() == random_access_iterator_tag)
			return last - first;
		else
		{
			typename iterator_traits<InputIterator>::difference_type n = 0;
			while (first++ != last)
				n++
		}
	}
}

#endif