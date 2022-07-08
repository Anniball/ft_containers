/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:13:41 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/08 17:24:07 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iostream>
# include <stdexcept>
# include <cmath>
# include "../iter/IteratorsTraits.hpp"
# include "../iter/ReverseIterator.hpp"

namespace ft
{
	template<typename T, class Alloc = std::allocator<T> >
	class vector
	{
		typedef				T												value_type;
		typedef				Alloc											allocator_type;
		typedef				value_type&										reference;
		typedef				const value_type&								const_reference;
		typedef				value_type*										pointer;
		typedef				const value_type*								const_pointer;
		typedef	typename	ft::iterator_traits<value_type>					iterator;
		typedef	typename	ft::iterator_traits<const value_type>			const_iterator;
		typedef	typename	ft::reverse_iterator<iterator>					reverse_iterator;
		typedef	typename	ft::reverse_iterator<const_iterator>			const_reverse_iterator;
		typedef	typename	iterator_traits<iterator>::difference_type		difference_type;
		typedef size_t														size_type;

		private:
			pointer			_container;
			size_type		_size;
			size_type		_capacity;
			allocator_type	_alloc;
			
		public:
			/*
				CONSTRUCTORS AND DESTRUCTORS
			*/
			explicit vector (const allocator_type& alloc = allocator_type());
			explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type());
			vector (const vector& x);
			~vector(void);

			/*
				OPERATOR OVERLOADS
			*/
			vector			&operator=(const vector& x);
			reference		operator[](size_type n); //ok
			const_reference	operator[](size_type n) const; //ok

			/*
				MEMBER FUNCTIONS
			*/
			/*Iterators*/
			iterator				begin(void); //ok
			const_iterator			begin(void) const; //ok
			iterator				end(void); //ok
			const_iterator			end(void) const; //ok
			reverse_iterator		rbegin(void); //ok
			const_reverse_iterator	rbegin(void) const; //ok
			reverse_iterator		rend(void); //ok
			const_reverse_iterator	rend(void) const; //ok
			/*Capacity*/
			size_type				size(void) const; //ok
			size_type				max_size(void) const; //ok
			void					resize(size_type n, value_type val = value_type()); //ok
			size_type				capacity(void) const; //ok
			bool					empty(void) const; //ok
			void					reserve(size_type n); //ok
			/*Element access*/
			reference				at(size_type n); //ok
			const_reference			at(size_type n) const; //ok
			reference				front(void); //ok
			const_reference			front(void) const; //ok
			reference				back(void); //ok
			const_reference			back(void) const; //ok
			/*Modifiers*/
			template<class InputIterator>
			void 					assign(InputIterator first, InputIterator last); //ok
			void					assign(size_type n, const value_type &val); // ok
			void					push_back(const value_type &val); //ok
			void					pop_back(void); //ok
			iterator				insert(iterator position, const value_type &val); //ok
			void					insert(iterator position, size_type n, const value_type &val); //ok
			template<class InputIterator>
			void					insert(iterator position, InputIterator first, InputIterator last);
			iterator				erase(iterator position);
			iterator				erase(iterator first, iterator last);
			void					swap(vector &x);
			void					clear(void); //ok
			/*Allocator*/
			allocator_type			get_allocator(void) const;
	};

	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/

	template<typename T, class Alloc>
	vector<T, Alloc>::vector(const allocator_type& alloc) : _container(nullptr), _size(0), _capacity(0) {}

	//STILL TO DO
	template<typename T, class Alloc>
	vector<T, Alloc>::vector(size_type n, const value_type& val, const allocator_type& alloc) {}
	
	//STILL TO DO
	template <typename T, class Alloc>
	template <class InputIterator>
	vector<T, Alloc>::vector(InputIterator first, InputIterator last, const allocator_type& alloc){}
	
	//STILL TO DO
	template <typename T, class Alloc>
	vector<T, Alloc>::vector(const vector& x){}
	
	//STILL TO DO
	template <typename T, class Alloc>
	vector<T, Alloc>::~vector(void){}

	/*
		OPERATOR OVERLOADS
	*/

	//STILL TO DO
	template<typename T, class Alloc>
	vector<T, Alloc>							&vector<T, Alloc>::operator=(const vector& x){}

	template<typename T, class Alloc>
	typename vector<T, Alloc>::reference		vector<T, Alloc>::operator[](size_type n)
	{
		return (this->_container[n]);
	}

	template<typename T, class Alloc>
	typename vector<T, Alloc>::const_reference	vector<T, Alloc>::operator[](size_type n) const
	{
		return (this->_container[n]);
	}


	/*
		MEMBER FUNCTIONS
	*/
	/*Iterators*/
	template<typename T, class Alloc>
	typename vector<T, Alloc>::iterator					vector<T, Alloc>::begin(void)
	{
		return (vector<T, Alloc>::iterator(this->_container));
	}

	template<typename T, class Alloc>
	typename vector<T, Alloc>::const_iterator			vector<T, Alloc>::begin(void) const
	{
		return (vector<T, Alloc>::const_iterator(this->_container));
	}

	template<typename T, class Alloc>
	typename vector<T, Alloc>::iterator					vector<T, Alloc>::end(void)
	{
		return (vector<T, Alloc>::iterator(this->_container + this->_size));
	}

	template<typename T, class Alloc>
	typename vector<T, Alloc>::const_iterator			vector<T, Alloc>::end(void) const
	{
		return (vector<T, Alloc>::const_iterator(this->_container + this->_size));
	}

	template<typename T, class Alloc>
	typename vector<T, Alloc>::reverse_iterator			vector<T, Alloc>::rbegin(void)
	{
		return reverse_iterator(this->end());
	}

	template<typename T, class Alloc>
	typename vector<T, Alloc>::const_reverse_iterator	vector<T, Alloc>::rbegin(void) const
	{
		return const_reverse_iterator(this->end());
	}

	template<typename T, class Alloc>
	typename vector<T, Alloc>::reverse_iterator			vector<T, Alloc>::rend(void)
	{
		return reverse_iterator(this->begin());
	}

	template<typename T, class Alloc>
	typename vector<T, Alloc>::const_reverse_iterator	vector<T, Alloc>::rend(void) const
	{
		return const_reverse_iterator(this->begin());
	}

	/*Capacity*/
	template<typename T, class Alloc>
	typename vector<T, Alloc>::size_type					vector<T, Alloc>::size(void) const
	{
		return (this->_size);
	}

	//STILL TO CHANGE
	template<typename T, class Alloc>
	typename vector<T, Alloc>::size_type					vector<T, Alloc>::max_size(void) const
	{
		return (static_cast<size_type>((pow(2, 64) / static_cast<double>(sizeof(value_type))) - 1));
	}

	template<typename T, class Alloc>
	void													vector<T, Alloc>::resize(size_type n, value_type val)
	{
		if (n > this->max_size())
			throw std::out_of_range("vector::resize");
		this->reserve(n);
		for (size_type i = this->_size; i < n; i++)
			this->_alloc.construct(this->_container + i, val);
		for (size_type i = this->size - 1; i >= n; i--)
			this->_alloc.destroy(this->_container + i);
		this->_size = n;
	}

	template<typename T, class Alloc>
	typename vector<T, Alloc>::size_type					vector<T, Alloc>::capacity(void) const
	{
		return (this->_capacity);
	}

	template<typename T, class Alloc>
	bool													vector<T, Alloc>::empty(void) const
	{
		return (this->_size == 0);
	}

	template<typename T, class Alloc>
	void													vector<T, Alloc>::reserve(size_type n)
	{
		if (n > this->max_size())
			throw std::out_of_range("vector::reserve");
		else if (this->_capacity >= n)
			return ;
		pointer tmp = this->_alloc.allocate(n);
		for (size_type i = 0; i < this->_size; i++)
		{
			this->_alloc.construct(tmp + i, this->_container[i]);
			this->_alloc.destroy(this->_container + i);
		}
		this->_alloc.deallocate(this->_container, this->_capacity);
		this->_container = tmp;
		this->_capacity = n;
	}

	/*Element access*/
	template<typename T, class Alloc>
	typename vector<T, Alloc>::reference					vector<T, Alloc>::at(size_type n)
	{
		if (n >= this->_size)
			throw std::out_of_range("vector::at");
		return (this->_container[n]);
	}

	template<typename T, class Alloc>
	typename vector<T, Alloc>::const_reference				vector<T, Alloc>::at(size_type n) const
	{
		if (n >= this->_size)
			throw std::out_of_range("vector::at");
		return (this->_container[n]);
	}

	template<typename T, class Alloc>
	typename vector<T, Alloc>::reference					vector<T, Alloc>::front(void)
	{
		return (*this->_container);
	}
	
	template<typename T, class Alloc>
	typename vector<T, Alloc>::const_reference				vector<T, Alloc>::front(void) const
	{
		return (*this->_container);
	}
	
	template<typename T, class Alloc>
	typename vector<T, Alloc>::reference					vector<T, Alloc>::back(void)
	{
		return (this->_container[this->_size - 1]);	
	}
	
	template<typename T, class Alloc>
	typename vector<T, Alloc>::const_reference				vector<T, Alloc>::back(void) const
	{
		return (this->_container[this->_size - 1]);
	}

	/*Modifiers*/
	template<typename T, class Alloc>
	template<class InputIterator>
	void 													vector<T, Alloc>::assign(InputIterator first, InputIterator last)
	{
		size_type size = distance(first, last);
		this->clear();
		if (size > this->_capacity)
		{
			this->_alloc.deallocate(this->_container, this->_capacity);
			this->_container = this->_alloc.allocate(size);
			this->_capacity = size;
		}
		for (size_type i = 0; i < size; i++)
			this->_alloc.construct(this->_container + i, first++);
	}

	template<typename T, class Alloc>
	void													vector<T, Alloc>::assign(size_type n, const value_type &val)
	{
		this->clear();
		if (n > this->_capacity)
		{
			this->_alloc.deallocate(this->_container, this->_capacity);
			this->_container = this->_alloc.allocate(n);
			this->_capacity = n;
		}
		while (--n > 0)
			this->_alloc.construct(this->_container + n, val);
	}

	template<typename T, class Alloc>
	void													vector<T, Alloc>::push_back(const value_type &val)
	{
		if (this->_size + 1 > this->_capacity)
			this->reserve(!this->_capacity ? 1 : this->_capacity * 2);
		this->_alloc.construct(this->_size, val);
		this->_size++;
	}

	template<typename T, class Alloc>
	void													vector<T, Alloc>::pop_back(void)
	{
		if (!this->_size)
			return ;
		this->_alloc.destroy(this->_container + this->_size - 1);
		this->_size--;
	}

	template<typename T, class Alloc>
	typename vector<T, Alloc>::iterator						vector<T, Alloc>::insert(vector<T, Alloc>::iterator position, const vector<T, Alloc>::value_type &val)
	{
		insert(position, 1, val);
		return this->begin() + (distance(this->begin(), position));
	}

	template<typename T, class Alloc>
	void													vector<T, Alloc>::insert(vector<T, Alloc>::iterator position, size_type n, const value_type &val)
	{
		size_type pos = distance(this->_begin(), position);
		if (this->_size + n > this->_capacity)
		{
			size_type size = 2;
			while (this->_capacity * size < this->_size + n)
				size *= 2;
			if (this->_capacity * size > this->max_size())
				throw std::out_of_range("vector::insert");
			pointer tmp = this->_alloc.allocate(this->_capacity * size);
			for (size_type i = 0; i < pos; i++)
			{
				this->_alloc.construct(tmp + i, this->_container[i]);
				this->_alloc.destroy(this->_container + i);
			}
			for (size_type i = 0; i < n; i++)
				this->_alloc.construct(tmp + pos + i, val);
			for (size_type i = pos; i < this->_size; i++)
			{
				this->_alloc.construct(tmp + i + n, this->_container[i]);
				this->_alloc.destroy(this->_container + i);
			}
			this->_alloc.deallocate(this->_container);
			this->_container = tmp;
			this->_capacity = this->_capacity * size;
		}
		else
		{
			for (size_type i = pos; i < this->_size; i++)
				this->_container[i+n] = this->_container[i];
			for (size_type i = pos; i < pos+n; i++)
				this->_alloc(this->_container + i, val);
		}
		this->_size += n;
	}

	template<typename T, class Alloc>
	template<class InputIterator>
	void					vector<T, Alloc>::insert(typename vector<T, Alloc>::iterator position, InputIterator first, InputIterator last)
	{
		typename vector<T, Alloc>::size_type pos = distance(this->begin(), position);
		typename vector<T, Alloc>::size_type dist = distance(first, last);
		if (this->_size + dist > this->_capacity)
		{
			size_type size = 2;
			while (this->_capacity * size < this->_size + dist)
				size *= 2;
			if (this->_capacity * size > this->max_size())
				throw std::out_of_range("vector::insert");
			pointer tmp = this->_alloc.allocate(this->_capacity * size);
			for (size_type i = 0; i < pos; i++)
			{
				this->_alloc.construct(tmp + i, this->_container[i]);
				this->_alloc.destroy(this->_container + i);
			}
			for (size_type i = 0; i < dist; i++)
				this->_alloc.construct(tmp + pos + i, first++);
			for (size_type i = pos; i < this->_size; i++)
			{
				this->_alloc.construct(tmp + i + dist, this->_container[i]);
				this->_alloc.destroy(this->_container + i);
			}
			this->_alloc.deallocate(this->_container);
			this->_container = tmp;
			this->_capacity = this->_capacity * size;
		}
		else
		{
			for (size_type i = pos; i < this->_size; i++)
				this->_container[i + dist] = this->_container[i];
			for (size_type i = pos; i < pos + dist; i++)
				this->_alloc(this->_container + i, first);
		}
		this->_size += dist;
	}

	// template<typename T, class Alloc>
	// iterator				erase(iterator position);

	// template<typename T, class Alloc>
	// iterator				erase(iterator first, iterator last);

	// template<typename T, class Alloc>
	// void					swap(vector &x);

	//MAYBE OK
	template<typename T, class Alloc>
	void													vector<T, Alloc>::clear(void)
	{
		for (int i = 0; i < this->_size; i++)
			this->_alloc.destroy(this->_container + i);
		this->_size = 0;
	}

	
	/*
		NON-MEMBER FUNCTIONS
	*/
	/*Relational operators*/
	template <class T, class Alloc>
  	bool	operator==(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	bool	operator!=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
	template <class T, class Alloc>
  	bool	operator<(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	bool	operator<=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	bool	operator>(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
	template <class T, class Alloc>
	bool	operator>=(const vector<T, Alloc>& lhs, const vector<T, Alloc>& rhs);
	/*swap*/
	template <class T, class Alloc>
	void	swap(vector<T, Alloc> &x, vector<T, Alloc> &y);
}

#endif