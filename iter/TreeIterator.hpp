/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeIterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:25:03 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/29 11:24:16 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

# include "../util/rbtree/RedBlackNode.hpp"
# include "../util/Pair.hpp"

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

	template <class T>
	tree_iterator<T>::tree_iterator(void) {}
	
	template <class T>
	tree_iterator<T>::tree_iterator(iterator const &src) : _content(src._content) {}

	template <class T>
	tree_iterator<T>::tree_iterator(node_pointer ptr) : _content(ptr) {}
	
	template <class T>
	tree_iterator<T>::~tree_iterator(void) {}


	/*
		OPERATOR OVERLOADS
		red_black_node<ft::pair<const int, std::__1::basic_string<char> > > *const
		red_black_node<const ft::pair<const int, std::__1::basic_string<char> > > *
	*/

	// template <class T>
	// tree_iterator<T>::operator				tree_iterator<const T>() const
	// {
	// 	return this->_content;
	// }

	template <class T>
	tree_iterator<T>::operator				node_pointer() const
	{
		return this->_content;
	}

	template <class T>
	typename tree_iterator<T>::iterator		&tree_iterator<T>::operator=(tree_iterator const &right)
	{
		this->_content = right._content;
	}
	
	template <class T>
	typename tree_iterator<T>::reference	tree_iterator<T>::operator*(void) const
	{
		return this->_content->get_value();
	}
	
	//WE GOT A PROBLEM HERE
	template <class T>
	typename tree_iterator<T>::pointer		tree_iterator<T>::operator->(void) const
	{
		return &this->_content->get_value();
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
		UTILS
	*/
	// template <class T>
	// typename tree_iterator<T>::pointer const	&tree_iterator<T>::base(void) const
	// {
	// 	return &this->_content->get_value();
	// }

	/*
		COMPARISON OPERATOR OVERLOADS
	*/


	template <class T>
	bool									operator==(tree_iterator<T> &left, tree_iterator<T> &right)
	{
		return *left == *right;
	}


	template <class T>
	bool									operator!=(tree_iterator<T> &left, tree_iterator<T> &right)
	{
		return !(left == right);
	}
}

#endif