/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeIterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:25:03 by ldelmas           #+#    #+#             */
/*   Updated: 2022/08/10 14:21:11 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

# include "../util/rbtree/RedBlackNode.hpp"
# include "../util/Pair.hpp"

namespace ft
{
	template <class T, class Compare = ft::less<T>, class Node = red_black_node<T, Compare> >
	class tree_iterator
	{
		public :
			typedef T								value_type;
			typedef T&								reference;
			typedef T*								pointer;
			typedef ptrdiff_t						difference_type;
			typedef Node							&node_reference;
			typedef Node							*node_pointer;
			typedef tree_iterator<T, Compare, Node>	iterator;
			typedef bidirectional_iterator_tag		iterator_category;

		public :
			tree_iterator(void);
			tree_iterator(tree_iterator const &src);
			tree_iterator(node_pointer ptr);
			~tree_iterator(void);

			operator			tree_iterator<const T, Compare, red_black_node<const T, Compare> >() const;
			operator			node_pointer() const;

			iterator			&operator=(tree_iterator const &right);
			reference			operator*(void) const;
			pointer				operator->(void) const;
			iterator			&operator++(void);
			iterator			operator++(int);
			iterator			&operator--(void);
			iterator			operator--(int);
			
			pointer const		&base(void) const;

		private :
			node_pointer		_content;
	};

	
	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/

	template <class T, class Compare, class Node>
	tree_iterator<T, Compare, Node>::tree_iterator(void) {}
	
	template <class T, class Compare, class Node>
	tree_iterator<T, Compare, Node>::tree_iterator(tree_iterator const &src) : _content(src._content) {}

	template <class T, class Compare, class Node>
	tree_iterator<T, Compare, Node>::tree_iterator(node_pointer ptr) : _content(ptr) {}
	
	template <class T, class Compare, class Node>
	tree_iterator<T, Compare, Node>::~tree_iterator(void) {}


	/*
		OPERATOR OVERLOADS
	*/

	template <class T, class Compare, class Node>
	tree_iterator<T, Compare, Node>::operator				tree_iterator<const T, Compare, red_black_node<const T, Compare> >() const
	{
		const iterator &it = *this;
		return reinterpret_cast<const tree_iterator<const T, Compare, red_black_node<const T, Compare> >& >(it);
	}

	template <class T, class Compare, class Node>
	tree_iterator<T, Compare, Node>::operator				node_pointer() const
	{
		return this->_content;
	}

	template <class T, class Compare, class Node>
	typename tree_iterator<T, Compare, Node>::iterator		&tree_iterator<T, Compare, Node>::operator=(tree_iterator const &right)
	{
		this->_content = right._content;
		return *this;
	}
	
	template <class T, class Compare, class Node>
	typename tree_iterator<T, Compare, Node>::reference	tree_iterator<T, Compare, Node>::operator*(void) const
	{
		return this->_content->get_value();
	}
	
	template <class T, class Compare, class Node>
	typename tree_iterator<T, Compare, Node>::pointer		tree_iterator<T, Compare, Node>::operator->(void) const
	{
		return &this->_content->get_value();
	}

	template <class T, class Compare, class Node>
	typename tree_iterator<T, Compare, Node>::iterator		&tree_iterator<T, Compare, Node>::operator++(void) 
	{
		this->_content = this->_content->iterate();
		return *this;
	}
	
	template <class T, class Compare, class Node>
	typename tree_iterator<T, Compare, Node>::iterator		tree_iterator<T, Compare, Node>::operator++(int)
	{
		tree_iterator	tmp(*this);
		this->_content = this->_content->iterate();
		return tmp;
	}
	
	template <class T, class Compare, class Node>
	typename tree_iterator<T, Compare, Node>::iterator		&tree_iterator<T, Compare, Node>::operator--(void)
	{
		this->_content = this->_content->reverse_iterate();
		return *this;
	}
	
	template <class T, class Compare, class Node>
	typename tree_iterator<T, Compare, Node>::iterator		tree_iterator<T, Compare, Node>::operator--(int)
	{
		tree_iterator	tmp(*this);
		this->_content = this->_content->reverse_iterate();
		return tmp;
	}


	/*
		PUBLIC METHODS
	*/

	/*
'const ft::tree_iterator<ft::pair<const char, int>, ft::map<char, int, ft::less<char>, std::__1::allocator<ft::pair<const char, int> > >::value_compare, ft::red_black_node<ft::pair<const char, int>, ft::map<char, int, ft::less<char>, std::__1::allocator<ft::pair<const char, int> > >::value_compare> >::node_pointer'
	aka
'ft::red_black_node<ft::pair<const char, int>, ft::map<char, int, ft::less<char>, std::__1::allocator<ft::pair<const char, int> > >::value_compare> *const')
	could not bind to an rvalue of type
'ft::red_black_node<ft::pair<const char, int>, ft::map<char, int, ft::less<char>, std::__1::allocator<ft::pair<const char, int> > >::value_compare>::value_type *'
	aka
'ft::pair<const char, int> *'
	*/

	template <class T, class Compare, class Node>
	typename tree_iterator<T, Compare, Node>::pointer const	&tree_iterator<T, Compare, Node>::base(void) const
	{
		return &(this->_content->get_value());
	}


	/*
		COMPARISON OPERATOR OVERLOADS
	*/

	template <class T1, class T2, class Compare, class Node1, class Node2>
	bool									operator==(const tree_iterator<T1, Compare, Node1> &left, const tree_iterator<T2, Compare, Node2> &right)
	{
		return *left == *right;
	}

	template <class T1, class T2, class Compare, class Node1, class Node2>
	bool									operator!=(const tree_iterator<T1, Compare, Node1> &left, const tree_iterator<T2, Compare, Node2> &right)
	{
		return !(left == right);
	}
}

#endif