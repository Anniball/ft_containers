/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IteratorsTraits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:04:59 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/07 14:14:57 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_TRAITS_HPP
# define ITERATORS_TRAITS_HPP

# include<cstddef>
# include "Iterator.hpp"

namespace ft
{
	template<class Category, class T, class Distance=ptrdiff_t, class Pointer=T*, class Reference=T&>
	class iterator;
	
	struct input_iterator_tag {};
	struct output_iterator_tag {};
	struct forward_iterator_tag {};
	struct bidirectional_iterator_tag {};
	struct random_access_iterator_tag {}; //->this is the only one important

	template<class Iterator>
	class iterator_traits
	{
		public :
			typedef typename Iterator::iterator_category	iterator_category;
			typedef typename Iterator::value_type			value_type;
			typedef typename Iterator::difference_type		difference_type;
			typedef typename Iterator::pointer				pointer;
			typedef typename Iterator::reference			reference;
	};

	template<class T>
	class iterator_traits<T*>
	{
		public :
			typedef random_access_iterator_tag	iterator_category;
			typedef T							value_type;
			typedef ptrdiff_t					difference_type;
			typedef T*							pointer;
			typedef T&							reference;
	};

	template<class T>
	class iterator_traits<const T*>
	{
		public :
			typedef random_access_iterator_tag	iterator_category;
			typedef T							value_type;
			typedef ptrdiff_t					difference_type;
			typedef T*							pointer;
			typedef T&							reference;
	};

}

#endif
