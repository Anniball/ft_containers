/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseIterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 16:17:05 by ldelmas           #+#    #+#             */
/*   Updated: 2022/08/10 15:09:31 by ldelmas          ###   ########.fr       */
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
		public :
			typedef Iterator												iterator_type;
			typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
			typedef typename iterator_traits<Iterator>::value_type			value_type;
			typedef typename iterator_traits<Iterator>::difference_type		difference_type;
			typedef	typename iterator_traits<Iterator>::pointer				pointer;
			typedef typename iterator_traits<Iterator>::reference			reference;

		public:
			reverse_iterator(void);
			explicit reverse_iterator(iterator_type it);
			template <class Iterator2>
			reverse_iterator (const reverse_iterator<Iterator2> &rev_it);
			~reverse_iterator(void);

			operator			reverse_iterator<const Iterator>() const;

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

	template <class Iterator>
	reverse_iterator<Iterator>::reverse_iterator(void) {return ;}
	
	template <class Iterator>
	reverse_iterator<Iterator>::reverse_iterator(iterator_type it) : _base_iterator(it) {return ;}
	
	template <class Iterator1>
	template <class Iterator2>
	reverse_iterator<Iterator1>::reverse_iterator (const reverse_iterator<Iterator2> &rev_it) : _base_iterator(rev_it.base()) {return ;}
	
	template <class Iterator>
	reverse_iterator<Iterator>::~reverse_iterator(void) {return ;}


	/*
		OPERATOR OVERLOADS
	*/

	template <class Iterator>
	reverse_iterator<Iterator>::operator			reverse_iterator<const Iterator>() const
	{
		return this->_base_iterator;
	}

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
		return &(this->operator*());
	}
	
	template <class Iterator>
	typename reverse_iterator<Iterator>::reference			reverse_iterator<Iterator>::operator[](reverse_iterator<Iterator>::difference_type n) const
	{
		return *(this->_base_iterator - n - 1);
	}


	/*
		PUBLIC UTILS
	*/

	template <class Iterator>
	typename reverse_iterator<Iterator>::iterator_type reverse_iterator<Iterator>::base(void) const { return this->_base_iterator; }


	/*
		NON-MEMBER OPERATOR OVERLOADS
		Important note : I thought that using 2 different kind of vectors in comparison operators is a C++11 feature but most
		testers try it. As it is still compatible with C++98 I'll implement it.
	*/

	template <class Iterator1, class Iterator2>
	bool	operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {return (lhs.base() == rhs.base());}
	
	template <class Iterator1, class Iterator2>
	bool	operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {return (lhs.base() != rhs.base());}
	
	template <class Iterator1, class Iterator2>
	bool	operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {return (lhs.base() > rhs.base());}
	
	template <class Iterator1, class Iterator2>
	bool	operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {return (lhs.base() >= rhs.base());}
	
	template <class Iterator1, class Iterator2>
	bool	operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {return (lhs.base() < rhs.base());}
	
	template <class Iterator1, class Iterator2>
	bool	operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {return (lhs.base() <= rhs.base());}

	template <class Iterator>
	reverse_iterator<Iterator>								operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
	{
		return rev_it + n;
	}
	
	template <class Iterator1, class Iterator2>
	typename reverse_iterator<Iterator1>::difference_type	operator-(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
	{
		return (rhs.base() - lhs.base());
	}
}

#endif