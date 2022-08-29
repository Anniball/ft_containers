/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:35:11 by ldelmas           #+#    #+#             */
/*   Updated: 2022/08/29 14:47:04 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_HPP
# define SET_HPP

# include <memory>
# include "../iter/IteratorsTraits.hpp"
# include "../iter/ReverseIterator.hpp"
# include "../iter/TreeIterator.hpp"
# include "../util/Pair.hpp"
# include "../util/rbtree/RedBlackTree.hpp"
# include "../util/rbtree/RedBlackNode.hpp"
# include "../util/Utilities.hpp"

namespace ft
{
	template < class T, class Compare = ft::less<T>, class Alloc = std::allocator<T> >
	class set
	{
		public :
			typedef T																												key_type;
			typedef T																												value_type;
			typedef Compare																											key_compare;
			typedef Alloc																											allocator_type;
			typedef typename allocator_type::reference																				reference;
			typedef typename allocator_type::const_reference																		const_reference;
			typedef typename allocator_type::pointer																				pointer;
			typedef typename allocator_type::const_pointer																			const_pointer;
			typedef	typename ft::tree_iterator<value_type, value_compare, red_black_node<value_type, value_compare> >				iterator;
			typedef typename ft::tree_iterator<const value_type, value_compare, red_black_node<const value_type, value_compare> >	const_iterator;
			typedef typename ft::reverse_iterator<iterator>																			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>																	const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type																difference_type;
			typedef size_t																											size_type;

			/*
				CONSTRUCTORS AND DESTRUCTORS
			*/
			explicit set(const key_compare& comp = key_compare(), const allocator_type &alloc = allocator_type());
			template <class InputIterator>
			set(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type());
			set(const set &x);
			~set(void);

			/*
				OPERATOR OVERLOADS
			*/
			set	&operator=(const set &other);

			/*
				MEMBERS METHODS
			*/
			/*Iterators*/
			iterator									begin(void);
			const_iterator								begin(void) const;
			iterator									end(void);
			const_iterator								end(void) const;
			reverse_iterator							rbegin(void);
			const_reverse_iterator						rbegin(void) const;
			reverse_iterator 							rend(void);
			const_reverse_iterator						rend(void) const;
			/*Capacity*/
			bool										empty(void) const;
			size_type									size(void) const;
			size_type									max_size(void) const;
			/*Modifiers*/
			pair<iterator,bool>							insert(const value_type &val);
			iterator									insert(iterator position, const value_type &val);
			template <class InputIterator>
			void 										insert(InputIterator first, InputIterator last);
			void										erase(iterator position);
			size_type									erase(const value_type& val);
			void										erase(iterator first, iterator last);
			void										clear(void);
			void										swap(set &x);
			/*Observers*/
			key_compare									key_comp(void) const;
			value_compare								value_comp(void) const;
			/*Operations*/
			size_type									count(const Key &key) const;
			iterator									find(const Key &key);
			iterator 									lower_bound (const value_type &val) const;
			const_iterator								find(const Key &key) const;
			std::pair<iterator,iterator>				equal_range(const Key &key);
			std::pair<const_iterator,const_iterator>	equal_range(const Key &key) const;
			iterator									lower_bound(const Key &key);
			const_iterator								lower_bound(const Key &key) const;
			iterator									upper_bound(const Key &key);
			const_iterator								upper_bound(const Key &key) const;
			/*Allocator*/
			allocator_type								get_allocator(void) const;

		private :
			red_black_tree<value_type, Alloc, value_compare>	_tree;
			size_type											_size;
			key_compare											_key_comp;
	};

	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/

	template <class T, class Compare, class Alloc>
	set<T, Compare, Alloc>::set(const typename set<T, Compare, Alloc>::key_compare &comp, const typename set<T, Compare, Alloc>::allocator_type &alloc)
	: _tree(_val_comp), _size(0), _key_comp(comp), _val_comp(_key_comp)
	{
		(void)alloc;
	}
	
	template <class T, class Compare, class Alloc>
	template <class InputIterator>
	set<T, Compare, Alloc>::set(InputIterator first, InputIterator last, const set<T, Compare, Alloc>::key_compare &comp, const set<T, Compare, Alloc>::allocator_type &alloc)
	: _tree(_val_comp), _size(0), _key_comp(comp), _val_comp(_key_comp)
	{
		(void)alloc;
		this->insert(first, last);
	}
	
	template <class T, class Compare, class Alloc>
	set<T, Compare, Alloc>::set(const set &x)
	: _tree(x._tree), _size(x.size()), _key_comp(x._key_comp), _val_comp(_key_comp)
	{
		return ;
	}
	
	template <class T, class Compare, class Alloc>
	set<T, Compare, Alloc>::~set() {return ;}
	

	/*
		OPERATOR OVERLOADS
	*/

	template <class T, class Compare, class Alloc>
	set<T, Compare, Alloc>							&set<T, Compare, Alloc>::operator=(const set &other)
	{
		this->_tree = other._tree;
		this->_size = other._size;
	}
	

	/*
		MEMBER FUNCTIONS
	*/
	
	/*Iterators*/ 

	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::iterator					set<T, Compare, Alloc>::begin(void)
	{
		if (!this->_size)
			return this->end();
		return iterator(red_black_node<value_type, value_compare>::get_smallest(this->_tree.get_root()));
	}
	
	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::const_iterator				set<T, Compare, Alloc>::begin(void) const
	{
		if (!this->_size)
			return this->end();
		return static_cast<const_iterator>(iterator(red_black_node<value_type, value_compare>::get_smallest(this->_tree.get_root())));
	}
	
	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::iterator					set<T, Compare, Alloc>::end(void)
	{
		return iterator(this->_tree.get_end());
	}
	
	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::const_iterator				set<T, Compare, Alloc>::end(void) const
	{
		iterator it(this->_tree.get_end());
		return static_cast<const_iterator>(iterator(it));
	}
	
	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::reverse_iterator			set<T, Compare, Alloc>::rbegin(void)
	{
		return reverse_iterator(this->_tree.get_end());
	}
	
	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::const_reverse_iterator		set<T, Compare, Alloc>::rbegin(void) const
	{
		return const_reverse_iterator(this->_tree.get_end());
	}
	
	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::reverse_iterator			set<T, Compare, Alloc>::rend(void)
	{
		return reverse_iterator(red_black_node<value_type, value_compare>::get_smallest(this->_tree.get_root()));
	}
	
	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::const_reverse_iterator		set<T, Compare, Alloc>::rend(void) const
	{
		return const_reverse_iterator(red_black_node<value_type, value_compare>::get_smallest(this->_tree.get_root()));
	}
	
	/*Capacity*/

	template <class T, class Compare, class Alloc>
	bool														set<T, Compare, Alloc>::empty(void) const
	{
		return !this->_size;
	}
	
	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::size_type					set<T, Compare, Alloc>::size(void) const
	{
		return this->_size;
	}
	
	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::size_type					set<T, Compare, Alloc>::max_size(void) const
	{
		return this->_tree.get_alloc().max_size();
	}
	
		
	/*
		NON MEMBER OPERATOR OVERLOADS
	*/
	
	template<class T, class Compare, class Alloc>
	bool	operator==(const ft::set<T,Compare,Alloc> &lhs, const ft::set<T,Compare,Alloc> &rhs)
	{
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin()) && lhs.size() == rhs.size();
	}

	template<class T, class Compare, class Alloc>
	bool	operator!=(const ft::set<T,Compare,Alloc> &lhs, const ft::set<T,Compare,Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template<class T, class Compare, class Alloc>
	bool	operator<(const ft::set<T,Compare,Alloc> &lhs, const ft::set<T,Compare,Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template<class T, class Compare, class Alloc>
	bool	operator<=(const ft::set<T,Compare,Alloc> &lhs, const ft::set<T,Compare,Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	template<class T, class Compare, class Alloc>
	bool	operator>(const ft::set<T,Compare,Alloc> &lhs, const ft::set<T,Compare,Alloc> &rhs)
	{
		return rhs < lhs;
	}

	template<class T, class Compare, class Alloc>
	bool	operator>=(const ft::set<T,Compare,Alloc> &lhs, const ft::set<T,Compare,Alloc> &rhs)
	{
		return !(lhs < rhs);
	}
}

#endif