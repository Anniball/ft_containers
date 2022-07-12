/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utilities.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 14:42:08 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/12 14:03:20 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILITIES_HPP
# define UTILITIES_HPP

# include "../iter/IteratorsTraits.hpp"

namespace ft
{
	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type	_distance(InputIterator first, InputIterator last, random_access_iterator_tag)
	{
		return last - first;
	}

	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type	_distance(InputIterator first, InputIterator last, input_iterator_tag)
	{
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first++ != last)
			n++;
		return n;
	}

	template<class InputIterator>
	typename iterator_traits<InputIterator>::difference_type	distance(InputIterator first, InputIterator last)
	{
		return _distance(first, last, iterator_traits<InputIterator>::iterator_category());
	}

	template <class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		for (first1; first1 != last1; first1++, first2++)
			if (!(*first1 == *first2))
				return false;
		return true;
	}
			  
	//Should implement predicate equal?
	// template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	// bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
	// {}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
	{ 
		for (first1; first1 != last1; ++first1, ++first2)
  		{
    		if (first2 == last2 || *first2 < *first1)
				return false;
    		else if (*first1 < *first2)
				return true;
  		}
  		return (first2 != last2);
	}

	//Should implement compare lexico?
	// template <class InputIterator1, class InputIterator2, class Compare>
	// bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp);
}

#endif