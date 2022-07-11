/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:14:33 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/11 15:43:11 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

namespace ft
{
	template <class T, class Container = vector<T> >
	class stack
	{
		typedef T				value_type;
		typedef Container		container_type;
		typedef size_t			size_type;

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

	// /*
	// 	CONSTRUCTORS AND DESTRUCTORS
	// */
	// template <class T, class Container>
	// stack(const stack<class T, class Container>::container_type &ctnr = container_type()) {}

	// /*
	// 	MEMBER FUNCTIONS
	// */

	
	// template <class T, class Container>
	// bool				empty() const
	// {
	// 	return c.empty();
	// }
	
	// template <class T, class Container>
	// size_type			size() const
	// {
	// 	return c.size();
	// }
	
	// template <class T, class Container>
	// value_type&			top()
	// {
	// 	return c.begin();
	// }
	
	// template <class T, class Container>
	// const value_type&	top() const;
	// {
	// 	return c.begin();
	// }
	
	// template <class T, class Container>
	// void 				push (const value_type& val)
	// {
	// 	c.push_back(val);
	// }
	
	// template <class T, class Container>
	// void 				pop()
	// {
	// 	c.pop_back();
	// }


	// /*
	// 	NON-MEMBER FUNCTIONS
	// */
	// /*Relational operators*/

	// template <class T, class Container>
	// bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

	// template <class T, class Container>
	// bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

	// template <class T, class Container>
  	// bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

	// template <class T, class Container>
  	// bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

	// template <class T, class Container>
  	// bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs);

	// template <class T, class Container>
  	// bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs);
	
}

#endif