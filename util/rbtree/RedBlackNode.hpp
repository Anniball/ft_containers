/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackNode.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:56:12 by ldelmas           #+#    #+#             */
/*   Updated: 2022/08/11 11:45:40 by ldelmas          ###   ########.fr       */
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

	template <class T, class Compare, class Node>
	class tree_iterator;
	
	template <class T, class Compare>
	class red_black_node
	{
		public :
			typedef T																	value_type;
			typedef ft::red_black_node<value_type, Compare>								node_type;
			typedef ft::red_black_node<const value_type, Compare>						node_const_type;
			typedef std::allocator<value_type>											alloc_type;
			typedef Compare																value_compare;
			typedef node_type*															pointer;
			typedef const node_type*													const_pointer;
			typedef ft::tree_iterator<value_type, value_compare, node_type>				iterator;
			typedef ft::tree_iterator<const value_type, value_compare, node_const_type>	const_iterator;
			typedef ft::reverse_iterator<iterator>										reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>								const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type					difference_type;
			typedef size_t																size_type;

		public :
			/*
				CONSTRUCTORS AND DESTRUCTORS
			*/
			explicit red_black_node(const pointer ptr = nullptr, const value_compare &comp = value_compare());
			red_black_node(const value_type &val, const pointer ptr = nullptr, const value_compare &comp = value_compare());
			red_black_node(const pointer parent, const pointer ptr = nullptr, const value_compare &comp = value_compare());
			red_black_node(const value_type &val, 
							const pointer left, 
							const pointer right,
							const pointer parent = nullptr,
							const pointer end = nullptr, 
							const value_compare &comp = value_compare());
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
			pointer				get_end(void) const;
			bool				is_red(void) const;
			bool				is_black(void) const;
			bool				is_leaf(void) const;
			pointer				get_uncle(void) const;
			void				set_value(value_type	const &val);
			void				set_right(pointer node);
			void				set_left(pointer node);
			void				set_parent(pointer node);
			void				set_end(pointer ptr);
			
			/*
				PUBLIC UTILS
			*/
			pointer				iterate(void) const;
			pointer				reverse_iterate(void) const;

			/*
				STATIC UTILS
			*/
			static pointer		get_smallest(pointer ptr);
			static pointer		get_biggest(pointer ptr);

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
			pointer				_end; //lead to the end of the tree except for the end node itself that lead to the root
			const value_compare &_comp;
	};

	
	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/
	
	template <class T, class Compare>
	red_black_node<T, Compare>::red_black_node(const pointer ptr, const value_compare &comp) :
	_content(), _color(RBT_RED), _left(nullptr), _right(nullptr), _parent(nullptr), _end(ptr), _comp(comp) {return ;}

	template <class T, class Compare>
	red_black_node<T, Compare>::red_black_node(const value_type &val, const pointer ptr, const value_compare &comp) :
	_content(val), _color(RBT_RED), _left(nullptr), _right(nullptr), _parent(nullptr), _end(ptr), _comp(comp) {return ;}

	template <class T, class Compare>
	red_black_node<T, Compare>::red_black_node(const pointer parent, const pointer ptr, const value_compare &comp) :
	_content(), _color(RBT_BLACK), _left(nullptr), _right(nullptr), _parent(parent), _end(ptr), _comp(comp) {return ;}
	
	template <class T, class Compare>
	red_black_node<T, Compare>::red_black_node(const value_type &val, const pointer left, const pointer right, const pointer parent, const pointer end, const value_compare &comp) :
	_content(val), _color(RBT_RED), _left(left), _right(right), _parent(parent), _end(end), _comp(comp) {return ;}
	
	template <class T, class Compare>
	red_black_node<T, Compare>::red_black_node(const node_type &src) :
	_content(src._content), _color(src._color), _left(src._left), _right(src._right), _parent(src._parent), _end(src._end), _comp(src._comp) {return ;}
	
	template <class T, class Compare>
	red_black_node<T, Compare>::~red_black_node(void) {return ;}

	/*
		GETTERS
	*/
	
	template <class T, class Compare>
	typename red_black_node<T, Compare>::value_type			&red_black_node<T, Compare>::get_value(void) {return this->_content;}

	template <class T, class Compare>
	typename red_black_node<T, Compare>::pointer			red_black_node<T, Compare>::get_left(void) const {return this->_left;}
	
	template <class T, class Compare>
	typename red_black_node<T, Compare>::pointer			red_black_node<T, Compare>::get_right(void) const {return this->_right;}
	
	template <class T, class Compare>
	typename red_black_node<T, Compare>::pointer			red_black_node<T, Compare>::get_parent(void) const {return this->_parent;}
	
	template <class T, class Compare>
	typename red_black_node<T, Compare>::pointer			red_black_node<T, Compare>::get_grand_parent(void) const {return this->_parent->_parent;}

	template <class T, class Compare>
	typename red_black_node<T, Compare>::pointer			red_black_node<T, Compare>::get_end(void) const {return this->_end;}
	
	template <class T, class Compare>
	typename red_black_node<T, Compare>::pointer			red_black_node<T, Compare>::get_uncle(void) const
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
	
	template <class T, class Compare>
	void									red_black_node<T, Compare>::set_end(const pointer ptr) {this->_end = ptr;}


	/*
		UTILS
	*/

	template <class T, class Compare>
	typename red_black_node<T, Compare>::pointer		red_black_node<T, Compare>::iterate(void) const
	{
		const node_type	*k = this;
		node_type		*right = k->get_right();
		node_type		*parent = k->get_parent();
		
		if (right && !right->is_leaf())
			return node_type::get_smallest(right);
		while (parent && parent->get_right() == k)
		{
			k = parent;
			parent = k->get_parent();
		}
		if (parent && parent->get_left() == k)
			return parent;
		return this->_end;
	}

	template <class T, class Compare>
	typename red_black_node<T, Compare>::pointer		red_black_node<T, Compare>::reverse_iterate(void) const
	{
		if (!this->_parent && !this->_left && !this->_right) //meaning this node is the end
			return node_type::get_biggest(this->_end);
		const node_type	*k = this;
		node_type	*left = k->get_left();
		node_type	*parent = k->get_parent();
		if (!left->is_leaf())
			return node_type::get_biggest(left);
		while (parent && parent->get_left() == k)
		{
			k = parent;
			parent = k->get_parent();
		}
		if (parent)
			return parent;
		return this->_end; //probably not that since it's the first
	}


	/*
		STATIC UTILS
	*/

	template <class T, class Compare>
	typename red_black_node<T, Compare>::pointer		red_black_node<T, Compare>::get_smallest(pointer ptr)
	{
		while (!ptr->is_leaf() && !ptr->_left->is_leaf())
			ptr = ptr->_left;
		return ptr;
	}
	
	template <class T, class Compare>
	typename red_black_node<T, Compare>::pointer		red_black_node<T, Compare>::get_biggest(pointer ptr)
	{
		while (!ptr->is_leaf() && !ptr->_right->is_leaf())
			ptr = ptr->_right;
		return ptr;
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