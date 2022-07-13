/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:02:21 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/13 13:53:39 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include "Pair.hpp"
# include "../iter/IteratorsTraits.hpp"

# define RBT_RED true
# define RBT_BLACK false

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class red_black_node
	{
		typedef Key													key_type;
		typedef T													mapped_type;
		typedef ft::pair<const Key, T>								value_type;
		typedef ft::red_black_node<Key, T, Compare, Alloc>			node_type;
		typedef Compare												key_compare;
		typedef Alloc												allocator_type;
		typedef	typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
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
				GETTERS AND SETTERS
			*/
			key_type		&get_key(void) const;
			mapped_type		&get_value(void) const;
			value_type		&get_pair(void) const;
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

		private :
			value_type				&_content;
			bool					_color;
			pointer					_left;
			pointer					_right;
			pointer					_parent;
	};

	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/
	template <class Key, class T, class Compare, class Alloc>
	red_black_node<Key, T, Compare, Alloc>::red_black_node(void) :
	_content(value_type()), _color(RBT_RED), _left(nullptr), _right(nullptr), _parent(nullptr) {}
	
	template <class Key, class T, class Compare, class Alloc>
	red_black_node<Key, T, Compare, Alloc>::red_black_node(const value_type &val) :
	_content(val), _color(RBT_RED), _left(nullptr), _right(nullptr), _parent(nullptr) {}

	template <class Key, class T, class Compare, class Alloc>
	red_black_node<Key, T, Compare, Alloc>::red_black_node(const pointer parent) :
	_content(value_type()), _color(RBT_BLACK), _left(nullptr), _right(nullptr), _parent(parent) {}
	
	template <class Key, class T, class Compare, class Alloc>
	red_black_node<Key, T, Compare, Alloc>::red_black_node(const value_type &val, const pointer left, const pointer right, const pointer parent) :
	_content(val), _color(RBT_RED), _left(left), _right(right), _parent(parent) {}
	
	template <class Key, class T, class Compare, class Alloc>
	red_black_node<Key, T, Compare, Alloc>::red_black_node(const node_type &src) :
	_content(src._content), _color(src._color), _left(src._left), _right(src._right), _parent(src._parent) {}
	
	template <class Key, class T, class Compare, class Alloc>
	red_black_node<Key, T, Compare, Alloc>::~red_black_node(void) {}


	/*
		GETTERS
	*/
	template <class Key, class T, class Compare, class Alloc>
	typename red_black_node<Key, T, Compare, Alloc>::key_type		&red_black_node<Key, T, Compare, Alloc>::get_key(void) const {return this->_content.first;}
	
	template <class Key, class T, class Compare, class Alloc>
	typename red_black_node<Key, T, Compare, Alloc>::mapped_type	&red_black_node<Key, T, Compare, Alloc>::get_value(void) const {return this->_content.second;}
	
	template <class Key, class T, class Compare, class Alloc>
	typename red_black_node<Key, T, Compare, Alloc>::value_type		&red_black_node<Key, T, Compare, Alloc>::get_pair(void) const {return this->_content;}
	
	template <class Key, class T, class Compare, class Alloc>
	typename red_black_node<Key, T, Compare, Alloc>::pointer		red_black_node<Key, T, Compare, Alloc>::get_left(void) const {return this->_left;}
	
	template <class Key, class T, class Compare, class Alloc>
	typename red_black_node<Key, T, Compare, Alloc>::pointer		red_black_node<Key, T, Compare, Alloc>::get_right(void) const {return this->_right;}
	
	template <class Key, class T, class Compare, class Alloc>
	typename red_black_node<Key, T, Compare, Alloc>::pointer		red_black_node<Key, T, Compare, Alloc>::get_parent(void) const {return this->_parent;}
	
	template <class Key, class T, class Compare, class Alloc>
	typename red_black_node<Key, T, Compare, Alloc>::pointer		red_black_node<Key, T, Compare, Alloc>::get_grand_parent(void) const {return this->_parent->_parent;}
	
	template <class Key, class T, class Compare, class Alloc>
	typename red_black_node<Key, T, Compare, Alloc>::pointer		red_black_node<Key, T, Compare, Alloc>::get_uncle(void) const
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

	template <class Key, class T, class Compare, class Alloc>
	bool															red_black_node<Key, T, Compare, Alloc>::is_red(void) const {return this->_color == RBT_RED;}
	
	template <class Key, class T, class Compare, class Alloc>
	bool															red_black_node<Key, T, Compare, Alloc>::is_black(void) const {return this->_color == RBT_BLACK;}
	
	template <class Key, class T, class Compare, class Alloc>
	bool															red_black_node<Key, T, Compare, Alloc>::is_leaf(void) const {return this->_left == nullptr && this->right == nullptr;}

	template <class Key, class T, class Compare, class Alloc>
	void															red_black_node<Key, T, Compare, Alloc>::set_pair(value_type	const &val) {this->_content = val;}
	
	template <class Key, class T, class Compare, class Alloc>
	void															red_black_node<Key, T, Compare, Alloc>::set_right(pointer node) {this->_right = node;}
	
	template <class Key, class T, class Compare, class Alloc>
	void															red_black_node<Key, T, Compare, Alloc>::set_left(pointer node) {this->_left = node;}
	
	template <class Key, class T, class Compare, class Alloc>
	void															red_black_node<Key, T, Compare, Alloc>::set_parent(pointer node) {this->_parent = node;}

	/*
		RELATIONAL OPERATORS
	*/

	

	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class red_black_tree
	{
		typedef Key													key_type;
		typedef T													mapped_type;
		typedef ft::pair<const Key, T>								value_type;
		typedef ft::red_black_node<Key, T, Compare, Alloc>			node_type;
		typedef ft::red_black_tree<Key, T, Compare, Alloc>			tree_type;
		typedef Compare												key_compare;
		typedef Alloc												allocator_type;
		typedef	typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
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
			red_black_tree();
			red_black_tree(const value_type &val);
			red_black_tree(const node_type &val);
			red_black_tree(const tree_type &src);
			~red_black_tree();

			/*
				MEMBER METHODS
			*/
			node_type	*search(key_type &key);
			node_type	*insert(value_type &val);
			void		erase(key_type &val);

		private :
			node_type	*_root;

			/*
				PRIVATE UTILS METHOD
			*/
			node_type	*_create_leaf(const node_type *parent);
			void		_replace_node(node_type *parent, node_type *z, node_type *replacer);
			node_type	*_get_biggest(node_type *subroot);
			node_type	*_get_smallest(node_type *subroot);
	};
	
	
	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/
	template <class Key, class T, class Compare, class Alloc>
	red_black_tree<Key, T, Compare, Alloc>::red_black_tree() : _root() {}
	
	template <class Key, class T, class Compare, class Alloc>
	red_black_tree<Key, T, Compare, Alloc>::red_black_tree(const value_type &val) : _root(val) {}
	
	template <class Key, class T, class Compare, class Alloc>
	red_black_tree<Key, T, Compare, Alloc>::red_black_tree(const node_type &node) : _root(node) {}
	
	// template <class Key, class T, class Compare, class Alloc>
	// red_black_tree(const &tree_type src) {} //LET'S GO BACK ON IT LATER
	
	// template <class Key, class T, class Compare, class Alloc>
	// ~red_black_tree() {} //LET'S GO BACK ON IT LATER

	/*
		MEMBER METHODS
	*/
	
	template <class Key, class T, class Compare, class Alloc>
	typename red_black_tree<Key, T, Compare, Alloc>::node_type	*red_black_tree<Key, T, Compare, Alloc>::search(key_type &key)
	{
		node_type	*z = this->_root;
		key_type	&z_key = z->get_key();
		while (z_key != key)
		{
			if (z->is_leaf())
				return nullptr;
			else if (key > z_key)
				z = z->get_right();
			else
				z = z->get_left();
			z_key = z->get_key();
		}
		return z;
	}

	template <class Key, class T, class Compare, class Alloc>
	typename red_black_tree<Key, T, Compare, Alloc>::node_type	*red_black_tree<Key, T, Compare, Alloc>::insert(value_type &value)
	{
		node_type	*z = this->_root;
		key_type	&z_key = z->get_key();
		key_type	&v_key = value.first;
		while (!z->is_leaf())
		{
			if (z_key == v_key)
				return z;
			else if (v_key > z_key)
				z = z->get_right();
			else
				z = z->get_left();
			z_key = z->get_key();
		}
		node_type *new_node = new node_type(value, z, this->_create_leaf(), z->parent);
		z->set_parent(new_node);
		return new_node;
	}

	template <class Key, class T, class Compare, class Alloc>
	void														red_black_tree<Key, T, Compare, Alloc>::erase(key_type &key)
	{
		node_type	*z = this->search(key);
		if (!z)
			return ;
		if ( (z->get_left().is_leaf && z->get_right().is_leaf) || (!z->get_left().is_leaf && z->get_right().is_leaf) )
		{
			delete z->get_right();
			this->_replace_node(z->parent, z, z->get_left());
		}
		else if (z->get_left().is_leaf && !z->get_right().is_leaf)
		{
			delete z->get_left();
			this->_replace_node(z->parent, z, z->get_right());
		}
		else
		{
			node_type	*smallest = this->_get_smallest(z->get_right());
			z->set_pair(smallest->get_pair());
			this->erase(smallest);
		}
	}

	/*
		PRIVATE UTILS METHOD
	*/
	
	template <class Key, class T, class Compare, class Alloc>
	typename red_black_tree<Key, T, Compare, Alloc>::node_type	*red_black_tree<Key, T, Compare, Alloc>::_create_leaf(const node_type *parent)
	{
		return node_type(parent);
	}

	template <class Key, class T, class Compare, class Alloc>
	void														red_black_tree<Key, T, Compare, Alloc>::_replace_node(node_type *parent, node_type *z, node_type *replacer)
	{
		if (z == parent->get_left())
			parent->set_left(replacer);
		else if (z == parent->get_right())
			parent->set_right(replacer);
		else
			return ;
		delete z;
	}

	template <class Key, class T, class Compare, class Alloc>
	typename red_black_tree<Key, T, Compare, Alloc>::node_type	*red_black_tree<Key, T, Compare, Alloc>::_get_biggest(node_type *subroot)
	{
		while (!subroot->get_right()->is_leaf())
			subroot = subroot->get_right();
		return subroot;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename red_black_tree<Key, T, Compare, Alloc>::node_type	*red_black_tree<Key, T, Compare, Alloc>::_get_smallest(node_type *subroot)
	{
		while (!subroot->get_left()->is_leaf())
			subroot = subroot->get_left();
		return subroot;
	}

}


/*
	---RULES---
	balanced binary tree rules :
		-each node can have until 2 subtrees :
			-left items are smaller
			-right items are larger
	red black tree rules :
		-a node is black or red
		-NIL are black
		-if a node is red its children are black
		-all path from a node to leaves contain same amount of black nodes
	red black tree subrules
		-nodes need one storage bit to keep track of color
		-longest path from root in no more twice the length of sorthest path
			-direct consequence : shortest path is all black nodes and longest is alternating red and black
*/
/*
	---SEARCH---
	Just iterate or :
	First rule: The first node in the tree is the leftmost node in the tree.
	Next rule: The successor of a node is:
		Next-R rule: If it has a right subtree, the leftmost node in the right subtree.
		Next-U rule: Otherwise, traverse up the tree
			If you make a right turn (i.e. this node was a left child), then that parent node is the successor
			If you make a left turn (i.e. this node was a right child), continue going up.
			If you can't go up anymore, then there's no successor

	Iterate in order : https://stackoverflow.com/questions/2942517/how-do-i-iterate-over-binary-tree
*/
/*
	---ROTATIONS---
	-Rearrange subtrees (not a simple "rotation")
	-Goal is to decrease height of the tree
		-larger subtrees up, smaller subtrees down
	-Does not affect the order of elements

	Left Rotate Pseudo-Code :
	y = x.right
	x.right = y.left
	if y.left != T.nil
		y.left.p = x
	y.p = x.p
	if x.p == T.nil
		T.root = y
	else if x == x.p.left
		x.p.left = y
	else
		x.p.right = y
	y.left = x
	x.p = y
*/
/*
	---INSERT---
	Steps :
		-Insert Z and color it red
		-Recolor and rotate nodes to fix violation
	Scenarios to fix violation (where Z is the node posing problem):
		-Z = root -> color black
		-Z.uncle = red -> recolor
		-Z.uncle = black (triangle) -> rotate Z.parent //in opposite direction of Z I think?
		-Z.uncle = black (line) -> rotate Z.grandparent + recolor //in opposite direction of Z I think?
	Personal Note : A violation fixing can cause another violation, loop over the violation fixing while changing Z each time! 

	Simple Insert Pseudo-Code :
	y = T.nil
	x = T.root
	while x != T.nil
		y = x
		if z.key < x.key
			x = x.left
		else
			x = x.right
	z.p = y
	if y == T.nil
		T.root = z
	else if z.key < y.key
		y.left = z
	else
		y.right = z
	z.left = T.nil
	z.right = T.nil
	z.color = RED
	RB-INSERT-FIXUP(z) (Next Pseudo-Code)

	Case 4 Fix Violation Scenario Pseudo-Code
	while z.p.color == RED
		if z.p == z.p.p.left
			y = z.p.p.right
			if y.color == RED
				z.p.color = BLACK
				y.color = BLACK
				z.p.p.color = RED
				z = z.p.p
			else if z == z.p.right
				z = z.p
				LEFT-ROTATE(z)
			z.p.color = BLACK
			z.p.p.color = RED
			RIGHT-ROTATE(z.p.p)
		else (same but echange left and right)
	T.root.color = BLACK (Case 0)
	http://staff.ustc.edu.cn/~csli/graduate/algorithms/book6/chap14.htm
*/


#endif