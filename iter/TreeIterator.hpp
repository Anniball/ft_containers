/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeIterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:25:03 by ldelmas           #+#    #+#             */
/*   Updated: 2022/08/03 14:12:54 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

# include "../util/rbtree/RedBlackNode.hpp"
# include "../util/Pair.hpp"

namespace ft
{
	template <class T, class Node = red_black_node<T> >
	class tree_iterator
	{
		public :
			typedef T							value_type;
			typedef T&							reference;
			typedef T*							pointer;
			typedef ptrdiff_t					difference_type;
			typedef Node						&node_reference;
			typedef Node						*node_pointer;
			typedef tree_iterator<T, Node>		iterator;
			typedef bidirectional_iterator_tag	iterator_category;

		public :
			tree_iterator(void);
			tree_iterator(tree_iterator const &src);
			tree_iterator(node_pointer ptr);
			~tree_iterator(void);

			// pointer const	&base(void) const;
			operator		tree_iterator<const T>() const;
			operator		node_pointer() const;

			iterator		&operator=(tree_iterator const &right);
			reference		operator*(void) const;
			pointer			operator->(void) const;
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

	template <class T, class Node>
	tree_iterator<T, Node>::tree_iterator(void) {}
	
	template <class T, class Node>
	tree_iterator<T, Node>::tree_iterator(iterator const &src) : _content(src._content) {}

	template <class T, class Node>
	tree_iterator<T, Node>::tree_iterator(node_pointer ptr) : _content(ptr) {}
	
	template <class T, class Node>
	tree_iterator<T, Node>::~tree_iterator(void) {}


	/*
		OPERATOR OVERLOADS
	*/

	template <class T, class Node>
	tree_iterator<T, Node>::operator				tree_iterator<const T>() const
	{
		return this->_content;
	}

	template <class T, class Node>
	tree_iterator<T, Node>::operator				node_pointer() const
	{
		return this->_content;
	}

	template <class T, class Node>
	typename tree_iterator<T, Node>::iterator		&tree_iterator<T, Node>::operator=(tree_iterator const &right)
	{
		this->_content = right._content;
		return *this;
	}
	
	template <class T, class Node>
	typename tree_iterator<T, Node>::reference	tree_iterator<T, Node>::operator*(void) const
	{
		return this->_content->get_value();
	}
	
	template <class T, class Node>
	typename tree_iterator<T, Node>::pointer		tree_iterator<T, Node>::operator->(void) const
	{
		return &this->_content->get_value();
	}
	
	template <class T, class Node>
	typename tree_iterator<T, Node>::iterator		&tree_iterator<T, Node>::operator++(void) 
	{
		this->_content = this->_content->iterate();
		return *this;
	}
	
	template <class T, class Node>
	typename tree_iterator<T, Node>::iterator		tree_iterator<T, Node>::operator++(int)
	{
		tree_iterator	tmp(*this);
		this->_content = this->_content->iterate();
		return tmp;
	}
	
	template <class T, class Node>
	typename tree_iterator<T, Node>::iterator		&tree_iterator<T, Node>::operator--(void)
	{
		this->_content = this->_content->reverse_iterate();
		return *this;
	}
	
	template <class T, class Node>
	typename tree_iterator<T, Node>::iterator		tree_iterator<T, Node>::operator--(int)
	{
		tree_iterator	tmp(*this);
		this->_content = this->_content->reverse_iterate();
		return tmp;
	}

	/*
		UTILS
	*/
	// template <class T, class Node>
	// typename tree_iterator<T, Node>::pointer const	&tree_iterator<T, Node>::base(void) const
	// {
	// 	return &this->_content->get_value();
	// }

	/*
		COMPARISON OPERATOR OVERLOADS
	*/


	template <class T, class Node>
	bool									operator==(tree_iterator<T, Node> &left, tree_iterator<T, Node> &right)
	{
		return *left == *right;
	}


	template <class T, class Node>
	bool									operator!=(tree_iterator<T, Node> &left, tree_iterator<T, Node> &right)
	{
		return !(left == right);
	}
}

#endif