/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:27:00 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/18 11:50:20 by ldelmas          ###   ########.fr       */
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
			template <class U, class V>
			pair(const pair<U,V>& pr);
			pair(const first_type& a, const second_type& b);
			
			/*
				OPERATOR OVERLOADS
			*/
			pair	&operator=(const pair& pr);
	};


	/*
		CONSTRUCTORS AND DESTRUCTORS
	*/
	template <class T1, class T2>
	pair<T1, T2>::pair() : first(), second() {}

	template <class T1, class T2>
	template <class U, class V>
	pair<T1, T2>::pair(const pair<U,V> &pr) : first(pr.first), second(pr.second) {}

	template <class T1, class T2>
	pair<T1, T2>::pair(const first_type &a, const second_type &b) : first(a), second(b) {}


	/*
		OPERATOR OVERLOADS
	*/
	
	template <class T1, class T2>
	pair<T1, T2>	&pair<T1, T2>::operator=(const pair<T1, T2> &pr)
	{
		this->first = pr.first;
		this->second = pr.second;
		return *this;
	}


	/*
		NON MEMBER OPERATOR OVERLOADS
	*/
	
	template <class T1, class T2>
	bool	operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}
	
	template <class T1, class T2>
	bool	operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs == rhs);
	}
	
	template <class T1, class T2>
	bool	operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}
	
	template <class T1, class T2>
	bool	operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(rhs < lhs);
	}
	
	template <class T1, class T2>
	bool	operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return (rhs < lhs);
	}
	
	template <class T1, class T2>
	bool	operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{
		return !(lhs < rhs);
	}
	
	/*
		NON MEMBER FUNCTIONS
	*/
	
	template <class T1, class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{
		return pair<T1,T2>(x, y);
	}
}

#endif