/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:02:21 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/18 11:06:49 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include "RedBlackNode.hpp"
# include "../Pair.hpp"
# include "../../iter/IteratorsTraits.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class red_black_tree
	{
		typedef Key													key_type;
		typedef T													mapped_type;
		typedef ft::pair<const Key, T>								value_type;
		typedef ft::red_black_node<T>								node_type;
		typedef ft::red_black_tree<Key, T, Compare, Alloc>			tree_type;
		typedef Compare												key_compare;
		typedef Alloc												allocator_type;
		typedef	typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
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
				GETTERS
			*/
			node_type	*get_root(void) const;
			node_type	*get_end(void) const;

			/*
				MEMBER METHODS
			*/
			node_type	*search(key_type &key);
			node_type	*insert(value_type &val);
			void		erase(key_type &val);
			node_type	*iterate(node_type *k); //may be useless 
			node_type	*reverse_iterate(node_type *k); //may be useless

		private :
			node_type	*_root;
			node_type	*_end;

			/*
				PRIVATE UTILS METHOD
			*/
			node_type	*_create_leaf(const node_type *parent);
			void		_replace_node(node_type *parent, node_type *z, node_type *replacer);
	};
	
	
	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/
	template <class Key, class T, class Compare, class Alloc>
	red_black_tree<Key, T, Compare, Alloc>::red_black_tree()
	{
		this->_end = new node_type();
		this->_root = new node_type();
	}
	
	template <class Key, class T, class Compare, class Alloc>
	red_black_tree<Key, T, Compare, Alloc>::red_black_tree(const value_type &val)
	{
		this->_end = new node_type();
		this->_root = new node_type(val);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	red_black_tree<Key, T, Compare, Alloc>::red_black_tree(const node_type &node) : _root(node)
	{
		this->_end = new node_type();
		this->_root = new node_type(node);
	}
	
	// template <class Key, class T, class Compare, class Alloc>
	// red_black_tree(const &tree_type src) {} //LET'S GO BACK ON IT LATER
	
	// template <class Key, class T, class Compare, class Alloc>
	// ~red_black_tree() {} //LET'S GO BACK ON IT LATER


	/*
		GETTERS
	*/
	
	template <class Key, class T, class Compare, class Alloc>
	typename red_black_tree<Key, T, Compare, Alloc>::node_type	*red_black_tree<Key, T, Compare, Alloc>::get_root(void) const
	{
		return this->_root;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename red_black_tree<Key, T, Compare, Alloc>::node_type	*red_black_tree<Key, T, Compare, Alloc>::get_end(void) const
	{
		return this->_end;
	}


	/*
		MEMBER METHODS
	*/
	
	template <class Key, class T, class Compare, class Alloc>
	typename red_black_tree<Key, T, Compare, Alloc>::node_type	*red_black_tree<Key, T, Compare, Alloc>::search(key_type &key)
	{
		node_type	*z = this->_root;
		key_type	&z_key = z->get_value()->first;
		while (z_key != key)
		{
			if (z->is_leaf())
				return nullptr;
			else if (key > z_key)
				z = z->get_right();
			else
				z = z->get_left();
			z_key = z->get_value()->first;
		}
		return z;
	}

	template <class Key, class T, class Compare, class Alloc>
	typename red_black_tree<Key, T, Compare, Alloc>::node_type	*red_black_tree<Key, T, Compare, Alloc>::insert(value_type &value)
	{
		node_type	*z = this->_root;
		key_type	&z_key = z->get_value()->first;
		key_type	&v_key = value.first;
		while (!z->is_leaf())
		{
			if (z_key == v_key)
				return z;
			else if (v_key > z_key)
				z = z->get_right();
			else
				z = z->get_left();
			z_key = z->get_value()->first;
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
			node_type	*smallest = z->get_right()->get_smallest;
			z->set_pair(smallest->get_pair());
			this->erase(smallest);
		}
	}

	template <class Key, class T, class Compare, class Alloc>
	typename red_black_tree<Key, T, Compare, Alloc>::node_type	*red_black_tree<Key, T, Compare, Alloc>::iterate(node_type *k)
	{
		node_type	*right = k->get_right;
		node_type	*parent = k->get_parent();
		if (!right->is_leaf())
			return right->get_smallest();
		else if (parent->get_left() == k)
			return parent;
		else if (parent->get_right() == k)
			return (this->iterate(parent));
		return this->_end;
	}

	template <class Key, class T, class Compare, class Alloc>
	typename red_black_tree<Key, T, Compare, Alloc>::node_type	*red_black_tree<Key, T, Compare, Alloc>::reverse_iterate(node_type *k)
	{
		node_type	*left = k->get_left;
		node_type	*parent = k->get_parent();
		if (!left->is_leaf())
			return left->get_biggest();
		else if (parent->get_right() == k)
			return parent;
		else if (parent->get_left() == k)
			return (this->iterate(parent));
		return this->_end; //probably not that since it's the first
		//return this->_get_smallest(this->_root); //maybe this instead
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