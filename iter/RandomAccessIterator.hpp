/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomAccessIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:42:10 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/20 11:21:21 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

#include "IteratorsTraits.hpp"

namespace ft
{
	template<typename T>
	class random_access_iterator
	{
		public:
			typedef typename	ft::iterator<random_access_iterator_tag, T>::difference_type	difference_type;
			typedef typename	ft::iterator<random_access_iterator_tag, T>::value_type			value_type;
			typedef typename	ft::iterator<random_access_iterator_tag, T>::pointer			pointer;
			typedef typename	ft::iterator<random_access_iterator_tag, T>::reference			reference;
			typedef typename	ft::iterator<random_access_iterator_tag, T>::iterator_category	iterator_category;

			random_access_iterator(void);
			random_access_iterator(random_access_iterator const &src);
			random_access_iterator(pointer ptr);
			~random_access_iterator(void);

			random_access_iterator	&operator=(random_access_iterator const &right);
			reference				operator*(void);
			pointer					operator->(void);
			random_access_iterator	&operator++(void); //prefix
			random_access_iterator	operator++(int); //postfix
			random_access_iterator	&operator--(void); //prefix
			random_access_iterator	operator--(int); //postfix
			random_access_iterator	operator+(difference_type right);
			random_access_iterator	operator-(difference_type right);
			random_access_iterator	&operator+=(difference_type right);
			random_access_iterator	&operator-=(difference_type right);
			reference				operator[](difference_type val);

			pointer const			&base(void) const;

		private:
			pointer				_content;
	};


	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/

	template<typename T>
	random_access_iterator<T>::random_access_iterator(void){return ;}

	template<typename T>
	random_access_iterator<T>::random_access_iterator(random_access_iterator const &src) : _content(src._content) {return ;}


	template<typename T>
	random_access_iterator<T>::random_access_iterator(pointer ptr) : _content(ptr) {return ;}

	template<typename T>
	random_access_iterator<T>::~random_access_iterator(void){return ;}


	/*
		OPERATOR OVERLOADS
	*/

	template<typename T>
	random_access_iterator<T>						&random_access_iterator<T>::operator=(random_access_iterator const &right)
	{
		this->_content = right._content;
		return *this;
	}

	template<typename T>
	typename random_access_iterator<T>::reference	random_access_iterator<T>::operator*(void)
	{
		return (*(this->_content));
	}

	template<typename T>
	typename random_access_iterator<T>::pointer	random_access_iterator<T>::operator->(void)
	{
		return (this->content);
	}
	
	template<typename T>
	random_access_iterator<T>						&random_access_iterator<T>::operator++(void)
	{
		++this->_content;
		return (*this);
	}

	template<typename T>
	random_access_iterator<T>						random_access_iterator<T>::operator++(int)
	{
		random_access_iterator<T> tmp(*this);
		++this->_content;
		return (tmp);
	}

	template<typename T>
	random_access_iterator<T>						&random_access_iterator<T>::operator--(void)
	{
		--this->_content;
		return (*this);
	}
	
	template<typename T>
	random_access_iterator<T>						random_access_iterator<T>::operator--(int)
	{
		random_access_iterator<T> tmp(*this);
		--this->_content;
		return (tmp);
	}

	template<typename T>
	random_access_iterator<T>						&random_access_iterator<T>::operator+=(difference_type right)
	{
		this->_content += right;
		return (*this);
	}

	template<typename T>
	random_access_iterator<T>						&random_access_iterator<T>::operator-=(difference_type right)
	{
		this->_content -= right;
		return (*this);
	}

	template<typename T>
	random_access_iterator<T>						random_access_iterator<T>::operator+(difference_type right)
	{
		return (random_access_iterator<T>(this->_content +  right));
	}

	template<typename T>
	random_access_iterator<T>						random_access_iterator<T>::operator-(difference_type right)
	{
		return (random_access_iterator<T>(this->_content - right));
	}

	template<typename T>
	typename	random_access_iterator<T>::reference	random_access_iterator<T>::operator[](random_access_iterator<T>::difference_type val)
	{
		return (*(this->_content + val));
	}


	/*
		PUBLIC METHOD
	*/

	template<typename T>
	typename random_access_iterator<T>::pointer const	&random_access_iterator<T>::base(void) const
	{
		return this->_content;
	}

	/*
		NON MEMBER OPERATOR OVERLOADS
	*/

	template<class Iterator1, class Iterator2>
	bool	operator==(random_access_iterator<Iterator1> const &left, random_access_iterator<Iterator2> const &right)
	{
		return (left.base() == right.base());
	}

	template<class Iterator1, class Iterator2>
	bool	operator!=(random_access_iterator<Iterator1> const &left, random_access_iterator<Iterator2> const &right)
	{
		return (left.base() != right.base());
	}
	
	template<class Iterator1, class Iterator2>
	bool	operator<(random_access_iterator<Iterator1> const &left, random_access_iterator<Iterator2> const &right)
	{

		return (left.base() < right.base());
	}

	template<class Iterator1, class Iterator2>
	bool	operator>(random_access_iterator<Iterator1> const &left, random_access_iterator<Iterator2> const &right)
	{
		return (left.base() > right.base());
	}

	template<class Iterator1, class Iterator2>
	bool	operator<=(random_access_iterator<Iterator1> const &left, random_access_iterator<Iterator2> const &right)
	{
		return (left.base() <= right.base());
	}

	template<class Iterator1, class Iterator2>
	bool	operator>=(random_access_iterator<Iterator1> const &left, random_access_iterator<Iterator2> const &right)
	{
		return (left.base() >= right.base());
	}

	template<class Iterator>
	random_access_iterator<Iterator>	operator+(typename random_access_iterator<Iterator>::difference_type left, random_access_iterator<Iterator> const &right)
	{
		return (left + right);
	}

	template<class Iterator1, class Iterator2>
	typename	random_access_iterator<Iterator1>::difference_type	operator-(random_access_iterator<Iterator2> const &left, random_access_iterator<Iterator1> const &right)
	{
		return (left.base() - right.base());
	}
}

#endif