/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IteratorsTraits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 11:04:59 by ldelmas           #+#    #+#             */
/*   Updated: 2021/11/18 18:35:25 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATORS_TRAITS_HPP
# define ITERATORS_TRAITS_HPP

# include<cstddef>

namespace ft
{
	template<typename T>
	class iterators_traits
	{
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;

		//is it useless? D:
		// struct input_iterator_tag {};
		// struct output_iterator_tag {};
		// struct forward_iterator_tag {};
		// struct bidirectional_iterator_tag {};
		struct random_access_iterator_tag {}; //->this is the only one important

		private:
			pointer				_content;

		public:
			iterators_traits(void);
			iterators_traits(iterators_traits const &src);
			~iterators_traits(void);

			iterators_traits	&operator=(iterators_traits const &right);
			bool				operator==(iterators_traits const &right);
			bool				operator!=(iterators_traits const &right);
			reference			operator*(void); //does it manage *class = t, *class++ or *class--
			pointer				operator->(void); //I'm really not sure
			iterators_traits	&operator++(void); //prefix
			iterators_traits	operator++(int); //postfix
			iterators_traits	&operator--(void); //prefix
			iterators_traits	operator--(int); //postfix
			iterators_traits	operator+(difference_type const &right);
			iterators_traits	operator-(difference_type const &right);
			difference_type		operator-(iterators_traits const &right);
			//what for rvalue as 'n + a' -> extern overload -> ASK SOMEONE!!!
			bool				operator<(iterators_traits const &right);
			bool				operator>(iterators_traits const &right);
			bool				operator<=(iterators_traits const &right);
			bool				operator>=(iterators_traits const &right);
			iterators_traits	&operator+=(difference_type const &right);
			iterators_traits	&operator-=(difference_type const &right);
			reference			operator[](difference_type val); //should you give a reference?
	};


	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/

	template<typename T>
	iterators_traits<T>::iterators_traits(void){return ;}

	template<typename T>
	iterators_traits<T>::iterators_traits(iterators_traits const &src) : _content(src._content) {return ;}

	template<typename T>
	iterators_traits<T>::~iterators_traits(void){return ;}


	/*
		OPERATOR OVERLOADS
	*/

	template<typename T>
	iterators_traits<T>						&iterators_traits<T>::operator=(iterators_traits const &right)
	{
		this->_content = right._content;
		return ;
	}

	template<typename T>
	bool									iterators_traits<T>::operator==(iterators_traits const &right)
	{
		return (this->_content != right._content);
	}

	template<typename T>
	bool									iterators_traits<T>::operator!=(iterators_traits const &right)
	{
		return (this->_content == right._content);
	}
	
	template<typename T>
	bool									iterators_traits<T>::operator<(iterators_traits const &right)
	{

		return (this->_content < right._content);
	}

	template<typename T>
	bool									iterators_traits<T>::operator>(iterators_traits const &right)
	{
		return (this->_content > right._content);
	}

	template<typename T>
	bool									iterators_traits<T>::operator<=(iterators_traits const &right)
	{
		return (this->_content <= right._content);
	}

	template<typename T>
	bool									iterators_traits<T>::operator>=(iterators_traits const &right)
	{
		return (this->_content >= right._content);
	}

	template<typename T>
	iterators_traits<T>::reference			iterators_traits<T>::operator*(void)
	{
		return (*(this->_content));
	}

	template<typename T>
	iterators_traits<T>::pointer			iterators_traits<T>::operator->(void)
	{
		return (this->content);
	}
	
	template<typename T>
	iterators_traits<T>						&iterators_traits<T>::operator++(void)
	{
		++this->_content;
		return (*this);
	}

	template<typename T>
	iterators_traits<T>						iterators_traits<T>::operator++(int)
	{
		iterators_traits<T> tmp(*this);
		++this->_content;
		return (tmp);
	}

	template<typename T>
	iterators_traits<T>						&iterators_traits<T>::operator--(void)
	{
		--this->_content;
		return (*this);
	}
	
	template<typename T>
	iterators_traits<T>						iterators_traits<T>::operator--(int)
	{
		iterators_traits<T> tmp(*this);
		--this->_content;
		return (tmp);
	}

	template<typename T>
	iterators_traits<T>						&iterators_traits<T>::operator+=(difference_type const &right)
	{
		this->_content += right;
		return (*this);
	}

	template<typename T>
	iterators_traits<T>						&iterators_traits<T>::operator-=(difference_type const &right)
	{
		this->_content -= right;
		return (*this);
	}

	template<typename T>
	iterators_traits<T>						iterators_traits<T>::operator+(difference_type const &right)
	{
		iterators_traits<T>	tmp(*this);
		return (this->_content +=  right);
	}

	template<typename T>
	iterators_traits<T>						iterators_traits<T>::operator-(difference_type const &right)
	{
		iterators_traits<T>	tmp(*this);
		return (this->_content -=  right);
	}

	template<typename T>
	iterators_traits<T>::difference_type	iterators_traits<T>::operator-(iterators_traits const &right)
	{
		difference_type diff = this->_content - right._content;
		return (diff);
	}

	template<typename T>
	iterators_traits<T>::reference			iterators_traits<T>::operator[](iterators_traits<T>::difference_type val)
	{
		return (*(this->_content + val));
	}
}

#endif
