/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreeIterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:25:03 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/13 14:44:20 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

# include "../util/rbtree/RedBlackNode.hpp"

namespace ft
{
	template <class T>
	class tree_iterator
	{
		typedef T							value_type;
		typedef T&							reference;
		typedef T*							pointer;
		typedef ptrdiff_t					difference_type;
		typedef red_black_node<T>			node_pointer; //going to be a problem since rbnode are based on <Key, T>
		typedef tree_iterator<T>			iterator;

		public :
			tree_iterator(void);
			tree_iterator(tree_iterator const &src);
			~tree_iterator(void);

			iterator		&operator=(tree_iterator const &right);
			reference		operator*(void);
			pointer			operator->(void);
			iterator		&operator++(void);
			iterator		operator++(int);
			iterator		&operator--(void);
			iterator		operator--(int);
		private :
			node_pointer	_content;
	}	
}

#endif