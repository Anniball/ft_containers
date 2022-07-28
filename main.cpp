/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:31:47 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/28 16:39:21 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "iter/Iterator.hpp"
#include "iter/IteratorsTraits.hpp"
#include "iter/RandomAccessIterator.hpp"
#include "iter/ReverseIterator.hpp"
#include "iter/TreeIterator.hpp"
#include "cont/Vector.hpp"
#include "cont/Stack.hpp"
#include "cont/Map.hpp"
#include "util/Utilities.hpp"
#include "util/TypeTraits.hpp"
#include "util/Pair.hpp"
#include "util/rbtree/RedBlackTree.hpp"
#include "util/rbtree/RedBlackNode.hpp"

#include <string>

// static int	iterator_tester()
// {
// 	ft::iterator<ft::iterators_traits<int>, int>  
// }

int		main(void)
{
	typedef std::string							string;
	typedef int									integer;
	typedef ft::pair<string, integer>			type;
	typedef ft::red_black_tree<type>			tree_type;
	typedef ft::red_black_node<type>			node_type;
	typedef ft::red_black_node<const type>		node_const_type;
	typedef ft::map<string, integer>			map;
	typedef map::iterator						iterator;
	typedef map::const_iterator					const_iterator;

	// tree_type rbtree;
	// node_type *rbnode = new node_type(rbtree); //genere une pair selon le type
	// node_const_type rbnode_const = node_type(rbtree);
	// iterator it = iterator(rbnode); //genere une pair selon map donc key est const
	// return 0;
	// ft::pair<std::string, int> mypair("hello", 4);
	// ft::pair<const std::string, int> constpair(mypair);
}
// red_black_node<pair<basic_string<char, char_traits<char>, allocator<char> >, int> > *
// red_black_node<ft::pair<const std::__1::basic_string<char>, int> > *