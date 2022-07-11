/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TypeTraits.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 14:18:21 by ldelmas           #+#    #+#             */
/*   Updated: 2022/07/11 14:49:57 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TRAITS_HPP
# define TYPE_TRAITS_HPP

namespace ft
{
	template<class T, T v>
	struct integral_constant
	{
		static const T	value = v;
		typedef			T						value_type;
		typedef			integral_constant<T,v>	type;
		operator		T() {return v;}
	};
	
	typedef  integral_constant<bool, true> true_type;
	typedef  integral_constant<bool, false> false_type;
	
	template<typename>
	struct is_integral : false_type {};

	template<>
	struct is_integral<bool> : true_type {};
	
	template<>
	struct is_integral<char16_t> : true_type {};
	
	template<>
	struct is_integral<char32_t> : true_type {};
	
	template<>
	struct is_integral<wchar_t> : true_type {};
	
	template<>
	struct is_integral<char> : true_type {};
	
	template<>
	struct is_integral<int> : true_type {};

	template<>
	struct is_integral<short int> : true_type {};

	template<>
	struct is_integral<long int> : true_type {};

	template<>
	struct is_integral<long long> : true_type {};

	template<>
	struct is_integral<unsigned char> : true_type {};
	
	template<>
	struct is_integral<unsigned int> : true_type {};

	template<>
	struct is_integral<unsigned short int> : true_type {};

	template<>
	struct is_integral<unsigned long int> : true_type {};

	template<>
	struct is_integral<unsigned long long> : true_type {};

	template <bool, class T = void>
	struct enable_if {};

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};
}

#endif