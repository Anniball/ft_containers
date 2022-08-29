/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:12:44 by ldelmas           #+#    #+#             */
/*   Updated: 2022/08/29 15:02:55 by ldelmas          ###   ########.fr       */
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

	template <class T, class Compare, class Node>
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
					value_compare(Compare c) : _comp(c) {return ;}
		
				public:
					bool operator()(const pair<const Key, T>& x, const pair<const Key, T>& y) const { return _comp(x.first, y.first); }
			};

			typedef Key																												key_type;
			typedef T																												mapped_type;
			typedef pair<const Key, T>																								value_type;
			typedef Compare																											key_compare;
			typedef Alloc																											allocator_type;
			typedef	typename allocator_type::reference																				reference;
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
			explicit map(const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type());
			template <class InputIterator>
  			map(InputIterator first, InputIterator last, const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type());	
			map(const map &x);
			~map(void);
			
			/*
				OPERATOR OVERLOADS
			*/
			map	&operator=(const map &x);

			
			/*
				MEMBER FUNCTIONS
			*/
			/*Iterators*/ 
			iterator							begin(void);
			const_iterator						begin(void) const;
			iterator							end(void);
			const_iterator						end(void) const;
			reverse_iterator					rbegin(void);
			const_reverse_iterator				rbegin(void) const;
			reverse_iterator					rend(void);
			const_reverse_iterator				rend(void) const;
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
			pair<iterator,iterator>				equal_range(const key_type& k);
			/*Allocator*/
			allocator_type						get_allocator(void) const;

		private :
			red_black_tree<value_type, Alloc, value_compare>	_tree;
			size_type											_size;
			key_compare											_key_comp;
			value_compare										_val_comp;
	};

	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/

	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::map(const typename map<Key, T, Compare, Alloc>::key_compare &comp, const typename map<Key, T, Compare, Alloc>::allocator_type &alloc)
	: _tree(_val_comp), _size(0), _key_comp(comp), _val_comp(_key_comp)
	{
		(void)alloc;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	template <class InputIterator>
	map<Key, T, Compare, Alloc>::map(InputIterator first, InputIterator last, const map<Key, T, Compare, Alloc>::key_compare &comp, const map<Key, T, Compare, Alloc>::allocator_type &alloc)
	: _tree(_val_comp), _size(0), _key_comp(comp), _val_comp(_key_comp)
	{
		(void)alloc;
		this->insert(first, last);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::map(const map &x)
	: _tree(x._tree), _size(x.size()), _key_comp(x._key_comp), _val_comp(_key_comp)
	{
		return ;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>::~map(void) {return ;}


	/*
		OPERATOR OVERLOADS
	*/
	
	template <class Key, class T, class Compare, class Alloc>
	map<Key, T, Compare, Alloc>										&map<Key, T, Compare, Alloc>::operator=(const map &x)
	{
		this->_tree = x._tree;
		this->_size = x._size;
		return *this;
	}

	
	/*
		MEMBER FUNCTIONS
	*/
	
	/*Iterators*/ 

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator					map<Key, T, Compare, Alloc>::begin(void)
	{
		if (!this->_size)
			return this->end();
		return iterator(red_black_node<value_type, value_compare>::get_smallest(this->_tree.get_root()));
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator			map<Key, T, Compare, Alloc>::begin(void) const
	{
		if (!this->_size)
			return this->end();
		return static_cast<const_iterator>(iterator(red_black_node<value_type, value_compare>::get_smallest(this->_tree.get_root())));
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
		return static_cast<const_iterator>(iterator(it));
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
		return reverse_iterator(red_black_node<value_type, value_compare>::get_smallest(this->_tree.get_root()));
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_reverse_iterator	map<Key, T, Compare, Alloc>::rend(void) const
	{
		return const_reverse_iterator(red_black_node<value_type, value_compare>::get_smallest(this->_tree.get_root()));
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
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type					map<Key, T, Compare, Alloc>::max_size(void) const
	{
		return this->_tree.get_alloc().max_size();
	}

	/*Element access*/

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::mapped_type				&map<Key, T, Compare, Alloc>::operator[](const key_type& k)
	{
		value_type v = value_type(k, mapped_type());
		iterator it = iterator(this->_tree.search(v));
		iterator ite = this->end();
		if (it != ite)
			return it->second;
		this->_size++;
		return this->_tree.insert(v).first->get_value().second;
	}
	
	/*Modifiers*/

	template <class Key, class T, class Compare, class Alloc>
	pair<typename map<Key, T, Compare, Alloc>::iterator,bool>		map<Key, T, Compare, Alloc>::insert(const value_type& val)
	{
		pair<red_black_node<value_type, value_compare>*, bool> tmp = this->_tree.insert(val);
		pair<iterator, bool> itp(iterator(tmp.first), tmp.second);
		if (itp.second)
			this->_size++;
		return itp;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator					map<Key, T, Compare, Alloc>::insert(iterator position, const value_type& val)
	{
		pair<red_black_node<value_type, value_compare>*, bool> tmp;
		if (position != this->begin() && position != this->end() && this->_val_comp(*(--position), val) && this->_val_comp(val, *(++position)))
			tmp = this->_tree.insert(val, position);
		else
			tmp = this->_tree.insert(val);
		if (tmp.second)
			this->_size++;
		return iterator(tmp.first);
	}
	
	template <class Key, class T, class Compare, class Alloc>
	template <class InputIterator>
	void 															map<Key, T, Compare, Alloc>::insert(InputIterator first, InputIterator last)
	{
		while (first != last)
		{
			pair<red_black_node<value_type, value_compare>*, bool> tmp = this->_tree.insert(*first++);
			if (tmp.second)
				this->_size++;
		}
		return ;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	void															map<Key, T, Compare, Alloc>::erase(iterator position) 
	{
		if (this->_tree.erase(*position))
			this->_size--;
		return ;
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type					map<Key, T, Compare, Alloc>::erase(const key_type& k)
	{
		value_type val(value_type(k, mapped_type()));
		if (this->_tree.erase(val))
		{
			this->_size--;
			return 1;
		}
		return 0;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	void															map<Key, T, Compare, Alloc>::erase(iterator first, iterator last)
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
	
	template <class Key, class T, class Compare, class Alloc>
	void															map<Key, T, Compare, Alloc>::swap(map& x)
	{
		this->_tree.swap_content(x._tree);
		size_type tmp = x._size;
		x._size = this->_size;
		this->_size = tmp;
		return ;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	void															map<Key, T, Compare, Alloc>::clear()
	{
		this->_tree.clear();
		this->_size = 0;
		return ;
	}
	
	/*Observers*/

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::key_compare				map<Key, T, Compare, Alloc>::key_comp(void) const
	{
		return this->_key_comp;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::value_compare				map<Key, T, Compare, Alloc>::value_comp(void) const
	{
		return this->_val_comp;
	}
	
	/*Operations*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator					map<Key, T, Compare, Alloc>::find(const key_type& k)
	{
		value_type val(k, mapped_type());
		return iterator(this->_tree.search(val));
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator			map<Key, T, Compare, Alloc>::find(const key_type& k) const
	{
		value_type val(k, mapped_type());
		return static_cast<const_iterator>(iterator(this->_tree.search(val)));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::size_type					map<Key, T, Compare, Alloc>::count(const key_type& k) const
	{
		value_type val(k, mapped_type());
		if (this->_tree.search(val) == this->_tree.get_end())
			return 0;
		return 1;
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator					map<Key, T, Compare, Alloc>::lower_bound(const key_type& k)
	{
		value_type val(k, mapped_type());
		return iterator(this->_tree.search_lower_bound(val));
	}

	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator			map<Key, T, Compare, Alloc>::lower_bound(const key_type& k) const
	{
		value_type val(k, mapped_type());
		return static_cast<const_iterator>(iterator(this->_tree.search_lower_bound(val)));
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::iterator					map<Key, T, Compare, Alloc>::upper_bound(const key_type& k)
	{
		value_type val(k, mapped_type());
		return iterator(this->_tree.search_upper_bound(val));
	}
	
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::const_iterator			map<Key, T, Compare, Alloc>::upper_bound(const key_type& k) const
	{
		value_type val(k, mapped_type());
		return static_cast<const_iterator>(iterator(this->_tree.search_upper_bound(val)));
	}
	
	template <class Key, class T, class Compare, class Alloc>
	pair<typename map<Key, T, Compare, Alloc>::const_iterator,typename map<Key, T, Compare, Alloc>::const_iterator>	map<Key, T, Compare, Alloc>::equal_range(const key_type& k) const
	{
		value_type	val(k, mapped_type());
		return pair<const_iterator, const_iterator>(iterator(this->_tree.search_lower_bound(val)), iterator(this->_tree.search_upper_bound(val)));
	}
	
	template <class Key, class T, class Compare, class Alloc>
	pair<typename map<Key, T, Compare, Alloc>::iterator,typename map<Key, T, Compare, Alloc>::iterator>				map<Key, T, Compare, Alloc>::equal_range (const key_type& k)
	{
		value_type	val(k, mapped_type());
		return pair<iterator, iterator>(this->_tree.search_lower_bound(val), this->_tree.search_upper_bound(val));
	}

	/*Allocator*/
	template <class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::allocator_type			map<Key, T, Compare, Alloc>::get_allocator() const
	{
		return allocator_type();
	}

	
	/*
		NON MEMBER OPERATOR OVERLOADS
	*/
	
	template< class Key, class T, class Compare, class Alloc >
	bool	operator==(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin()) && lhs.size() == rhs.size();
	}

	template< class Key, class T, class Compare, class Alloc >
	bool	operator!=(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool	operator<(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template< class Key, class T, class Compare, class Alloc >
	bool	operator<=(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool	operator>(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return rhs < lhs;
	}

	template< class Key, class T, class Compare, class Alloc >
	bool	operator>=(const ft::map<Key,T,Compare,Alloc> &lhs, const ft::map<Key,T,Compare,Alloc> &rhs)
	{
		return !(lhs < rhs);
	}
}

#endif