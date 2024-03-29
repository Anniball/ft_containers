/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Set.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 16:35:11 by ldelmas           #+#    #+#             */
/*   Updated: 2022/08/30 14:15:49 by ldelmas          ###   ########.fr       */
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
			typedef Compare																											value_compare;
			typedef Alloc																											allocator_type;
			typedef typename allocator_type::reference																				reference;
			typedef typename allocator_type::const_reference																		const_reference;
			typedef typename allocator_type::pointer																				pointer;
			typedef typename allocator_type::const_pointer																			const_pointer;
			typedef	typename ft::tree_iterator<const value_type, value_compare, red_black_node<const value_type, value_compare> >	iterator;
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
			iterator									begin(void) const ;
			iterator									end(void) const ;
			reverse_iterator							rbegin(void) const;
			reverse_iterator 							rend(void) const;
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
			iterator									find(const key_type &k) const;
			size_type									count(const key_type &k) const;
			iterator									lower_bound(const key_type &k) const;
			iterator									upper_bound(const key_type &k) const;
			ft::pair<iterator,iterator>					equal_range(const key_type &k) const;
			/*Allocator*/
			allocator_type								get_allocator(void) const;

		private :
			red_black_tree<const value_type, Alloc, value_compare>	_tree;
			size_type												_size;
			key_compare												_key_comp;
	};

	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/

	template <class T, class Compare, class Alloc>
	set<T, Compare, Alloc>::set(const typename set<T, Compare, Alloc>::key_compare &comp, const typename set<T, Compare, Alloc>::allocator_type &alloc)
	: _tree(_key_comp), _size(0), _key_comp(comp)
	{
		(void)alloc;
	}
	
	template <class T, class Compare, class Alloc>
	template <class InputIterator>
	set<T, Compare, Alloc>::set(InputIterator first, InputIterator last, const set<T, Compare, Alloc>::key_compare &comp, const set<T, Compare, Alloc>::allocator_type &alloc)
	: _tree(_key_comp), _size(0), _key_comp(comp)
	{
		(void)alloc;
		this->insert(first, last);
	}
	
	template <class T, class Compare, class Alloc>
	set<T, Compare, Alloc>::set(const set &x)
	: _tree(x._tree), _size(x.size()), _key_comp(x._key_comp)
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
		return *this;
	}
	

	/*
		MEMBER FUNCTIONS
	*/
	
	/*Iterators*/ 

	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::iterator					set<T, Compare, Alloc>::begin(void) const
	{
		if (!this->_size)
			return this->end();
		return iterator(red_black_node<const value_type, value_compare>::get_smallest(this->_tree.get_root()));
	}
	
	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::iterator					set<T, Compare, Alloc>::end(void) const
	{
		return iterator(this->_tree.get_end());
	}
	
	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::reverse_iterator			set<T, Compare, Alloc>::rbegin(void) const
	{
		return reverse_iterator(this->_tree.get_end());
	}
	
	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::reverse_iterator			set<T, Compare, Alloc>::rend(void) const
	{
		return reverse_iterator(red_black_node<const value_type, value_compare>::get_smallest(this->_tree.get_root()));
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
		
	/*Modifiers*/

	template <class T, class Compare, class Alloc>
	pair<typename set<T, Compare, Alloc>::iterator,bool>		set<T, Compare, Alloc>::insert(const value_type& val)
	{
		pair<red_black_node<const value_type, value_compare>*, bool> tmp = this->_tree.insert(val);
		pair<iterator, bool> itp(iterator(tmp.first), tmp.second);
		if (itp.second)
			this->_size++;
		return itp;
	}
	
	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::iterator					set<T, Compare, Alloc>::insert(iterator position, const value_type& val)
	{
		pair<red_black_node<const value_type, value_compare>*, bool> tmp;
		if (position != this->begin() && position != this->end() && this->_key_comp(*(--position), val) && this->_key_comp(val, *(++position)))
			tmp = this->_tree.insert(val, position);
		else
			tmp = this->_tree.insert(val);
		if (tmp.second)
			this->_size++;
		return iterator(tmp.first);
	}
	
	template <class T, class Compare, class Alloc>
	template <class InputIterator>
	void 														set<T, Compare, Alloc>::insert(InputIterator first, InputIterator last)
	{
		while (first != last)
		{
			pair<red_black_node<const value_type, value_compare>*, bool> tmp = this->_tree.insert(*first++);
			if (tmp.second)
				this->_size++;
		}
		return ;
	}
	
	template <class T, class Compare, class Alloc>
	void														set<T, Compare, Alloc>::erase(iterator position) 
	{
		if (this->_tree.erase(*position))
			this->_size--;
		return ;
	}

	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::size_type					set<T, Compare, Alloc>::erase(const key_type& k)
	{
		if (this->_tree.erase(k))
		{
			this->_size--;
			return 1;
		}
		return 0;
	}
	
	template <class T, class Compare, class Alloc>
	void														set<T, Compare, Alloc>::erase(iterator first, iterator last)
	{
		while (first != last)
		{
			iterator tmp = first;
			++first;
			if (this->_tree.erase(*tmp))
				this->_size--;
		}
		return ;
	}
	
	template <class T, class Compare, class Alloc>
	void														set<T, Compare, Alloc>::swap(set &x)
	{
		this->_tree.swap_content(x._tree);
		size_type tmp = x._size;
		x._size = this->_size;
		this->_size = tmp;
		return ;
	}
	
	template <class T, class Compare, class Alloc>
	void														set<T, Compare, Alloc>::clear(void)
	{
		this->_tree.clear();
		this->_size = 0;
		return ;
	}

	/*Observers*/

	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::key_compare				set<T, Compare, Alloc>::key_comp(void) const
	{
		return this->_key_comp;
	}
	
	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::value_compare				set<T, Compare, Alloc>::value_comp(void) const
	{
		return this->_key_comp;
	}

	/*Operations*/
	
	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::iterator					set<T, Compare, Alloc>::find(const key_type &k) const
	{
		return iterator(this->_tree.search(k));
	}

	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::size_type					set<T, Compare, Alloc>::count(const key_type &k) const
	{
		if (this->_tree.search(k) == this->_tree.get_end())
			return 0;
		return 1;
	}
	
	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::iterator					set<T, Compare, Alloc>::lower_bound(const key_type &k) const
	{
		return iterator(this->_tree.search_lower_bound(k));
	}
	
	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::iterator					set<T, Compare, Alloc>::upper_bound(const key_type &k) const
	{
		return iterator(this->_tree.search_upper_bound(k));
	}
	
	template <class T, class Compare, class Alloc>
	pair<typename set<T, Compare, Alloc>::iterator,typename set<T, Compare, Alloc>::iterator>	set<T, Compare, Alloc>::equal_range(const key_type &k) const
	{
		return pair<const_iterator, const_iterator>(iterator(this->_tree.search_lower_bound(k)), iterator(this->_tree.search_upper_bound(k)));
	}
	
	/*Allocator*/
	template <class T, class Compare, class Alloc>
	typename set<T, Compare, Alloc>::allocator_type			set<T, Compare, Alloc>::get_allocator(void) const
	{
		return allocator_type();
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