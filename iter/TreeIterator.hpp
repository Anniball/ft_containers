/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeIterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:25:03 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/15 11:33:35 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

# include "../util/rbtree/RedBlackNode.hpp"

namespace ft
{
	template <class T>
	class tree_iterator
	{
		typedef T							value_type;
		typedef T&							reference;
		typedef T*							pointer;
		typedef ptrdiff_t					difference_type;
		typedef red_black_node<T>			node_pointer; //going to be a problem since rbnode are based on <Key, T>
		typedef tree_iterator<T>			iterator;

		public :
			tree_iterator(void);
			tree_iterator(tree_iterator const &src);
			~tree_iterator(void);

			iterator		&operator=(tree_iterator const &right);
			reference		operator*(void);
			pointer			operator->(void);
			iterator		&operator++(void);
			iterator		operator++(int);
			iterator		&operator--(void);
			iterator		operator--(int);
		private :
			node_pointer	_content;
	};

	
	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/

	template <class T>
	tree_iterator<T>::tree_iterator(void) {}
	
	template <class T>
	tree_iterator<T>::tree_iterator(tree_iterator const &src) : _content(src._content) {}
	
	template <class T>
	tree_iterator<T>::~tree_iterator(void) {}


	/*
		OPERATOR OVERLOADS
	*/

	template <class T>
	typename tree_iterator<T>::iterator		&tree_iterator<T>::operator=(tree_iterator const &right)
	{
		this->_content = right._content;
	}
	
	template <class T>
	typename tree_iterator<T>::reference	tree_iterator<T>::operator*(void)
	{
		return this->_content->get_pair();
	}
	
	template <class T>
	typename tree_iterator<T>::pointer		tree_iterator<T>::operator->(void)
	{
		return this->_content->get_pointer();
	}
	
	template <class T>
	typename tree_iterator<T>::iterator		&tree_iterator<T>::operator++(void) 
	{
		this->_content = this->content->iterate();
		return *this;
	}
	
	template <class T>
	typename tree_iterator<T>::iterator		tree_iterator<T>::operator++(int)
	{
		tree_iterator	tmp(*this);
		this->_content = this->content->iterate();
		return tmp;
	}
	
	template <class T>
	typename tree_iterator<T>::iterator		&tree_iterator<T>::operator--(void)
	{
		this->_content = this->content->reverse_iterate();
		return *this;
	}
	
	template <class T>
	typename tree_iterator<T>::iterator		tree_iterator<T>::operator--(int)
	{
		tree_iterator	tmp(*this);
		this->_content = this->content->reverse_iterate();
		return tmp;
	}
}

#endif