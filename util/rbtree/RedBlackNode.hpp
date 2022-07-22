/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackNode.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:56:12 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/22 15:58:26 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_NODE_HPP
# define RED_BLACK_NODE_HPP

# include "../Pair.hpp"
# include "../../iter/IteratorsTraits.hpp"
# include "RedBlackTree.hpp"

# define RBT_RED true
# define RBT_BLACK false

namespace ft
{
	template <class T >
	class red_black_node
	{
		typedef T													value_type;
		typedef ft::red_black_node<T>								node_type;
		typedef node_type*											pointer;
		typedef const node_type*									const_pointer;
		typedef ft::iterator_traits<value_type>						iterator;
		typedef ft::iterator_traits<const value_type>				const_iterator;
		typedef ft::reverse_iterator<iterator>						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t												size_type;

		public :
			/*
				CONSTRUCTORS AND DESTRUCTORS
			*/
			red_black_node(void);
			red_black_node(const value_type &val, red_black_tree<T> &tree);
			red_black_node(const pointer parent, red_black_tree<T> &tree);
			red_black_node(const value_type &val, const pointer left, const pointer right, const pointer parent, red_black_tree<T> &tree);
			red_black_node(const node_type &src);
			~red_black_node(void);
			
			/*
				GETTERS AND SETTERS
			*/
			value_type			&get_value(void) const;
			pointer				get_left(void) const;
			pointer				get_right(void) const;
			pointer				get_parent(void) const;
			pointer				get_grand_parent(void) const;
			bool				is_red(void) const;
			bool				is_black(void) const;
			bool				is_leaf(void) const;
			pointer				get_uncle(void) const;
			void				set_value(value_type	const &val);
			void				set_right(pointer node);
			void				set_left(pointer node);
			void				set_parent(pointer node);
			
			/*
				PUBLIC UTILS
			*/
			pointer				iterate(void);
			pointer				reverse_iterate(void);
			pointer				get_smallest(void);
			pointer				get_biggest(void);

		private :
			value_type			_content;
			bool				_color;
			pointer				_left;
			pointer				_right;
			pointer				_parent;
			red_black_tree<T>	&_tree;

			/*
				PRIVATE UTILS
			*/
	};

	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/
	template <class T>
	red_black_node<T>::red_black_node(void) : _color(RBT_RED), _left(nullptr), _right(nullptr), _parent(nullptr), _content() {}
	
	template <class T>
	red_black_node<T>::red_black_node(const value_type &val, red_black_tree<T> &tree) :
	_color(RBT_RED), _left(nullptr), _right(nullptr), _parent(nullptr), _content(val), _tree(tree) {}

	template <class T>
	red_black_node<T>::red_black_node(const pointer parent, red_black_tree<T> &tree) :
	_color(RBT_BLACK), _left(nullptr), _right(nullptr), _parent(parent), _content(), _tree(tree) {}
	
	template <class T>
	red_black_node<T>::red_black_node(const value_type &val, const pointer left, const pointer right, const pointer parent, red_black_tree<T> &tree) :
	_color(RBT_RED), _left(left), _right(right), _parent(parent), _content(val), _tree(tree) {}
	
	template <class T>
	red_black_node<T>::red_black_node(const node_type &src) :
	_content(src->_content), _color(src._color), _left(src._left), _right(src._right), _parent(src._parent), _tree(src._tree) {}
	
	template <class T>
	red_black_node<T>::~red_black_node(void) {}

	/*
		GETTERS
	*/
	
	template <class T>
	typename red_black_node<T>::value_type	&red_black_node<T>::get_value(void) const {return this->_content;}

	template <class T>
	typename red_black_node<T>::pointer		red_black_node<T>::get_left(void) const {return this->_left;}
	
	template <class T>
	typename red_black_node<T>::pointer		red_black_node<T>::get_right(void) const {return this->_right;}
	
	template <class T>
	typename red_black_node<T>::pointer		red_black_node<T>::get_parent(void) const {return this->_parent;}
	
	template <class T>
	typename red_black_node<T>::pointer		red_black_node<T>::get_grand_parent(void) const {return this->_parent->_parent;}
	
	template <class T>
	typename red_black_node<T>::pointer		red_black_node<T>::get_uncle(void) const
	{
		pointer	parent = this->_parent;
		pointer	grand_parent = parent->_parent;
		if (!grand_parent)
			return nullptr;
		else if (grand_parent->_left == parent)
			return grand_parent->_right;
		else
			return grand_parent->_left;
	}

	template <class T>
	bool									red_black_node<T>::is_red(void) const {return this->_color == RBT_RED;}
	
	template <class T>
	bool									red_black_node<T>::is_black(void) const {return this->_color == RBT_BLACK;}
	
	template <class T>
	bool									red_black_node<T>::is_leaf(void) const {return this->_left == nullptr && this->right == nullptr;}

	template <class T>
	void									red_black_node<T>::set_value(value_type	const &val) {this->_content = val;}
	
	template <class T>
	void									red_black_node<T>::set_right(pointer node) {this->_right = node;}
	
	template <class T>
	void									red_black_node<T>::set_left(pointer node) {this->_left = node;}
	
	template <class T>
	void									red_black_node<T>::set_parent(pointer node) {this->_parent = node;}


	/*
		UTILS
	*/

	template <class T>
	typename red_black_node<T>::pointer		red_black_node<T>::iterate(void)
	{
		return this->_tree.iterate(this);
	}

	template <class T>
	typename red_black_node<T>::pointer		red_black_node<T>::reverse_iterate(void)
	{
		return this->_tree.reverse_iterate(this);
	}

	template <class T>
	typename red_black_node<T>::pointer		red_black_node<T>::get_smallest(void)
	{
		node_type	*tmp = this;
		while (!tmp->is_leaf())
			tmp = tmp->_left();
		return tmp;
	}
	
	template <class T>
	typename red_black_node<T>::node_type	*red_black_node<T>::get_biggest(void)
	{
		node_type	*tmp = this;
		while (!tmp->is_leaf())
			tmp = tmp->_right();
		return tmp;
	}

	
	/*
		RELATIONAL OPERATORS
	*/

	template <class T>
	bool									operator==(red_black_node<T> const &left, red_black_node<T> const &right)
	{
		return left._content == right._content;
	}

	template <class T>
	bool									operator!=(red_black_node<T> const &left, red_black_node<T> const &right)
	{
		return !(left == right);
	}

	template <class T>
	bool									operator<(red_black_node<T> const &left, red_black_node<T> const &right)
	{
		return left._content < right._content;
	}

	template <class T>
	bool									operator<=(red_black_node<T> const &left, red_black_node<T> const &right)
	{
		return !(right < left);
	}

	template <class T>
	bool									operator>(red_black_node<T> const &left, red_black_node<T> const &right)
	{
		return (right < left);
	}

	template <class T>
	bool									operator>=(red_black_node<T> const &left, red_black_node<T> const &right)
	{
		return !(left < right);
	}
}

#endif