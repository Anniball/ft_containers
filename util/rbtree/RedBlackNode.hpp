/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackNode.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:56:12 by ldelmas           #+#    #+#             */
/*   Updated: 2022/08/08 11:10:59 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_NODE_HPP
# define RED_BLACK_NODE_HPP

# include "../Pair.hpp"
# include "../../iter/IteratorsTraits.hpp"
# include "../../iter/TreeIterator.hpp"
# include "RedBlackTree.hpp"

# define RBT_RED true
# define RBT_BLACK false

namespace ft
{
	template <class T, class Alloc, class Compare>
	class red_black_tree;

	template <class T, class Node>
	class tree_iterator;
	
	template <class T, class Compare>
	class red_black_node
	{
		public :
			typedef T													value_type;
			typedef ft::red_black_node<T, Compare>						node_type;
			typedef std::allocator<value_type>							alloc_type;
			typedef Compare												value_compare;
			typedef ft::red_black_tree<T, alloc_type, value_compare>	tree_type;
			typedef node_type*											pointer;
			typedef const node_type*									const_pointer;
			typedef ft::tree_iterator<value_type, node_type>			iterator;
			typedef ft::tree_iterator<const value_type, node_type>		const_iterator;
			typedef ft::reverse_iterator<iterator>						reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type	difference_type;
			typedef size_t												size_type;

		public :
			/*
				CONSTRUCTORS AND DESTRUCTORS
			*/
			red_black_node(tree_type &tree);
			red_black_node(const value_type &val, const tree_type &tree);
			red_black_node(const pointer parent, const tree_type &tree);
			red_black_node(const value_type &val, const pointer left, const pointer right, const pointer parent, tree_type &tree);
			red_black_node(const node_type &src);
			~red_black_node(void);
			
			/*
				GETTERS AND SETTERS
			*/
			value_type			&get_value(void);
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
			pointer				iterate(void) const;
			pointer				reverse_iterate(void) const;
			pointer				get_smallest(void);
			pointer				get_biggest(void);

			/*
				OPERATORS
			*/
			operator			red_black_node<const T, Compare>() const;
			bool				operator==(node_type const &right) const;
			bool				operator!=(node_type const &right) const;
			bool				operator<(node_type const &right) const;
			bool				operator>(node_type const &right) const;
			bool				operator<=(node_type const &right) const;
			bool				operator>=(node_type const &right) const;

		private :
			value_type			_content;
			bool				_color;
			pointer				_left;
			pointer				_right;
			pointer				_parent;
			const tree_type		&_tree;
			const value_compare &_comp;	

			/*
				PRIVATE UTILS
			*/
	};

	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/
	template <class T, class Compare>
	red_black_node<T, Compare>::red_black_node(tree_type &tree) :
	_content(), _color(RBT_RED), _left(nullptr), _right(nullptr), _parent(nullptr), _tree(tree), _comp(tree.get_comp()) {}
	
	template <class T, class Compare>
	red_black_node<T, Compare>::red_black_node(const value_type &val, const tree_type &tree) :
	 _content(val), _color(RBT_RED), _left(nullptr), _right(nullptr), _parent(nullptr), _tree(tree), _comp(tree.get_comp()) {}

	template <class T, class Compare>
	red_black_node<T, Compare>::red_black_node(const pointer parent, const tree_type &tree) :
	_content(), _color(RBT_BLACK), _left(nullptr), _right(nullptr), _parent(parent), _tree(tree), _comp(tree.get_comp()) {}
	
	template <class T, class Compare>
	red_black_node<T, Compare>::red_black_node(const value_type &val, const pointer left, const pointer right, const pointer parent, tree_type &tree) :
	_content(val), _color(RBT_RED), _left(left), _right(right), _parent(parent), _tree(tree), _comp(tree.get_comp()) {}
	
	template <class T, class Compare>
	red_black_node<T, Compare>::red_black_node(const node_type &src) :
	_content(src._content), _color(src._color), _left(src._left), _right(src._right), _parent(src._parent), _tree(src._tree), _comp(src._comp) {}
	
	template <class T, class Compare>
	red_black_node<T, Compare>::~red_black_node(void) {}

	/*
		GETTERS
	*/
	
	template <class T, class Compare>
	typename red_black_node<T, Compare>::value_type	&red_black_node<T, Compare>::get_value(void) {return this->_content;}

	template <class T, class Compare>
	typename red_black_node<T, Compare>::pointer		red_black_node<T, Compare>::get_left(void) const {return this->_left;}
	
	template <class T, class Compare>
	typename red_black_node<T, Compare>::pointer		red_black_node<T, Compare>::get_right(void) const {return this->_right;}
	
	template <class T, class Compare>
	typename red_black_node<T, Compare>::pointer		red_black_node<T, Compare>::get_parent(void) const {return this->_parent;}
	
	template <class T, class Compare>
	typename red_black_node<T, Compare>::pointer		red_black_node<T, Compare>::get_grand_parent(void) const {return this->_parent->_parent;}
	
	template <class T, class Compare>
	typename red_black_node<T, Compare>::pointer		red_black_node<T, Compare>::get_uncle(void) const
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

	template <class T, class Compare>
	bool									red_black_node<T, Compare>::is_red(void) const {return this->_color == RBT_RED;}
	
	template <class T, class Compare>
	bool									red_black_node<T, Compare>::is_black(void) const {return this->_color == RBT_BLACK;}
	
	template <class T, class Compare>
	bool									red_black_node<T, Compare>::is_leaf(void) const {return this->_left == nullptr && this->_right == nullptr;}

	template <class T, class Compare>
	void									red_black_node<T, Compare>::set_value(value_type	const &val) {this->_content = val;}
	
	template <class T, class Compare>
	void									red_black_node<T, Compare>::set_right(pointer node) {this->_right = node;}
	
	template <class T, class Compare>
	void									red_black_node<T, Compare>::set_left(pointer node) {this->_left = node;}
	
	template <class T, class Compare>
	void									red_black_node<T, Compare>::set_parent(pointer node) {this->_parent = node;}


	/*
		UTILS
	*/

	template <class T, class Compare>
	typename red_black_node<T, Compare>::pointer		red_black_node<T, Compare>::iterate(void) const
	{
		return this->_tree.iterate(this);
	}

	template <class T, class Compare>
	typename red_black_node<T, Compare>::pointer		red_black_node<T, Compare>::reverse_iterate(void) const
	{
		return this->_tree.reverse_iterate(this);
	}

	template <class T, class Compare>
	typename red_black_node<T, Compare>::pointer		red_black_node<T, Compare>::get_smallest(void) 
	{
		node_type	*tmp = this;
		while (!tmp->is_leaf() && !tmp->_left->is_leaf())
			tmp = tmp->_left;
		return tmp;
	}
	
	template <class T, class Compare>
	typename red_black_node<T, Compare>::pointer		red_black_node<T, Compare>::get_biggest(void)
	{
		node_type	*tmp = this;
		while (!tmp->is_leaf() && !tmp->_right->is_leaf())
			tmp = tmp->_right;
		return tmp;
	}

	/*
		OPERATORS
	*/

	template <class T, class Compare>
	red_black_node<T, Compare>::operator				red_black_node<const T, Compare>() const
	{
		return red_black_node<const T>(*this);
	}
	
	/*
		RELATIONAL OPERATORS
	*/

	template <class T, class Compare>
	bool												red_black_node<T, Compare>::operator==(node_type const &right) const
	{
		return !this->_comp(this->_content, right._content) && !this->_comp(right._content, this->_content);
	}

	template <class T, class Compare>
	bool												red_black_node<T, Compare>::operator!=(node_type const &right) const
	{
		return !(*this == right);
	}

	template <class T, class Compare>
	bool												red_black_node<T, Compare>::operator<(node_type const &right) const
	{
		return this->_comp(this->_content, right._content);
	}

	template <class T, class Compare>
	bool												red_black_node<T, Compare>::operator<=(node_type const &right) const
	{
		return !(right < *this);
	}

	template <class T, class Compare>
	bool												red_black_node<T, Compare>::operator>(node_type const &right) const
	{
		return (right < *this);
	}

	template <class T, class Compare>
	bool												red_black_node<T, Compare>::operator>=(node_type const &right) const
	{
		return !(*this < right);
	}
}

#endif