/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:12:44 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/22 11:57:50 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "../iter/IteratorsTraits.hpp"
# include "../iter/ReverseIterator.hpp"
# include "../util/Pair.hpp"
# include "../util/rbtree/RedBlackTree.hpp"

namespace ft
{
	template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
		typedef Key													key_type;
		typedef T													mapped_type;
		typedef pair<const Key, T>									value_type;
		typedef Compare												key_compare;
		typedef Alloc												allocator_type;
		typedef	typename allocator_type::reference					reference;
		typedef typename allocator_type::const_reference			const_reference;
		typedef typename allocator_type::pointer					pointer;
		typedef typename allocator_type::const_pointer				const_pointer;
		typedef	tree_iterator<value_type>							iterator;
		typedef tree_iterator<const value_type>						const_iterator;
		typedef reverse_iterator<iterator>							reverse_iterator;
		typedef reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef typename iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t												size_type;

		public :
			/*
				CONSTRUCTORS AND DESTRUCTORS
			*/
			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type());
			template <class InputIterator>
  			map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type());	
			map(const map &x);
			~map();
			
			/*
				OPERATOR OVERLOADS
			*/
			map &operator=(const map &x);


			/*
				CLASS
			*/
			class value_compare
			{
				typedef	bool		result_type;
				typedef value_type	first_argument_type;
				typedef value_type	second_argument_type;

				protected :
					key_compare		comp;

					value_compare(key_compare c) : comp(c) {}

				public :
					bool	operator()(const value_type &lhs, const value_type &rhs) {return comp(lhs.first, rhs.first);}
			};
			
			/*
				MEMBER FUNCTIONS
			*/
			/*Iterators*/ 
			iterator							begin(void); //ok
			const_iterator						begin(void) const; //ok
			iterator							end(void); //ok
			const_iterator						end(void) const; //ok
			reverse_iterator					rbegin(void); //ok
			const_reverse_iterator				rbegin(void) const; //ok
			reverse_iterator					rend(void); //ok
			const_reverse_iterator				rend(void) const; //ok
			/*Capacity*/
			bool								empty(void) const;
			size_type							size(void) const;
			size_type							max_size(void) const;
			/*Element access*/
			mapped_type							&operator[](const key_type& k);
			/*Modifiers*/
			pair<iterator,bool>					insert(const value_type& val);
			iterator							insert(iterator position, const value_type& val);
			template <class InputIterator>
			void 								insert(InputIterator first, InputIterator last);
			void								erase(iterator position);
			size_type							erase(const key_type& k);
			void								erase(iterator first, iterator last);
			void								swap(map& x);
			void								clear(void);
			/*Observers*/
			key_compare							key_comp(void) const;
			value_compare						value_comp(void) const;
			/*Operations*/
			iterator							find(const key_type& k);
			const_iterator						find(const key_type& k) const;
			size_type							count(const key_type& k) const;
			iterator							lower_bound(const key_type& k);
			const_iterator						lower_bound(const key_type& k) const;
			iterator							upper_bound(const key_type& k);
			const_iterator						upper_bound(const key_type& k) const;
			pair<const_iterator,const_iterator>	equal_range(const key_type& k) const;
			pair<iterator,iterator>				equal_range (const key_type& k);
			/*Allocator*/
			allocator_type						get_allocator(void) const;

		private :
			red_black_tree<Key, T, Alloc>		_tree;
			size_type							_size;
	};

	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/

	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::map(const typename map<Key, T, Compare, Alloc>::key_compare &comp, const typename map<Key, T, Compare, Alloc>::allocator_type &alloc) {}
	
	template <class Key, class T, class Compare, class Alloc>
	template <class InputIterator>
	map<Key, T, Compare, Alloc>::map(InputIterator first, InputIterator last, const map<Key, T, Compare, Alloc>::key_compare &comp, const map<Key, T, Compare, Alloc>::allocator_type &alloc) {}
	
	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::map(const map &x) {}
	
	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::~map() {}


	/*
		OPERATOR OVERLOADS
	*/
	
	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>										&map<Key, T, Compare, Alloc>::operator=(const map &x) {}

	
	/*
		MEMBER FUNCTIONS
	*/
	/*Iterators*/ 
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator					map<Key, T, Compare, Alloc>::begin(void)
	{
		return iterator(this->_tree->_root->get_smallest());
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator			map<Key, T, Compare, Alloc>::begin(void) const
	{
		return const_iterator(this->_tree->_root->get_smallest());
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator					map<Key, T, Compare, Alloc>::end(void)
	{
		return iterator(this->_end);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator			map<Key, T, Compare, Alloc>::end(void) const
	{
		return const_iterator(this->_end);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::reverse_iterator			map<Key, T, Compare, Alloc>::rbegin(void)
	{
		return reverse_iterator(this->_end);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_reverse_iterator	map<Key, T, Compare, Alloc>::rbegin(void) const
	{
		return const_reverse_iterator(this->_end);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::reverse_iterator			map<Key, T, Compare, Alloc>::rend(void)
	{
		return reverse_iterator(this->_tree->_root->get_smallest());
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_reverse_iterator	map<Key, T, Compare, Alloc>::rend(void) const
	{
		return const_reverse_iterator(this->_tree->_root->get_smallest());
	}

	/*Capacity*/
	template <class Key, class T, class Compare, class Alloc>
	bool															map<Key, T, Compare, Alloc>::empty(void) const
	{
		return !this->_size;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type					map<Key, T, Compare, Alloc>::size(void) const
	{
		return this->_size;
	}
	
	//TO DO
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type					map<Key, T, Compare, Alloc>::max_size(void) const {}

	/*Element access*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::mapped_type				&map<Key, T, Compare, Alloc>::operator[](const key_type& k)
	{
		iterator	it = iterator(this->_tree->_root);
		while (it->get_value().first != k)
			it++;
		return it->get_value().second;
	}
	
	/*Modifiers*/
	
	template <class Key, class T, class Compare, class Alloc>
	pair<typename map<Key, T, Compare, Alloc>::iterator,bool>		map<Key, T, Compare, Alloc>::insert(const value_type& val) {}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator					map<Key, T, Compare, Alloc>::insert(iterator position, const value_type& val) {}
	
	template <class Key, class T, class Compare, class Alloc>
	template <class InputIterator>
	void 															map<Key, T, Compare, Alloc>::insert(InputIterator first, InputIterator last) {}
	
	template <class Key, class T, class Compare, class Alloc>
	void															map<Key, T, Compare, Alloc>::erase(iterator position) {}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type					map<Key, T, Compare, Alloc>::erase(const key_type& k) {}
	
	template <class Key, class T, class Compare, class Alloc>
	void															map<Key, T, Compare, Alloc>::erase(iterator first, iterator last) {}
	
	template <class Key, class T, class Compare, class Alloc>
	void															map<Key, T, Compare, Alloc>::swap(map& x) {}
	
	template <class Key, class T, class Compare, class Alloc>
	void															map<Key, T, Compare, Alloc>::clear() {}
	
	/*Observers*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::key_compare				map<Key, T, Compare, Alloc>::key_comp() const {}
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::value_compare				map<Key, T, Compare, Alloc>::value_comp() const {}
	
	/*Operations*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator					map<Key, T, Compare, Alloc>::find(const key_type& k) {}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator			map<Key, T, Compare, Alloc>::find(const key_type& k) const {}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type					map<Key, T, Compare, Alloc>::count(const key_type& k) const {}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator					map<Key, T, Compare, Alloc>::lower_bound(const key_type& k) {}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator			map<Key, T, Compare, Alloc>::lower_bound(const key_type& k) const {}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator					map<Key, T, Compare, Alloc>::upper_bound(const key_type& k) {}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator			map<Key, T, Compare, Alloc>::upper_bound(const key_type& k) const {}
	
	template <class Key, class T, class Compare, class Alloc>
	pair<typename map<Key, T, Compare, Alloc>::const_iterator,typename map<Key, T, Compare, Alloc>::const_iterator>	map<Key, T, Compare, Alloc>::equal_range(const key_type& k) const {}
	
	template <class Key, class T, class Compare, class Alloc>
	pair<typename map<Key, T, Compare, Alloc>::iterator,typename map<Key, T, Compare, Alloc>::iterator>				map<Key, T, Compare, Alloc>::equal_range (const key_type& k) {}

	/*Allocator*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::allocator_type			map<Key, T, Compare, Alloc>::get_allocator() const {}

	
	/*
		NON MEMBER OPERATOR OVERLOADS
	*/
	
	template< class Key, class T, class Compare, class Alloc >
	bool	operator==(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs ) {}

	template< class Key, class T, class Compare, class Alloc >
	bool	operator!=(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs ) {}

	template< class Key, class T, class Compare, class Alloc >
	bool	operator<(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs ) {}

	template< class Key, class T, class Compare, class Alloc >
	bool	operator<=(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs ) {}

	template< class Key, class T, class Compare, class Alloc >
	bool	operator>(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs ) {}

	template< class Key, class T, class Compare, class Alloc >
	bool	operator>=(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs ) {}
}

#endif