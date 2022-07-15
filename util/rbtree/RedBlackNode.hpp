/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackNode.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:56:12 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/15 11:30:37 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_NODE_HPP
# define RED_BLACK_NODE_HPP

# include "../Pair.hpp"
# include "../../iter/IteratorsTraits.hpp"

# define RBT_RED true
# define RBT_BLACK false

namespace ft
{
	template <class Key, class T>
	class red_black_node
	{
		typedef Key													key_type;
		typedef T													mapped_type;
		typedef ft::pair<const Key, T>								value_type;
		typedef ft::red_black_node<Key, T>							node_type;
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
			red_black_node(const value_type &val);
			red_black_node(const pointer parent);
			red_black_node(const value_type &val, const pointer left, const pointer right, const pointer parent);
			red_black_node(const node_type &src);
			~red_black_node(void);

			/*
				OPERATORS OVERLOADS
			*/
			node_type		&operator++(void);
			node_type		operator++(int);
			node_type		&operator--(void);
			node_type		operator--(int);
			
			/*
				GETTERS AND SETTERS
			*/
			key_type		&get_key(void) const;
			mapped_type		&get_value(void) const;
			value_type		&get_pair(void) const;
			value_type		*get_pointer(void) const;
			pointer			get_left(void) const;
			pointer			get_right(void) const;
			pointer			get_parent(void) const;
			pointer			get_grand_parent(void) const;
			bool			is_red(void) const;
			bool			is_black(void) const;
			bool			is_leaf(void) const;
			pointer			get_uncle(void) const;
			void			set_pair(value_type	const &val);
			void			set_right(pointer node);
			void			set_left(pointer node);
			void			set_parent(pointer node);
			
			/*
				PUBLIC UTILS
			*/
			pointer			iterate(void);
			pointer			reverse_iterate(void);

		private :
			value_type		*_content; //A LOT OF CONSEQUENCES
			bool			_color;
			pointer			_left;
			pointer			_right;
			pointer			_parent;

			/*
				PRIVATE UTILS
			*/
			pointer			_get_smallest(void);
			pointer			_get_biggest(void);
	};

	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/
	template <class Key, class T>
	red_black_node<Key, T>::red_black_node(void) : _color(RBT_RED), _left(nullptr), _right(nullptr), _parent(nullptr)
	{
		this->_content = new value_type();
	}
	
	template <class Key, class T>
	red_black_node<Key, T>::red_black_node(const value_type &val) :
	_color(RBT_RED), _left(nullptr), _right(nullptr), _parent(nullptr)
	{
		this->_content = new value_type(val); 
	}

	template <class Key, class T>
	red_black_node<Key, T>::red_black_node(const pointer parent) :
	_color(RBT_BLACK), _left(nullptr), _right(nullptr), _parent(parent)
	{
		this->_content = new value_type();
	}
	
	template <class Key, class T>
	red_black_node<Key, T>::red_black_node(const value_type &val, const pointer left, const pointer right, const pointer parent) :
	_color(RBT_RED), _left(left), _right(right), _parent(parent)
	{
		this->_content = new value_type(val);
	}
	
	template <class Key, class T>
	red_black_node<Key, T>::red_black_node(const node_type &src) :
	_content(src->_content), _color(src._color), _left(src._left), _right(src._right), _parent(src._parent)
	{
		this->_content = new value_type(*(src->_content));
	}
	
	template <class Key, class T>
	red_black_node<Key, T>::~red_black_node(void)
	{
		delete this->_content;
	}


	/*
		OPERATORS OVERLOADS
	*/
	
	// template <class Key, class T>
	// typename red_black_node<Key, T>::node_type		&red_black_node<Key, T>::operator++(void)
	// {
	// 	this->_iterate();
	// 	return *this;
	// }
	
	// template <class Key, class T>
	// typename red_black_node<Key, T>::node_type		red_black_node<Key, T>::operator++(int)
	// {
	// 	node_type tmp(*this);
	// 	this->_iterate;
	// 	return tmp;
	// }
	
	// template <class Key, class T>
	// typename red_black_node<Key, T>::node_type		&red_black_node<Key, T>::operator--(void)
	// {
	// 	this->_reverse_iterate();
	// 	return *this;
	// }
	
	// template <class Key, class T>
	// typename red_black_node<Key, T>::node_type		red_black_node<Key, T>::operator--(int) 
	// {
	// 	node_type tmp(*this);
	// 	this->_reverse_iterate;
	// 	return tmp;
	// }

	/*
		GETTERS
	*/
	template <class Key, class T>
	typename red_black_node<Key, T>::key_type		&red_black_node<Key, T>::get_key(void) const {return this->_content->first;}
	
	template <class Key, class T>
	typename red_black_node<Key, T>::mapped_type	&red_black_node<Key, T>::get_value(void) const {return this->_content->second;}
	
	template <class Key, class T>
	typename red_black_node<Key, T>::value_type		&red_black_node<Key, T>::get_pair(void) const {return *(this->_content);}
		
	template <class Key, class T>
	typename red_black_node<Key, T>::value_type		*red_black_node<Key, T>::get_pointer(void) const {return this->_content;}

	template <class Key, class T>
	typename red_black_node<Key, T>::pointer		red_black_node<Key, T>::get_left(void) const {return this->_left;}
	
	template <class Key, class T>
	typename red_black_node<Key, T>::pointer		red_black_node<Key, T>::get_right(void) const {return this->_right;}
	
	template <class Key, class T>
	typename red_black_node<Key, T>::pointer		red_black_node<Key, T>::get_parent(void) const {return this->_parent;}
	
	template <class Key, class T>
	typename red_black_node<Key, T>::pointer		red_black_node<Key, T>::get_grand_parent(void) const {return this->_parent->_parent;}
	
	template <class Key, class T>
	typename red_black_node<Key, T>::pointer		red_black_node<Key, T>::get_uncle(void) const
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

	template <class Key, class T>
	bool															red_black_node<Key, T>::is_red(void) const {return this->_color == RBT_RED;}
	
	template <class Key, class T>
	bool															red_black_node<Key, T>::is_black(void) const {return this->_color == RBT_BLACK;}
	
	template <class Key, class T>
	bool															red_black_node<Key, T>::is_leaf(void) const {return this->_left == nullptr && this->right == nullptr;}

	template <class Key, class T>
	void															red_black_node<Key, T>::set_pair(value_type	const &val) {*(this->_content) = val;}
	
	template <class Key, class T>
	void															red_black_node<Key, T>::set_right(pointer node) {this->_right = node;}
	
	template <class Key, class T>
	void															red_black_node<Key, T>::set_left(pointer node) {this->_left = node;}
	
	template <class Key, class T>
	void															red_black_node<Key, T>::set_parent(pointer node) {this->_parent = node;}


	/*
		UTILS
	*/

	template <class Key, class T>
	typename red_black_node<Key, T>::pointer						red_black_node<Key, T>::iterate(void)
	{
		pointer		right = this->get_right();
		pointer		parent = this->get_parent();
		if (!right->is_leaf())
			return this->_get_smallest(right);
		else if (*(parent->get_left()) == *this)
			return parent;
		else if (*(parent->get_right()) == *this)
			return (parent->_iterate());
		return this->_end;
	}

	template <class Key, class T>
	typename red_black_node<Key, T>::pointer						red_black_node<Key, T>::reverse_iterate(void)
	{
		pointer		left = this->get_left();
		pointer		parent = this->get_parent();
		if (!left->is_leaf())
			return this->_get_biggest(left);
		else if (*(parent->get_right()) == *this)
			return parent;
		else if (*(parent->get_left()) == *this)
			return (parent->_iterate());
		return this->_end;
	}

	template <class Key, class T>
	typename red_black_node<Key, T>::pointer						red_black_node<Key, T>::_get_smallest(void)
	{
		node_type	*tmp = this;
		while (!tmp->is_leaf())
			tmp = tmp->_left();
		return tmp;
	}
	
	template <class Key, class T>
	typename red_black_node<Key, T>::node_type		*red_black_node<Key, T>::_get_biggest(void)
	{
		node_type	*tmp = this;
		while (!tmp->is_leaf())
			tmp = tmp->_right();
		return tmp;
	}

	
	/*
		RELATIONAL OPERATORS
	*/

}

#endif