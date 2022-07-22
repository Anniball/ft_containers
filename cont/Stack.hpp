/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:14:33 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/22 10:11:37 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "Vector.hpp"

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{
		public :
			typedef T				value_type;
			typedef Container		container_type;
			typedef size_t			size_type;
			typedef T&				reference;
			typedef const T&		const_reference;

		protected :
			Container 			c;
			
		public :
			/*
				CONSTRUCTORS AND DESTRUCTORS
			*/
			explicit stack(const container_type& ctnr = container_type());
			
			/*
				MEMBER FUNCTIONS
			*/
			bool				empty() const;
			size_type			size() const;
			value_type&			top();
			const value_type&	top() const;
			void 				push (const value_type& val);
			void 				pop();
	};

	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/
	template <class T, class Container>
	stack<T, Container>::stack(const typename stack<T, Container>::container_type &ctnr) : c(ctnr) {}

	/*
		MEMBER FUNCTIONS
	*/

	
	template <class T, class Container>
	bool												stack<T, Container>::empty() const
	{
		return c.empty();
	}
	
	template <class T, class Container>
	typename stack<T, Container>::size_type				stack<T, Container>::size() const
	{
		return c.size();
	}
	
	template <class T, class Container>
	typename stack<T, Container>::reference				stack<T, Container>::top()
	{
		return c.begin();
	}
	
	template <class T, class Container>
	typename stack<T, Container>::const_reference		stack<T, Container>::top() const
	{
		return c.begin();
	}
	
	template <class T, class Container>
	void 												stack<T, Container>::push (const value_type& val)
	{
		c.push_back(val);
	}
	
	template <class T, class Container>
	void 												stack<T, Container>::pop()
	{
		c.pop_back();
	}


	/*
		NON-MEMBER FUNCTIONS
	*/
	/*Relational operators*/

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return lhs.c == rhs.c;
	}

	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Container>
  	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return lhs.c < rhs.c;
	}

	template <class T, class Container>
  	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(rhs.c < lhs.c);
	}

	template <class T, class Container>
  	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return rhs.c < lhs.c;
	}

	template <class T, class Container>
  	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs.c < rhs.c);
	}
}

#endif