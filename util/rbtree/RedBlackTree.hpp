/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:02:21 by ldelmas           #+#    #+#             */
/*   Updated: 2022/08/11 11:44:29 by ldelmas          ###   ########.fr       */
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
			node_type			*_root;
			node_type			*_end;
			allocator_type		_node_alloc;
			value_compare		&_comp;

			/*
				PRIVATE UTILS METHOD
			*/
			node_type	*_create_leaf(node_type *parent);
			void		_replace_node(node_type *parent, node_type *z, node_type *replacer);
			void		_print_tree(void);
	};
	
	
	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/

	template <class T, class Alloc, class Compare>
	red_black_tree<T, Alloc, Compare>::red_black_tree(value_compare &comp) : _node_alloc(), _comp(comp)
	{
		this->_end = _node_alloc.allocate(1);
		this->_root = _node_alloc.allocate(1);
		this->_node_alloc.construct(this->_end, node_type(this->_root, this->_comp));
		this->_node_alloc.construct(this->_root, node_type(this->_end, this->_comp));
		return ;
	}
	
	template <class T, class Alloc, class Compare>
	red_black_tree<T, Alloc, Compare>::red_black_tree(const red_black_tree<T, Alloc, Compare> &src) : _node_alloc(src._node_alloc), _comp(src._comp)
	{
		this->_end = _node_alloc.allocate(1);
		this->_root = _node_alloc.allocate(1);
		this->_node_alloc.construct(this->_end, node_type(this->_root, this->_comp));
		this->_node_alloc.construct(this->_root, node_type(this->_end, this->_comp));
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
		for (node_type *node = node_type::get_smallest(right._root); node != right._end; node = node->iterate())
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
		while (!z->is_leaf() && *z != tmp)
		{
			if (tmp > *z)
				z = z->get_right();
			else
				z = z->get_left();
		}
		if (z->is_leaf())
			return this->_end;
		return z;
	}

	template <class T, class Alloc, class Compare>
	typename red_black_tree<T, Alloc, Compare>::node_type			*red_black_tree<T, Alloc, Compare>::search_lower_bound(value_type &val) const
	{
		node_type	*z = this->_root;
		node_type	tmp(val, this->_end, this->_comp);
		while (!z->is_leaf())
		{
			if (*z == tmp)
				return z;
			else if (tmp > *z)
				z = z->get_right();
			else
				z = z->get_left();
		}
		return z->iterate();
	}

	template <class T, class Alloc, class Compare>
	typename red_black_tree<T, Alloc, Compare>::node_type			*red_black_tree<T, Alloc, Compare>::search_upper_bound(value_type &val) const
	{
		node_type	*z = this->_root;
		node_type	tmp(val, this->_end, this->_comp);
		while (!z->is_leaf())
		{
			if (*z == tmp)
				break;
			else if (tmp > *z)
				z = z->get_right();
			else
				z = z->get_left();
		}
		return z->iterate();
	}

	//DELETE ME
	template <class T, class Alloc, class Compare>
	void	red_black_tree<T, Alloc, Compare>::_print_tree(void)
	{
		std:: cout << "Starting printing tree :" << std::endl;
		node_type *z = this->_root;
		while (z != this->_end)
			z = z->iterate();
		std:: cout << "Ending printing tree" << std::endl << std::endl;
	}
	//DELETE ME

	template <class T, class Alloc, class Compare>
	pair<typename red_black_tree<T, Alloc, Compare>::node_type*, bool>	red_black_tree<T, Alloc, Compare>::insert(const value_type &value)
	{
		node_type	*z = this->_root;
		node_type	tmp(value, this->_end, this->_comp);
		while (!z->is_leaf())
		{
			if (*z == tmp)
				return pair<node_type*, bool>(z, false);
			else if (tmp > *z)
				z = z->get_right();
			else
				z = z->get_left();
		}
		node_type *parent = z->get_parent();
		node_type *new_node = this->_node_alloc.allocate(1);
		this->_node_alloc.construct(new_node, node_type(value, z, this->_create_leaf(new_node), parent, this->_end, this->_comp));
		z->set_parent(new_node);
		if (z == this->_root)
			this->set_root(new_node);
		if (parent)
		{
			if (parent->get_left() == z)
				parent->set_left(new_node);
			else if (parent)
				parent->set_right(new_node);
		}
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
		if ( (left->is_leaf() && right->is_leaf()) || (!left->is_leaf() && right->is_leaf()) )
		{
			this->_node_alloc.destroy(right);
			this->_node_alloc.deallocate(right, 1);
			if (z == this->_root)
				this->set_root(left);
			this->_replace_node(z->get_parent(), z, left);
		}
		else if (left->is_leaf() && !right->is_leaf())
		{
			this->_node_alloc.destroy(left);
			this->_node_alloc.deallocate(left, 1);
			this->_replace_node(z->get_parent(), z, right);
			if (z == this->_root)
				this->set_root(right);
		}
		else
		{
			node_type	*smallest = node_type::get_smallest(right);
			this->_node_alloc.destroy(z);
			this->_node_alloc.construct(z, node_type(smallest->get_value(), left, right, z->get_parent(), this->_end, this->_comp));
			this->erase(smallest); //not optimal, could create a erase(node_type &val)
		}
		return true;
	}

	template <class T, class Alloc, class Compare>
	void													red_black_tree<T, Alloc, Compare>::clear(void)
	{
		node_type *nd = node_type::get_smallest(this->_root); 
		while (nd != this->_end)
		{
			node_type *tmp = nd->iterate();
			if (nd == this->_root)
			{
				this->_node_alloc.destroy(nd);
				this->_node_alloc.construct(nd, node_type(this->_end, this->_comp));
			}
			else
			{
				this->_node_alloc.destroy(nd);
				this->_node_alloc.deallocate(nd, 1);
			}
			nd = tmp;
		}
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
	typename red_black_tree<T, Alloc, Compare>::node_type	*red_black_tree<T, Alloc, Compare>::_create_leaf(node_type *parent)
	{
		node_type *new_node = _node_alloc.allocate(1);
		_node_alloc.construct(new_node, node_type(parent, this->_end, this->_comp));
		return new_node;
	}

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
		replacer->set_parent(parent);
		this->_node_alloc.destroy(z);
		this->_node_alloc.deallocate(z, 1);
		return ;
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