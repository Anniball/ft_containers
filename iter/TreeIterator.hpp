/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeIterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:25:03 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/22 16:59:50 by ldelmas          ###   ########.fr       */
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
		public :
			typedef T							value_type;
			typedef T&							reference;
			typedef T*							pointer;
			typedef ptrdiff_t					difference_type;
			typedef red_black_node<T>			node;
			typedef red_black_node<T>			&node_reference;
			typedef red_black_node<T>			*node_pointer;
			typedef tree_iterator<T>			iterator;
			typedef bidirectional_iterator_tag	iterator_category;

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
		return this->_content->get_value;
	}
	
	//WE GOT A PROBLEM HERE
	template <class T>
	typename tree_iterator<T>::pointer		tree_iterator<T>::operator->(void)
	{
		return this->_content;
	}
	
	template <class T>
	typename tree_iterator<T>::iterator		&tree_iterator<T>::operator++(void) 
	{
		this->_content = this->_content->iterate();
		return *this;
	}
	
	template <class T>
	typename tree_iterator<T>::iterator		tree_iterator<T>::operator++(int)
	{
		tree_iterator	tmp(*this);
		this->_content = this->_content->iterate();
		return tmp;
	}
	
	template <class T>
	typename tree_iterator<T>::iterator		&tree_iterator<T>::operator--(void)
	{
		this->_content = this->_content->reverse_iterate();
		return *this;
	}
	
	template <class T>
	typename tree_iterator<T>::iterator		tree_iterator<T>::operator--(int)
	{
		tree_iterator	tmp(*this);
		this->_content = this->_content->reverse_iterate();
		return tmp;
	}

	/*
		COMPARISON OPERATOR OVERLOADS
	*/


	template <class T>
	bool									operator==(tree_iterator<T> &left, tree_iterator<T> &right)
	{
		return left._content == right._content;
	}


	template <class T>
	bool									operator!=(tree_iterator<T> &left, tree_iterator<T> &right)
	{
		return !(left._content == right._content);
	}
}

#endif