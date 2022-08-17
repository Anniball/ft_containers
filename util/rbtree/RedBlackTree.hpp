/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:02:21 by ldelmas           #+#    #+#             */
/*   Updated: 2022/08/17 13:43:56 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <memory>
# include "RedBlackNode.hpp"
# include "../Pair.hpp"
# include "../../iter/IteratorsTraits.hpp"
# include "../../iter/TreeIterator.hpp"
# include "../Utilities.hpp"

# define RBT_RED true
# define RBT_BLACK false

namespace ft
{

	template <class T, class Compare, class Node>
	class tree_iterator;

	template <class T, class Compare = ft::less<T> >
	class red_black_node;

	template <class T, class Alloc = std::allocator<T>, class Compare = ft::less<T> >
	class red_black_tree
	{
		public :
			typedef T																		value_type;
			typedef red_black_node<value_type, Compare>										node_type;
			typedef red_black_node<const value_type, Compare>								node_const_type;
			typedef typename Alloc::template rebind<node_type>::other						allocator_type;
			typedef Compare																	value_compare;
			typedef red_black_tree<T, Alloc, Compare>										tree_type;
			typedef	typename allocator_type::reference										reference;
			typedef typename allocator_type::const_reference								const_reference;
			typedef typename allocator_type::pointer										pointer;
			typedef typename allocator_type::const_pointer									const_pointer;
			typedef ft::tree_iterator<value_type, value_compare, node_type>					iterator;
			typedef ft::tree_iterator<const value_type, value_compare, node_const_type >	const_iterator;
			typedef ft::reverse_iterator<iterator>											reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>									const_reverse_iterator;
			typedef size_t																	size_type;

		public :
			/*
				CONSTRUCTORS AND DESTRUCTORS
			*/
			explicit red_black_tree(value_compare &comp = value_compare());
			red_black_tree(const red_black_tree &src);
			~red_black_tree(void);

			/*
				OPERATOR OVERLOADS
			*/
			red_black_tree			&operator=(const red_black_tree &right);

			/*
				GETTERS & SETTERS
			*/
			node_type				*get_root(void) const;
			node_type				*get_end(void) const;
			value_compare const		&get_comp(void) const;
			allocator_type const	&get_alloc(void) const;
			void					set_root(node_type *ptr);
			void					set_end(node_type *end);

			/*
				MEMBER METHODS
			*/
			node_type				*search(value_type &val) const;
			node_type				*search_lower_bound(value_type &val) const;
			node_type				*search_upper_bound(value_type &val) const;
			pair<node_type*, bool>	insert(const value_type &val);
			pair<node_type*, bool>	insert(const value_type &val, node_type *hint);
			bool					erase(value_type &val);
			bool					erase(node_type *z);
			void					clear(void);
			node_type				*create_node(node_type *parent, node_type *left, node_type *right, value_type &content);
			void					swap_content(tree_type &tree);

		private :
			node_type				*_root;
			node_type				*_end;
			allocator_type			_node_alloc;
			value_compare			&_comp;

			/*
				PRIVATE UTILS METHOD
			*/
			void					_replace_node(node_type *parent, node_type *z, node_type *replacer);
			bool					_is_black(node_type *k);
			bool					_is_red(node_type *k);
			void					_left_rotate(node_type *k);
			void					_right_rotate(node_type *k);
			void					_check_violation(node_type *k);
			void					_print_tree(void);
	};
	
	
	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/

	template <class T, class Alloc, class Compare>
	red_black_tree<T, Alloc, Compare>::red_black_tree(value_compare &comp) : _root(nullptr), _node_alloc(), _comp(comp)
	{
		this->_end = _node_alloc.allocate(1);
		this->_node_alloc.construct(this->_end, node_type(this->_root, this->_comp));
		return ;
	}
	
	template <class T, class Alloc, class Compare>
	red_black_tree<T, Alloc, Compare>::red_black_tree(const red_black_tree<T, Alloc, Compare> &src) :  _root(nullptr), _node_alloc(src._node_alloc), _comp(src._comp)
	{
		this->_end = _node_alloc.allocate(1);
		this->_node_alloc.construct(this->_end, node_type(this->_root, this->_comp));
		for (node_type *node = node_type::get_smallest(src._root); node != src._end; node = node->iterate())
			this->insert(node->get_value());
		return ;
	}
	
	template <class T, class Alloc, class Compare>
	red_black_tree<T, Alloc, Compare>::~red_black_tree()
	{
		this->clear();
		this->_node_alloc.destroy(this->_end);
		this->_node_alloc.deallocate(this->_end, 1);
	}


	/*
		OPERATOR OVERLOADS
	*/

	template <class T, class Alloc, class Compare>
	red_black_tree<T, Alloc, Compare>							&red_black_tree<T, Alloc, Compare>::operator=(const red_black_tree<T, Alloc, Compare> &right)
	{
		this->clear();
		for (node_type *node = node_type::get_smallest(right._root); node != right._end && node; node = node->iterate())
			this->insert(node->get_value());
		return *this;
	}
	

	/*
		GETTERS AND SETTERS
	*/
	
	template <class T, class Alloc, class Compare>
	typename red_black_tree<T, Alloc, Compare>::node_type				*red_black_tree<T, Alloc, Compare>::get_root(void) const
	{
		return this->_root;
	}
	
	template <class T, class Alloc, class Compare>
	typename red_black_tree<T, Alloc, Compare>::node_type				*red_black_tree<T, Alloc, Compare>::get_end(void) const
	{
		return this->_end;
	}

	template <class T, class Alloc, class Compare>
	typename red_black_tree<T, Alloc, Compare>::value_compare const		&red_black_tree<T, Alloc, Compare>::get_comp(void) const
	{
		return this->_comp;	
	}
	
	template <class T, class Alloc, class Compare>
	typename red_black_tree<T, Alloc, Compare>::allocator_type const	&red_black_tree<T, Alloc, Compare>::get_alloc(void) const
	{
		return this->_node_alloc;
	}


	template <class T, class Alloc, class Compare>
	void																red_black_tree<T, Alloc, Compare>::set_root(node_type *ptr)
	{
		this->_root = ptr;
		this->_end->set_end(ptr);
	}
	
	template <class T, class Alloc, class Compare>
	void																red_black_tree<T, Alloc, Compare>::set_end(node_type *ptr)
	{
		this->_end = ptr;
	}
	

	/*
		MEMBER METHODS
	*/

	template <class T, class Alloc, class Compare>
	typename red_black_tree<T, Alloc, Compare>::node_type			*red_black_tree<T, Alloc, Compare>::search(value_type &val) const
	{
		node_type	*z = this->_root;
		node_type	tmp(val, this->_end, this->_comp);
		while (z)
		{
			if (*z == tmp)
				return z;
			else if (tmp > *z)
				z = z->get_right();
			else
				z = z->get_left();
		}
		return this->_end;
	}

	template <class T, class Alloc, class Compare>
	typename red_black_tree<T, Alloc, Compare>::node_type			*red_black_tree<T, Alloc, Compare>::search_lower_bound(value_type &val) const
	{
		node_type	*z = this->_root;
		node_type	tmp(val, this->_end, this->_comp);
		node_type	*previous = nullptr;
		while (z)
		{
			previous = z;
			if (*z == tmp)
				return z;
			else if (tmp > *z)
				z = z->get_right();
			else
				z = z->get_left();
		}
		if (!previous)
			return this->_end;
		else if (tmp > *previous)
			return previous->iterate();
		return previous;
	}

	template <class T, class Alloc, class Compare>
	typename red_black_tree<T, Alloc, Compare>::node_type			*red_black_tree<T, Alloc, Compare>::search_upper_bound(value_type &val) const
	{
		node_type	*z = this->_root;
		node_type	tmp(val, this->_end, this->_comp);
		node_type	*previous = nullptr;
		while (z)
		{
			previous = z;
			if (*z == tmp)
				return z->iterate();
			else if (tmp > *z)
				z = z->get_right();
			else
				z = z->get_left();
		}
		if (!previous)
			return this->_end;
		else if (tmp > *previous)
			return previous->iterate();
		return previous;
	}

	template <class T, class Alloc, class Compare>
	pair<typename red_black_tree<T, Alloc, Compare>::node_type*, bool>	red_black_tree<T, Alloc, Compare>::insert(const value_type &value)
	{
		node_type	*z = this->_root;
		node_type	tmp(value, this->_end, this->_comp);
		node_type	*previous = nullptr;
		while (z)
		{
			previous = z;
			if (tmp == *z)
				return pair<node_type*, bool>(z, false);
			if (tmp < *z)
				z = z->get_left();
			else
				z = z->get_right();
		}
		node_type *new_node = this->_node_alloc.allocate(1);
		this->_node_alloc.construct(new_node, node_type(value, nullptr, nullptr, previous, this->_end, this->_comp));
		if (!previous)
			this->set_root(new_node);
		else if (tmp < *previous)
			previous->set_left(new_node);
		else
			previous->set_right(new_node);
		this->_check_violation(new_node);
		return pair<node_type*, bool>(new_node, true);
	}

	//FUUUUUH
	template <class T, class Alloc, class Compare>
	pair<typename red_black_tree<T, Alloc, Compare>::node_type*, bool>	red_black_tree<T, Alloc, Compare>::insert(const value_type &val, node_type *hint)
	{
		// TEMPORARY SOLUTION
		(void)hint;
		return this->insert(val);
		// //CASE 1 : PARENT : position - 1, LEFT CHILD : position
		// node_type *parent = hint->get_parent();
		// if(val > hint->get_value() && val ))
		// {
		// 	node_type *new_node = this->_tree.create_node(parent, parent->get_left(), nullptr, val);
		// 	pos.set_parent(new_node);
		// 	previous.set_left(new_node);
		// 	return new_node;
		// }
		// //CASE 2 : RIGHT CHILD : position -  1, PARENT : position
		// else if (parent.get_right()->get_value() == hint)
		// {
		// 	node_type *new_node = this->_tree.create_node(parent, nullptr, position, val);
		// 	pos.set_parent(new_node);
		// 	previous.set_right(new_node);
		// 	return new_node;
		// }
		// return nullptr;
	}

	template <class T, class Alloc, class Compare>
	bool													red_black_tree<T, Alloc, Compare>::erase(value_type &val)
	{
		node_type	*z = this->search(val);
		return this->erase(z);
	}

	template <class T, class Alloc, class Compare>
	bool													red_black_tree<T, Alloc, Compare>::erase(node_type *z)
	{
		node_type	*left = z->get_left();
		node_type	*right = z->get_right();
		if (z == this->_end)
			return false;
		if ( (!left && !right) || (left && !right) )
		{
			this->_replace_node(z->get_parent(), z, left);
			if (z == this->_root)
				this->set_root(left);
		}
		else if (!left && right)
		{
			this->_replace_node(z->get_parent(), z, right);
			if (z == this->_root)
				this->set_root(right);
		}
		else
		{
			node_type	*smallest = node_type::get_smallest(right);
			this->_node_alloc.destroy(z);
			this->_node_alloc.construct(z, node_type(smallest->get_value(), left, right, z->get_parent(), this->_end, this->_comp));
			this->erase(smallest);
		}
		return true;
	}

	template <class T, class Alloc, class Compare>
	void													red_black_tree<T, Alloc, Compare>::clear(void)
	{
		node_type *nd = node_type::get_smallest(this->_root); 
		while (nd && nd != this->_end)
		{
			node_type *tmp = nd->iterate();
			this->erase(tmp);
			nd = tmp;
		}
		this->_root = nullptr;
		return ;
	}

	template <class T, class Alloc, class Compare>
	typename red_black_tree<T, Alloc, Compare>::node_type	*red_black_tree<T, Alloc, Compare>::create_node(node_type *parent, node_type *left, node_type *right, value_type &content)
	{
		node_type *new_node = this->_node_alloc.allocate(1);
		_node_alloc.construct(new_node, node_type(content, left, right, parent, this->_end, this->_comp));
		return new_node;
	}

	template <class T, class Alloc, class Compare>
	void													red_black_tree<T, Alloc, Compare>::swap_content(tree_type &tree)
	{
		node_type *tmp_root = tree.get_root();
		node_type *tmp_end = tree.get_end();
		tree.set_root(this->get_root());
		tree.set_end(this->get_end());
		this->set_root(tmp_root);
		this->set_end(tmp_end);
		for (node_type *k = this->get_root(); k != this->get_end(); k = k->iterate())
			k->set_end(this->_end);
		for (node_type *k = tree.get_root(); k != tree.get_end(); k = k->iterate())
			k->set_end(tree.get_end());
		return ;
	}

	/*
		PRIVATE UTILS METHODS
	*/

	template <class T, class Alloc, class Compare>
	void													red_black_tree<T, Alloc, Compare>::_replace_node(node_type *parent, node_type *z, node_type *replacer)
	{
		if (parent)
		{
			if (z == parent->get_left())
				parent->set_left(replacer);
			else if (z == parent->get_right())
				parent->set_right(replacer);
			else
				return ;
		}
		if (replacer)
			replacer->set_parent(parent);
		this->_node_alloc.destroy(z);
		this->_node_alloc.deallocate(z, 1);
		return ;
	}

	template <class T, class Alloc, class Compare>
	bool													red_black_tree<T, Alloc, Compare>::_is_black(node_type *k)
	{
		if (!k || k->is_black())
			return true;
		return false;
	}

	template <class T, class Alloc, class Compare>
	bool													red_black_tree<T, Alloc, Compare>::_is_red(node_type *k)
	{
		if (k && k->is_red())
			return true;
		return false;
	}

	template <class T, class Alloc, class Compare>
	void													red_black_tree<T, Alloc, Compare>::_left_rotate(node_type *k)
	{
		node_type	*right = k->get_right();
		node_type	*child_left = right->get_left();
		k->set_right(child_left);
		if (child_left)
			child_left->set_parent(k);
		right->set_parent(k->get_parent());
		if (!k->get_parent())
			this->set_root(right);
		else if (k == k->get_parent()->get_left())
			k->get_parent()->set_left(right);
		else
			k->get_parent()->set_right(right);
		right->set_left(k);
		k->set_parent(right);
		return ;
	}

	template <class T, class Alloc, class Compare>
	void													red_black_tree<T, Alloc, Compare>::_right_rotate(node_type *k)
	{
		node_type	*left = k->get_left();
		node_type	*child_right = left->get_right();
		k->set_left(child_right);
		if (child_right)
			child_right->set_parent(k);
		left->set_parent(k->get_parent());
		if (!k->get_parent())
			this->set_root(left);
		else if (k == k->get_parent()->get_right())
			k->get_parent()->set_right(left);
		else
			k->get_parent()->set_left(left);
		left->set_right(k);
		k->set_parent(left);
		return ;
	}

	template <class T, class Alloc, class Compare>
	void													red_black_tree<T, Alloc, Compare>::_check_violation(node_type *k)
	{
		while ( this->_is_red(k->get_parent()) && k->get_parent()->get_parent() )
		{
			node_type	*parent = k->get_parent();
			node_type	*gparent = parent->get_parent();
			bool		is_left = (gparent->get_left() == parent);
			node_type	*uncle = (is_left ? gparent->get_right() : gparent->get_left());

			if ( this->_is_red(uncle) )
			{
				parent->set_color(RBT_BLACK);
				uncle->set_color(RBT_BLACK);
				gparent->set_color(RBT_RED);
				k = gparent;
			}
			else
			{
				if ( k == (is_left ? parent->get_right() : parent->get_left()) )
				{
					k = parent;
					is_left ? this->_left_rotate(k) : this->_right_rotate(k);
				}
				parent->set_color(RBT_BLACK);
				gparent->set_color(RBT_RED);
				is_left ? this->_right_rotate(gparent) : this->_left_rotate(gparent);
			}
		}
		this->_root->set_color(RBT_BLACK);
		return ;
	}

	//DELETE ME
	template <class T, class Alloc, class Compare>
	void	red_black_tree<T, Alloc, Compare>::_print_tree(void)
	{
		std:: cout << "Starting printing tree :" << std::endl;
		node_type *z = red_black_node<T, Compare>::get_smallest(this->_root);
		while (z != this->_end)
		{
			std::cout << "\t key : " << z->get_value().first << " | value : " << z->get_value().second << std::endl;
			z = z->iterate();
		}
		std:: cout << "Ending printing tree" << std::endl << std::endl;
	}
	//DELETE ME
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