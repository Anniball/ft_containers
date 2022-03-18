/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseIterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:17:05 by ldelmas           #+#    #+#             */
/*   Updated: 2021/11/18 15:26:00 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "IteratorsTraits.hpp"

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
		typedef Iterator										iterator_type;
		typedef iterators_traits<Iterator>::iterator_category	iterator_category;
		typedef iterators_traits<Iterator>::value_type			value_type;
		typedef iterators_traits<Iterator>::difference_type		difference_type;
		typedef	iterators_traits<Iterator>::pointer				pointer;
		typedef iterators_traits<Iterator>::reference			reference;

		public:
			reverse_iterator(void);
			explicit reverse_iterator(iterator_type it);
			template <class Iter>
			reverse_iterator (const reverse_iterator<Iter> &rev_it);
			~reverse_iterator(void);

			reference			operator*(void) const;
			reverse_iterator	operator+(difference_type n) const;
			reverse_iterator	&operator++(void);
			reverse_iterator	operator++(int);
			reverse_iterator	&operator+=(difference_type n);
			reverse_iterator	operator-(difference_type n) const;
			reverse_iterator	&operator--(void);
			reverse_iterator	operator--(int);
			reverse_iterator	&operator-=(difference_type n);
			pointer				operator->(void) const;
			reference			operator[](difference_type n) const;

			iterator_type base(void) const;
	};

	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/



	/*
		OPERATOR OVERLOADS
	*/



	/*
		PUBLIC UTILS
	*/



	/*
		NON-MEMBER FUNCTIONS
	*/

	template <class Iterator>
	bool	operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
	bool	operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
	bool	operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
	bool	operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
	bool	operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
	template <class Iterator>
	bool	operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);

	template <class Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it);
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs);
}

#endif