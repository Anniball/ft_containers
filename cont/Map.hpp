/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:12:44 by ldelmas           #+#    #+#             */
/*   Updated: 2022/08/04 11:28:47 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

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
	template <class T, class Compare>
	class red_black_node;

	template <class T, class Node>
	class tree_iterator;

	template <class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class map
	{
		public :
			/*
				CLASSES
			*/
			class value_compare : public ft::binary_function<pair<const Key, T>, pair<const Key, T>, bool>
			{
				friend class map<Key, T, Compare, Alloc>;
				protected:
					Compare _comp;
					value_compare(Compare c) : _comp(c) {}
		
				public:
					bool operator()(const pair<const Key, T>& x, const pair<const Key, T>& y) const { return _comp(x.first, y.first); }
			};

			typedef Key																							key_type;
			typedef T																							mapped_type;
			typedef pair<const Key, T>																			value_type;
			typedef Compare																						key_compare;
			typedef Alloc																						allocator_type;
			typedef	typename allocator_type::reference															reference;
			typedef typename allocator_type::const_reference													const_reference;
			typedef typename allocator_type::pointer															pointer;
			typedef typename allocator_type::const_pointer														const_pointer;
			typedef	typename ft::tree_iterator<value_type, red_black_node<value_type, value_compare> >			iterator;
			typedef typename ft::tree_iterator<const value_type, red_black_node<value_type, value_compare> >	const_iterator;
			typedef typename ft::reverse_iterator<iterator>														reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>												const_reverse_iterator;
			typedef typename iterator_traits<iterator>::difference_type											difference_type;
			typedef size_t																						size_type;

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
			iterator							begin(void); //ok
			const_iterator						begin(void) const; //ok
			iterator							end(void); //ok
			const_iterator						end(void) const; //ok
			reverse_iterator					rbegin(void); //ok
			const_reverse_iterator				rbegin(void) const; //ok
			reverse_iterator					rend(void); //ok
			const_reverse_iterator				rend(void) const; //ok
			/*Capacity*/
			bool								empty(void) const; //ok
			size_type							size(void) const; //ok
			size_type							max_size(void) const; //ok
			/*Element access*/
			mapped_type							&operator[](const key_type& k); //ok
			/*Modifiers*/
			pair<iterator,bool>					insert(const value_type& val); //ok
			iterator							insert(iterator position, const value_type& val); //ok
			template <class InputIterator>
			void 								insert(InputIterator first, InputIterator last); //ok
			void								erase(iterator position); //ok
			size_type							erase(const key_type& k); //ok
			void								erase(iterator first, iterator last); //ok
			void								swap(map& x);
			void								clear(void); //ok
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
			red_black_tree<value_type, Alloc, value_compare>	_tree;
			size_type											_size;
			value_compare										_comp;
	};

	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/

	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::map(const typename map<Key, T, Compare, Alloc>::key_compare &comp, const typename map<Key, T, Compare, Alloc>::allocator_type &alloc)
	{
		(void)comp;
		(void)alloc;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	template <class InputIterator>
	map<Key, T, Compare, Alloc>::map(InputIterator first, InputIterator last, const map<Key, T, Compare, Alloc>::key_compare &comp, const map<Key, T, Compare, Alloc>::allocator_type &alloc)
	: _tree(_comp), _size(0), _comp(key_compare())
	{
		(void)comp;
		(void)alloc;
		for (InputIterator it = first; it != last; it++)
		{
			this->_tree.insert(*it);
			this->_size++;
		}
		// (void)first;
		// (void)last;
		// (void)alloc;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::map(const map &x)
	{
		(void)x;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::~map() {}


	/*
		OPERATOR OVERLOADS
	*/
	
	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>										&map<Key, T, Compare, Alloc>::operator=(const map &x)
	{
		(void)x;
	}

	
	/*
		MEMBER FUNCTIONS
	*/
	/*Iterators*/ 
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator					map<Key, T, Compare, Alloc>::begin(void)
	{

		return iterator(this->_tree.get_root()->get_smallest());
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator			map<Key, T, Compare, Alloc>::begin(void) const
	{
		iterator it = iterator(this->_tree.get_root()->get_smallest());
		return const_iterator(it);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator					map<Key, T, Compare, Alloc>::end(void)
	{
		return iterator(this->_tree.get_end());
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator			map<Key, T, Compare, Alloc>::end(void) const
	{
		iterator it(this->_tree.get_end());
		return const_iterator(it);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::reverse_iterator			map<Key, T, Compare, Alloc>::rbegin(void)
	{
		return reverse_iterator(this->_tree.get_end());
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_reverse_iterator	map<Key, T, Compare, Alloc>::rbegin(void) const
	{
		return const_reverse_iterator(this->_tree.get_end());
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::reverse_iterator			map<Key, T, Compare, Alloc>::rend(void)
	{
		return reverse_iterator(this->_tree.get_root()->get_smallest());
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_reverse_iterator	map<Key, T, Compare, Alloc>::rend(void) const
	{
		return const_reverse_iterator(this->_tree.get_root()->get_smallest());
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
	typename map<Key, T, Compare, Alloc>::size_type					map<Key, T, Compare, Alloc>::max_size(void) const
	{
		return 288230376151711743;
		// return this->_tree.get_alloc().max_size(); //the correct one
	}

	/*Element access*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::mapped_type				&map<Key, T, Compare, Alloc>::operator[](const key_type& k)
	{
		value_type v = value_type(k, mapped_type());
		red_black_node<value_type, value_compare> *tmp = this->_tree.search(v);
		if (tmp)
			return tmp->get_value().second;
		this->_size++;
		return this->_tree.insert(v)->get_value().second;
	}
	
	/*Modifiers*/
	
	template <class Key, class T, class Compare, class Alloc>
	pair<typename map<Key, T, Compare, Alloc>::iterator,bool>		map<Key, T, Compare, Alloc>::insert(const value_type& val)
	{
		this->_tree.insert(val);
		this->_size++;
		return val ;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator					map<Key, T, Compare, Alloc>::insert(iterator position, const value_type& val)
	{
		this->_size++;
		if (this->_comp(*(position - 1), val) && this->_comp(val, *position))
			return iterator(this->_tree.insert(val, position));
		else
			return iterator(this->_tree.insert(val));
	}
	
	template <class Key, class T, class Compare, class Alloc>
	template <class InputIterator>
	void 															map<Key, T, Compare, Alloc>::insert(InputIterator first, InputIterator last)
	{
		while (first != last)
		{
			this->_tree.insert(*first++);
			this->_size++;
		}
	}
	
	template <class Key, class T, class Compare, class Alloc>
	void															map<Key, T, Compare, Alloc>::erase(iterator position) 
	{
		if (this->_tree.erase(*position))
			this->_size--;
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type					map<Key, T, Compare, Alloc>::erase(const key_type& k)
	{
		if (this->_tree.erase(value_type(k, mapped_type())))
			this->_size--;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	void															map<Key, T, Compare, Alloc>::erase(iterator first, iterator last)
	{
		while (first != last)
		{
			if (this->_tree.erase(*first))
				this->_size--;
			first++; //maybe use ft::distance instead
		}
	}
	
	template <class Key, class T, class Compare, class Alloc>
	void															map<Key, T, Compare, Alloc>::swap(map& x)
	{
		(void)x; 
	}
	
	template <class Key, class T, class Compare, class Alloc>
	void															map<Key, T, Compare, Alloc>::clear()
	{
		iterator ite = this->end();
		for (iterator it = this->begin(); it < ite; it++)
			this->_tree.erase(*it);
		this->_size = 0;
	}
	
	/*Observers*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::key_compare				map<Key, T, Compare, Alloc>::key_comp() const {}
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::value_compare				map<Key, T, Compare, Alloc>::value_comp() const {}
	
	/*Operations*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator					map<Key, T, Compare, Alloc>::find(const key_type& k)
	{
		(void)k;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator			map<Key, T, Compare, Alloc>::find(const key_type& k) const
	{
		(void)k;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type					map<Key, T, Compare, Alloc>::count(const key_type& k) const
	{
		(void)k;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator					map<Key, T, Compare, Alloc>::lower_bound(const key_type& k)
	{
		(void)k;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator			map<Key, T, Compare, Alloc>::lower_bound(const key_type& k) const
	{
		(void)k;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator					map<Key, T, Compare, Alloc>::upper_bound(const key_type& k)
	{
		(void)k;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator			map<Key, T, Compare, Alloc>::upper_bound(const key_type& k) const
	{
		(void)k;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	pair<typename map<Key, T, Compare, Alloc>::const_iterator,typename map<Key, T, Compare, Alloc>::const_iterator>	map<Key, T, Compare, Alloc>::equal_range(const key_type& k) const
	{
		(void)k;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	pair<typename map<Key, T, Compare, Alloc>::iterator,typename map<Key, T, Compare, Alloc>::iterator>				map<Key, T, Compare, Alloc>::equal_range (const key_type& k)
	{
		(void)k;
	}

	/*Allocator*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::allocator_type			map<Key, T, Compare, Alloc>::get_allocator() const {}

	
	/*
		NON MEMBER OPERATOR OVERLOADS
	*/
	
	// template< class Key, class T, class Compare, class Alloc >
	// bool	operator==(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs ) {}

	// template< class Key, class T, class Compare, class Alloc >
	// bool	operator!=(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs ) {}

	// template< class Key, class T, class Compare, class Alloc >
	// bool	operator<(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs ) {}

	// template< class Key, class T, class Compare, class Alloc >
	// bool	operator<=(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs ) {}

	// template< class Key, class T, class Compare, class Alloc >
	// bool	operator>(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs ) {}

	// template< class Key, class T, class Compare, class Alloc >
	// bool	operator>=(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs ) {}
}

#endif