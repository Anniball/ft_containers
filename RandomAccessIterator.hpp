/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomAccessIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 13:42:10 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/07 14:06:28 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			~random_access_iterator(void);

			random_access_iterator	&operator=(random_access_iterator const &right);
			bool					operator==(random_access_iterator const &right);
			bool					operator!=(random_access_iterator const &right);
			reference				operator*(void); //does it manage *class = t, *class++ or *class--
			pointer					operator->(void); //I'm really not sure
			random_access_iterator	&operator++(void); //prefix
			random_access_iterator	operator++(int); //postfix
			random_access_iterator	&operator--(void); //prefix
			random_access_iterator	operator--(int); //postfix
			random_access_iterator	operator+(difference_type const &right);
			random_access_iterator	operator-(difference_type const &right);
			difference_type			operator-(random_access_iterator const &right);
			//what for rvalue as 'n + a' -> extern overload -> ASK SOMEONE!!!
			bool					operator<(random_access_iterator const &right);
			bool					operator>(random_access_iterator const &right);
			bool					operator<=(random_access_iterator const &right);
			bool					operator>=(random_access_iterator const &right);
			random_access_iterator	&operator+=(difference_type const &right);
			random_access_iterator	&operator-=(difference_type const &right);
			reference				operator[](difference_type val); //should you give a reference?
		
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
	random_access_iterator<T>::~random_access_iterator(void){return ;}


	/*
		OPERATOR OVERLOADS
	*/

	template<typename T>
	random_access_iterator<T>						&random_access_iterator<T>::operator=(random_access_iterator const &right)
	{
		this->_content = right._content;
		return ;
	}

	template<typename T>
	bool									random_access_iterator<T>::operator==(random_access_iterator const &right)
	{
		return (this->_content != right._content);
	}

	template<typename T>
	bool									random_access_iterator<T>::operator!=(random_access_iterator const &right)
	{
		return (this->_content == right._content);
	}
	
	template<typename T>
	bool									random_access_iterator<T>::operator<(random_access_iterator const &right)
	{

		return (this->_content < right._content);
	}

	template<typename T>
	bool									random_access_iterator<T>::operator>(random_access_iterator const &right)
	{
		return (this->_content > right._content);
	}

	template<typename T>
	bool									random_access_iterator<T>::operator<=(random_access_iterator const &right)
	{
		return (this->_content <= right._content);
	}

	template<typename T>
	bool									random_access_iterator<T>::operator>=(random_access_iterator const &right)
	{
		return (this->_content >= right._content);
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
	random_access_iterator<T>						&random_access_iterator<T>::operator+=(difference_type const &right)
	{
		this->_content += right;
		return (*this);
	}

	template<typename T>
	random_access_iterator<T>						&random_access_iterator<T>::operator-=(difference_type const &right)
	{
		this->_content -= right;
		return (*this);
	}

	template<typename T>
	random_access_iterator<T>						random_access_iterator<T>::operator+(difference_type const &right)
	{
		random_access_iterator<T>	tmp(*this);
		return (this->_content +=  right);
	}

	template<typename T>
	random_access_iterator<T>						random_access_iterator<T>::operator-(difference_type const &right)
	{
		random_access_iterator<T>	tmp(*this);
		return (this->_content -=  right);
	}

	template<typename T>
	typename	random_access_iterator<T>::difference_type	random_access_iterator<T>::operator-(random_access_iterator const &right)
	{
		difference_type diff = this->_content - right._content;
		return (diff);
	}

	template<typename T>
	typename	random_access_iterator<T>::reference			random_access_iterator<T>::operator[](random_access_iterator<T>::difference_type val)
	{
		return (*(this->_content + val));
	}
}