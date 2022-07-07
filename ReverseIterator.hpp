/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseIterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:17:05 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/07 18:09:50 by lucas            ###   ########.fr       */
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
		typedef Iterator												iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef	typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;

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

			iterator_type 		base(void) const;

		private:
			iterator_type		_base_iterator;
	};

	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/



	/*
		OPERATOR OVERLOADS
	*/

	template <class Iterator>
	typename reverse_iterator<Iterator>::reference	reverse_iterator<Iterator>::operator*(void) const
	{
		reverse_iterator<Iterator>::iterator_type tmp(this->_base_iterator);
		return *(--tmp);
	}

	template <class Iterator>
	reverse_iterator<Iterator>						reverse_iterator<Iterator>::operator+(reverse_iterator<Iterator>::difference_type n) const
	{
		return reverse_iterator<Iterator>(this->_base_iterator - n);
	}

	template <class Iterator>
	reverse_iterator<Iterator>						&reverse_iterator<Iterator>::operator++(void)
	{
		--this->_base_iterator;
		return *this;
	}

	template <class Iterator>
	reverse_iterator<Iterator>						reverse_iterator<Iterator>::operator++(int)
	{
		reverse_iterator<Iterator> tmp(*this);
		--this->_base_iterator;
		return tmp;
	}

	template <class Iterator>
	reverse_iterator<Iterator>						&reverse_iterator<Iterator>::operator+=(reverse_iterator<Iterator>::difference_type n)
	{
		this->_base_iterator -= n;
		return *this;
	}

	template <class Iterator>
	reverse_iterator<Iterator>						reverse_iterator<Iterator>::operator-(reverse_iterator<Iterator>::difference_type n) const
	{
		return reverse_iterator<Iterator>(this->_base_iterator + n);
	}

	template <class Iterator>
	reverse_iterator<Iterator>						&reverse_iterator<Iterator>::operator--(void)
	{
		++this->_base_iterator;
		return *this;
	}

	template <class Iterator>
	reverse_iterator<Iterator>						reverse_iterator<Iterator>::operator--(int)
	{
		reverse_iterator<Iterator> tmp(*this);
		++this->_base_iterator;
		return tmp;
	}

	template <class Iterator>
	reverse_iterator<Iterator>						&reverse_iterator<Iterator>::operator-=(reverse_iterator<Iterator>::difference_type n)
	{
		this->_base_iterator += n;
		return *this;
	}

	template <class Iterator>
	typename reverse_iterator<Iterator>::pointer				reverse_iterator<Iterator>::operator->(void) const
	{
		iterator_type tmp(this->_base_iterator);
		return --tmp;
	}
	
	template <class Iterator>
	typename reverse_iterator<Iterator>::reference			reverse_iterator<Iterator>::operator[](reverse_iterator<Iterator>::difference_type n) const
	{
		return *(this->_base_iterator - n);
	}


	/*
		PUBLIC UTILS
	*/



	/*
		NON-MEMBER FUNCTIONS
	*/

	template <class Iterator>
	bool	operator==(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs._base_iterator == rhs._base_iterator);}
	
	template <class Iterator>
	bool	operator!=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs._base_iterator != rhs._base_iterator);}
	
	template <class Iterator>
	bool	operator<(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs._base_iterator > rhs._base_iterator);}
	
	template <class Iterator>
	bool	operator<=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs._base_iterator >= rhs._base_iterator);}
	
	template <class Iterator>
	bool	operator>(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs._base_iterator < rhs._base_iterator);}
	
	template <class Iterator>
	bool	operator>=(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) {return (lhs._base_iterator <= rhs._base_iterator);}

	template <class Iterator>
	reverse_iterator<Iterator>								operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return (rev_it._base_iterator - n);
	}
	
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type	operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{
		return (lhs._base_iterator - rhs._base_iterator);
	}
}

#endif