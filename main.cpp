/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:31:47 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/27 13:43:39 by ldelmas          ###   ########.fr       */
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
	typedef ft::pair<std::string, int> type;
	typedef ft::red_black_tree<type> tree_type;
	typedef ft::red_black_node<type> node_type;

	tree_type rbtree;
	node_type rbnode = node_type(rbtree);
	return 0;
}