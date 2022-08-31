/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:31:47 by ldelmas           #+#    #+#             */
/*   Updated: 2022/08/31 14:39:09 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <deque>
#if 0 //CREATE A REAL STL EXAMPLE
	#include <map>
	#include <stack>
	#include <vector>
	namespace ft = std;
#else
	#include "./cont/Map.hpp"
	#include "./cont/Stack.hpp"
	#include "./cont/Vector.hpp"
#endif

#include <stdlib.h>

#define MAX_RAM 4294967296
#define BUFFER_SIZE 4096
struct Buffer
{
	int idx;
	char buff[BUFFER_SIZE];
};


#define COUNT (MAX_RAM / (int)sizeof(Buffer))

template<typename T>
class MutantStack : public ft::stack<T>
{
public:
	MutantStack() {}
	MutantStack(const MutantStack<T>& src) { *this = src; }
	MutantStack<T>& operator=(const MutantStack<T>& rhs) 
	{
		this->c = rhs.c;
		return *this;
	}
	~MutantStack() {}

	typedef typename ft::stack<T>::container_type::iterator iterator;

	iterator begin() { return this->c.begin(); }
	iterator end() { return this->c.end(); }
};

int main(int argc, char** argv) {
	if (argc != 2)
	{
		std::cerr << "Usage: ./test seed" << std::endl;
		std::cerr << "Provide a seed please" << std::endl;
		std::cerr << "Count value:" << COUNT << std::endl;
		return 1;
	}
	const int seed = atoi(argv[1]);
	srand(seed);

	ft::vector<std::string> vector_str;
	ft::vector<int> vector_int;
	ft::stack<int> stack_int;
	ft::vector<Buffer> vector_buffer;
	ft::stack<Buffer, std::deque<Buffer> > stack_deq_buffer;
	ft::map<int, int> map_int;

	for (int i = 0; i < COUNT; i++)
	{
		vector_buffer.push_back(Buffer());
	}

	for (int i = 0; i < COUNT; i++)
	{
		const int idx = rand() % COUNT;
		vector_buffer[idx].idx = 5;
	}
	ft::vector<Buffer>().swap(vector_buffer);

	try
	{
		for (int i = 0; i < COUNT; i++)
		{
			const int idx = rand() % COUNT;
			vector_buffer.at(idx);
			std::cerr << "Error: THIS VECTOR SHOULD BE EMPTY!!" <<std::endl;
		}
	}
	catch(const std::exception& e)
	{
		//NORMAL ! :P
	}
	
	for (int i = 0; i < COUNT; ++i)
	{
		map_int.insert(ft::make_pair(rand() % COUNT, rand() % COUNT));
	}

	int sum = 0;
	for (int i = 0; i < 10000; i++)
	{
		int access = rand() % COUNT;
		sum += map_int[access];
	}
	std::cout << "should be constant with the same seed: " << sum << std::endl;

	{
		ft::map<int, int> copy = map_int;
	}
	MutantStack<char> iterable_stack;
	for (char letter = 'a'; letter <= 'z'; letter++)
		iterable_stack.push(letter);
	for (MutantStack<char>::iterator it = iterable_stack.begin(); it != iterable_stack.end(); it++)
	{
		std::cout << *it;
	}
	std::cout << std::endl;
	return (0);
}

// #include "iter/Iterator.hpp"
// #include "iter/IteratorsTraits.hpp"
// #include "iter/RandomAccessIterator.hpp"
// #include "iter/ReverseIterator.hpp"
// #include "iter/TreeIterator.hpp"
// #include "cont/Vector.hpp"
// #include "cont/Stack.hpp"
// #include "cont/Map.hpp"
// #include "util/Utilities.hpp"
// #include "util/TypeTraits.hpp"
// #include "util/Pair.hpp"
// #include "util/rbtree/RedBlackTree.hpp"
// #include "util/rbtree/RedBlackNode.hpp"

// #include <string>

// // static int	iterator_tester()
// // {
// // 	ft::iterator<ft::iterators_traits<int>, int>  
// // }

// int		main(void)
// {
// 	typedef std::string							string;
// 	typedef int									integer;
// 	typedef ft::pair<string, integer>			type;
// 	typedef ft::red_black_tree<type>			tree_type;
// 	typedef ft::red_black_node<type>			node_type;
// 	typedef ft::red_black_node<const type>		node_const_type;
// 	typedef ft::map<string, integer>			map;
// 	typedef map::iterator						iterator;
// 	typedef map::const_iterator					const_iterator;

// 	// tree_type rbtree;
// 	// node_type *rbnode = new node_type(rbtree); //genere une pair selon le type
// 	// node_const_type rbnode_const = node_type(rbtree);
// 	// iterator it = iterator(rbnode); //genere une pair selon map donc key est const
// 	// return 0;
// 	// ft::pair<std::string, int> mypair("hello", 4);
// 	// ft::pair<const std::string, int> constpair(mypair);
// }
// // red_black_node<pair<basic_string<char, char_traits<char>, allocator<char> >, int> > *
// // red_black_node<ft::pair<const std::__1::basic_string<char>, int> > *