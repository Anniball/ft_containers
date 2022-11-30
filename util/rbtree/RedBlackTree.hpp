/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RedBlackTree.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 16:02:21 by ldelmas           #+#    #+#             */
/*   Updated: 2022/11/30 14:38:23 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_HPP
# define RED_BLACK_TREE_HPP

# include <memory>
# include "RedBlackNode.hpp"
# include "../Pair.hpp"
# include "../Utilities.hpp"

# define RBT_RED true
# define RBT_BLACK false

namespace ft
{
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
			node_type				*get_root(void);
			node_const_type			*get_root(void) const;
			node_type				*get_end(void);
			node_const_type			*get_end(void) const;
			value_compare const		&get_comp(void) const;
			allocator_type const	&get_alloc(void) const;
			void					set_root(node_type *ptr);
			void					set_end(node_type *end);

			/*
				MEMBER METHODS
			*/
			node_type				*search(const value_type &val);
			node_const_type			*search(const value_type &val) const;
			node_type				*search_lower_bound(const value_type &val);
			node_const_type			*search_lower_bound(const value_type &val) const;
			node_type				*search_upper_bound(const value_type &val);
			node_const_type			*search_upper_bound(const value_type &val) const;
			pair<node_type*, bool>	insert(node_type &node, node_type *z);
			pair<node_type*, bool>	insert(const value_type &val);
			pair<node_type*, bool>	insert(const value_type &val, node_type *hint);
			bool					erase(const value_type &val);
			bool					erase(node_type *k);
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
			pair<node_type*, bool>	_create_child(node_type *parent, bool is_left);
			void					_replace_node(node_type *parent, node_type *k, node_type *replacer);
			void					_transplant_node(node_type *parent, node_type *k, node_type *replacer);
			bool					_is_black(node_type *k);
			bool					_is_red(node_type *k);
			void					_left_rotate(node_type *k);
			void					_right_rotate(node_type *k);
			void					_fix_insertion(node_type *k);
			void					_fix_deletion(node_type *k);
			node_type				*_search(const value_type &val) const;
			node_type				*_search_lower_bound(const value_type &val) const;
			node_type				*_search_upper_bound(const value_type &val) const;
	};
	
	
	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/

	template <class T, class Alloc, class Compare>
	red_black_tree<T, Alloc, Compare>::red_black_tree(value_compare &comp) : _root(NULL), _node_alloc(), _comp(comp)
	{
		this->_end = _node_alloc.allocate(1);
		this->_node_alloc.construct(this->_end, node_type(this->_root, this->_comp));
		return ;
	}
	
	template <class T, class Alloc, class Compare>
	red_black_tree<T, Alloc, Compare>::red_black_tree(const red_black_tree<T, Alloc, Compare> &src) :  _root(NULL), _node_alloc(src._node_alloc), _comp(src._comp)
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
	typename red_black_tree<T, Alloc, Compare>::node_type				*red_black_tree<T, Alloc, Compare>::get_root(void)
	{
		return this->_root;
	}

	template <class T, class Alloc, class Compare>
	typename red_black_tree<T, Alloc, Compare>::node_const_type			*red_black_tree<T, Alloc, Compare>::get_root(void) const
	{
		return reinterpret_cast<node_const_type*>(this->_root);
	}
	
	template <class T, class Alloc, class Compare>
	typename red_black_tree<T, Alloc, Compare>::node_type				*red_black_tree<T, Alloc, Compare>::get_end(void)
	{
		return this->_end;
	}

	template <class T, class Alloc, class Compare>
	typename red_black_tree<T, Alloc, Compare>::node_const_type			*red_black_tree<T, Alloc, Compare>::get_end(void) const
	{
		return reinterpret_cast<node_const_type*>(this->_end);
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
		this->_end->set_end(this->_root);
	}
	

	/*
		MEMBER METHODS
	*/

	template <class T, class Alloc, class Compare>
	typename red_black_tree<T, Alloc, Compare>::node_type			*red_black_tree<T, Alloc, Compare>::search(const value_type &val)
	{
		return this->_search(val);
	}

	template <class T, class Alloc, class Compare>
	typename red_black_tree<T, Alloc, Compare>::node_const_type		*red_black_tree<T, Alloc, Compare>::search(const value_type &val) const
	{
		return reinterpret_cast<node_const_type*>(this->_search(val));
	}

	template <class T, class Alloc, class Compare>
	typename red_black_tree<T, Alloc, Compare>::node_type			*red_black_tree<T, Alloc, Compare>::search_lower_bound(const value_type &val)
	{
		return this->_search_lower_bound(val);
	}

	template <class T, class Alloc, class Compare>
	typename red_black_tree<T, Alloc, Compare>::node_const_type		*red_black_tree<T, Alloc, Compare>::search_lower_bound(const value_type &val) const
	{
		return reinterpret_cast<node_const_type*>(this->_search_lower_bound(val));
	}

	template <class T, class Alloc, class Compare>
	typename red_black_tree<T, Alloc, Compare>::node_type			*red_black_tree<T, Alloc, Compare>::search_upper_bound(const value_type &val)
	{
		return this->_search_upper_bound(val);
	}

	template <class T, class Alloc, class Compare>
	typename red_black_tree<T, Alloc, Compare>::node_const_type			*red_black_tree<T, Alloc, Compare>::search_upper_bound(const value_type &val) const
	{
		return reinterpret_cast<node_const_type*>(this->_search_upper_bound(val));
	}

	template <class T, class Alloc, class Compare>
	pair<typename red_black_tree<T, Alloc, Compare>::node_type*, bool>	red_black_tree<T, Alloc, Compare>::insert(node_type &node, node_type *z)
	{
		node_type	*previous = NULL;
		while (z)
		{
			previous = z;
			if (node == *z)
				return pair<node_type*, bool>(z, false);
			if (node < *z)
				z = z->get_left();
			else
				z = z->get_right();
		}
		node_type *new_node = this->_node_alloc.allocate(1);
		this->_node_alloc.construct(new_node, node_type(node.get_value(), NULL, NULL, previous, this->_end, this->_comp));
		if (!previous)
			this->set_root(new_node);
		else if (node < *previous)
			previous->set_left(new_node);
		else
			previous->set_right(new_node);
		this->_fix_insertion(new_node);
		return pair<node_type*, bool>(new_node, true);
	}

	template <class T, class Alloc, class Compare>
	pair<typename red_black_tree<T, Alloc, Compare>::node_type*, bool>	red_black_tree<T, Alloc, Compare>::insert(const value_type &value)
	{
		node_type	tmp(value, this->_end, this->_comp);
		return this->insert(tmp, this->_root);
	}

	template <class T, class Alloc, class Compare>
	pair<typename red_black_tree<T, Alloc, Compare>::node_type*, bool>	red_black_tree<T, Alloc, Compare>::insert(const value_type &val, node_type *hint)
	{
		node_type	tmp(val, this->_end, this->_comp);
		if (*hint < tmp && *(hint->iterate()) > tmp)
			return this->insert(tmp, hint);
		else
			return this->insert(tmp, this->_root);
	}

	template <class T, class Alloc, class Compare>
	bool													red_black_tree<T, Alloc, Compare>::erase(const value_type &val)
	{
		node_type	*z = this->search(val);
		return this->erase(z);
	}

	template <class T, class Alloc, class Compare>
	bool													red_black_tree<T, Alloc, Compare>::erase(node_type *k)
	{
		node_type				*left = k->get_left();
		node_type				*right = k->get_right();
		pair<node_type*, bool>	check = pair<node_type*, bool>(k, true);
		bool					color = k->get_color();
	
		if (k == this->_end)
			return false;
		if (!right)
		{
			check = this->_create_child(k, true);
			this->_replace_node(k->get_parent(), k, check.first);
		}
		else if (!left)
		{
			check = this->_create_child(k, false);
			this->_replace_node(k->get_parent(), k, check.first);
		}
		else
		{
			node_type	*smallest = node_type::get_smallest(right);
			color = smallest->get_color();
			check = this->_create_child(smallest, false);
			if (k == smallest->get_parent())
				check.first->set_parent(smallest);
			else
			{
				this->_transplant_node(smallest->get_parent(), smallest, smallest->get_right());
				smallest->set_right(right);
				smallest->get_right()->set_parent(smallest);
			}
			this->_replace_node(k->get_parent(), k, smallest);
			smallest->set_left(left);
			smallest->get_left()->set_parent(smallest);
			smallest->set_color(k->get_color());
		}
		if (color == RBT_BLACK)
			this->_fix_deletion(check.first);
		if (check.second)
		{
			if (check.first->get_parent())
				check.first == check.first->get_parent()->get_left() ? check.first->get_parent()->set_left(NULL) : check.first->get_parent()->set_right(NULL);
			if (check.first == this->_root)
				this->set_root(NULL);
			this->_node_alloc.destroy(check.first);
			this->_node_alloc.deallocate(check.first, 1);
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
			this->erase(nd);
			nd = tmp;
		}
		this->_root = NULL;
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
		tree._root = this->get_root();
		tree._end = this->get_end();
		this->_root = tmp_root;
		this->_end = tmp_end;
		return ;
	}

	/*
		PRIVATE UTILS METHODS
	*/

	template <class T, class Alloc, class Compare>
	pair<typename red_black_tree<T, Alloc, Compare>::node_type*, bool>	red_black_tree<T, Alloc, Compare>::_create_child(node_type *parent, bool is_left)
	{
		node_type	*child = (is_left ? parent->get_left() : parent->get_right());
		if (child)
			return pair<node_type*, bool>(child, false);
		node_type	*new_node = this->_node_alloc.allocate(1);
		this->_node_alloc.construct(new_node, node_type(value_type(), NULL, NULL, parent, this->_end, this->_comp));
		new_node->set_color(RBT_BLACK);
		is_left ? parent->set_left(new_node) : parent->set_right(new_node);
		return pair<node_type*, bool>(new_node, true);
	}

	template <class T, class Alloc, class Compare>
	void													red_black_tree<T, Alloc, Compare>::_replace_node(node_type *parent, node_type *k, node_type *replacer)
	{
		if (!parent)
			this->set_root(replacer);
		else if (k == parent->get_left())
			parent->set_left(replacer);
		else
			parent->set_right(replacer);
		if (replacer)
			replacer->set_parent(parent);
		this->_node_alloc.destroy(k);
		this->_node_alloc.deallocate(k, 1);
		return ;
	}

	template <class T, class Alloc, class Compare>
	void													red_black_tree<T, Alloc, Compare>::_transplant_node(node_type *parent, node_type *k, node_type *replacer)
	{
		if (!parent)
			this->set_root(replacer);
		else if (k == parent->get_left())
			parent->set_left(replacer);
		else
			parent->set_right(replacer);
		if (replacer)
			replacer->set_parent(parent);
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
	void													red_black_tree<T, Alloc, Compare>::_fix_insertion(node_type *k)
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
					parent = k->get_parent();
					gparent = parent->get_parent();
				}
				parent->set_color(RBT_BLACK);
				gparent->set_color(RBT_RED);
				is_left ? this->_right_rotate(gparent) : this->_left_rotate(gparent);
			}
		}
		this->_root->set_color(RBT_BLACK);
		return ;
	}

	template <class T, class Alloc, class Compare>
	void													red_black_tree<T, Alloc, Compare>::_fix_deletion(node_type *k)
	{
		while (this->_root != k && this->_is_black(k))
		{

			node_type	*parent = k->get_parent();
			bool		is_left = (k == k->get_parent()->get_left());
			node_type	*brother = is_left ? parent->get_right() : parent->get_left();

			if (this->_is_red(brother))
			{
				brother->set_color(RBT_BLACK);
				parent->set_color(RBT_RED);
				is_left ? this->_left_rotate(parent) : this->_right_rotate(parent);
				parent = k->get_parent();
				brother = is_left ? parent->get_right() : parent->get_left();
			}
			if (this->_is_black(brother) && this->_is_black(brother->get_left()) && this->_is_black(brother->get_right()))
			{
				brother->set_color(RBT_RED);
				k = parent;
				parent = parent->get_parent();
			}
			else
			{
				if ( (is_left && this->_is_black(brother) && this->_is_black(brother->get_right()) && this->_is_red(brother->get_left()))
					|| (!is_left && this->_is_black(brother) && this->_is_black(brother->get_left()) && this->_is_red(brother->get_right())) )
				{
					is_left ? brother->get_left()->set_color(RBT_BLACK) : brother->get_right()->set_color(RBT_BLACK);
					brother->set_color(RBT_RED);
					is_left ? this->_right_rotate(brother) : this->_left_rotate(brother);
					parent = k->get_parent();
					brother = ( is_left ? parent->get_right() : parent->get_left() );
				}
			
				brother->set_color(parent->get_color());
				parent->set_color(RBT_BLACK);
				is_left ? brother->get_right()->set_color(RBT_BLACK) : brother->get_left()->set_color(RBT_BLACK);
				is_left ? this->_left_rotate(parent) : this->_right_rotate(parent);
				k = this->_root;
			}
		}
		k->set_color(RBT_BLACK);
	}

	template <class T, class Alloc, class Compare>
	typename red_black_tree<T, Alloc, Compare>::node_type			*red_black_tree<T, Alloc, Compare>::_search(const value_type &val) const
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
	typename red_black_tree<T, Alloc, Compare>::node_type			*red_black_tree<T, Alloc, Compare>::_search_lower_bound(const value_type &val) const
	{
		node_type	*z = this->_root;
		node_type	tmp(val, this->_end, this->_comp);
		node_type	*previous = NULL;
	
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
	typename red_black_tree<T, Alloc, Compare>::node_type			*red_black_tree<T, Alloc, Compare>::_search_upper_bound(const value_type &val) const
	{
		node_type	*z = this->_root;
		node_type	tmp(val, this->_end, this->_comp);
		node_type	*previous = NULL;
	
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
}

#endif