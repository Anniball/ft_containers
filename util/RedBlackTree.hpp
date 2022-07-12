/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:02:21 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/12 17:53:04 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

#include "Pair.hpp"
#include "../iter/IteratorsTraits.hpp"

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

		private :
			value_type				&_content;
			bool					_isRed;
			pointer					_left;
			pointer					_right;
			pointer					_parent;
	};

	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/
	template <class Key, class T, class Compare, class Alloc>
	red_black_node<Key, T, Compare, Alloc>::red_black_node(void) :
	_content(value_type()), _isRed(true), _left(nullptr), _right(nullptr), _parent(nullptr) {}
	
	template <class Key, class T, class Compare, class Alloc>
	red_black_node<Key, T, Compare, Alloc>::red_black_node(const value_type &val) :
	_content(val), _isRed(true), _left(nullptr), _right(nullptr), _parent(nullptr) {}
	
	template <class Key, class T, class Compare, class Alloc>
	red_black_node<Key, T, Compare, Alloc>::red_black_node(const value_type &val, const pointer left, const pointer right, const pointer parent) :
	_content(val), _isRed(true), _left(left), _right(right), _parent(parent) {}
	
	template <class Key, class T, class Compare, class Alloc>
	red_black_node<Key, T, Compare, Alloc>::red_black_node(const node_type &src) :
	_content(src._content), _isRed(src._isRed), _left(src._left), _right(src._right), _parent(src._parent) {}
	
	template <class Key, class T, class Compare, class Alloc>
	red_black_node<Key, T, Compare, Alloc>::~red_black_node(void) {}


	/*
		GETTERS
	*/
	// key_type			&get_key(void) const;
	// mapped_type		&get_value(void) const;
	// value_type		&get_pair(void) const;
	// pointer			get_left(void) const;
	// pointer			get_right(void) const;
	// pointer			get_parent(void) const;
	// pointer			get_grand_parent(void) const;
	// bool				is_red(void) const;
	// bool				is_black(void) const;
	

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

		private :
			
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
			https://stackoverflow.com/questions/2942517/how-do-i-iterate-over-binary-tree
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
	};
}


#endif