/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:12:44 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/12 14:30:39 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include "../iter/IteratorsTraits.hpp"
# include "../iter/ReverseIterator.hpp"
# include "../util/Pair.hpp"

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
		typedef	ft::iterator_traits<value_type>						iterator;
		typedef ft::iterator_traits<const value_type>				const_iterator;
		typedef ft::reverse_iterator<iterator>						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
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
				MEMBER FUNCTIONS
			*/
			/*Iterators*/ 
			iterator							begin();
			const_iterator						begin() const;
			iterator							end();
			const_iterator						end() const;
			reverse_iterator					rbegin();
			const_reverse_iterator				rbegin() const;
			reverse_iterator					rend();
			const_reverse_iterator				rend() const;
			/*Capacity*/
			bool								empty() const;
			size_type							size() const;
			size_type							max_size() const;
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
			void								clear();
			/*Observers*/
			key_compare							key_comp() const;
			value_compare						value_comp() const;
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
			allocator_type						get_allocator() const;
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
	typename map<Key, T, Compare, Alloc>::iterator					map<Key, T, Compare, Alloc>::begin() {}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator			map<Key, T, Compare, Alloc>::begin() const {}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator					map<Key, T, Compare, Alloc>::end() {}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator			map<Key, T, Compare, Alloc>::end() const {}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::reverse_iterator			map<Key, T, Compare, Alloc>::rbegin() {}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_reverse_iterator	map<Key, T, Compare, Alloc>::rbegin() const {}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::reverse_iterator			map<Key, T, Compare, Alloc>::rend() {}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_reverse_iterator	map<Key, T, Compare, Alloc>::rend() const {}

	/*Capacity*/
	template <class Key, class T, class Compare, class Alloc>
	bool															map<Key, T, Compare, Alloc>::empty() const {}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type					map<Key, T, Compare, Alloc>::size() const {}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type					map<Key, T, Compare, Alloc>::max_size() const {}

	/*Element access*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::mapped_type				&map<Key, T, Compare, Alloc>::operator[](const key_type& k) {}
	
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