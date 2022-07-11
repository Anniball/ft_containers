/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:27:00 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/11 17:33:31 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft
{
	template <class T1, class T2>
	class pair
	{
		typedef T1		first_type;
		typedef T2		second_type;

		public :
			/*
				MEMBER VARIABLES
			*/
			first_type	first;
			second_type	second;

			/*
				CONSTRUCTORS AND DESTRUCTORS
			*/
			pair();
			template<class U, class V>
			pair(const pair<U,V>& pr);
			pair(const first_type& a, const second_type& b);
			
			/*
				OPERATOR OVERLOADS
			*/
			pair	&operator=(const pair& pr);
			template <class T1, class T2>
			bool	operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs);
			template <class T1, class T2>
			bool	operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs);
			template <class T1, class T2>
			bool	operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs);
			template <class T1, class T2>
			bool	operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs);
			template <class T1, class T2>
			bool	operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs);
			template <class T1, class T2>
			bool	operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs);
	}

	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y);
}

#endif