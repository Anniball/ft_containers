/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:13:30 by ldelmas           #+#    #+#             */
/*   Updated: 2022/09/01 17:18:06 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.hpp"

t_timeval current_time;

/*
	vector			&operator=(const vector& x);

	reverse_iterator		rbegin(void);
	const_reverse_iterator	rbegin(void) const;
	reverse_iterator		rend(void);
	const_reverse_iterator	rend(void) const;
	size_type				max_size(void) const;
	void					resize(size_type n, value_type val = value_type());
	size_type				capacity(void) const;
	bool					empty(void) const;
	void					reserve(size_type n);
	void 					assign(InputIterator first, InputIterator last, typename enable_if<!is_integral<InputIterator>::value>::type *dummy = NULL);
	void					assign(size_type n, const value_type &val);
	void					pop_back(void);
	void					swap(vector &x);
	void					clear(void);
	allocator_type			get_allocator(void) const;
*/

static int	test_insert(void)
{
	std::string filename = std::string(FILE_NAME) + "_insert_vector";
	freopen(filename.c_str(), "w", stdout);

	int_vector vec, vec2;
	initialize__time();
	for (int i = 0; i < 1000; i++)
		vec.push_back(rand() % 10000);
	vec.insert(vec.begin() + (rand() % vec.size()), -1);
	vec.insert(vec.begin() + (rand() % vec.size()), 10000, -1);
	vec2.insert(vec2.begin(), vec.begin(), vec.begin() + (rand() % vec.size()));
	print_delta_time();
	int_vector::iterator itb = vec.begin();
	int_vector::iterator ite = vec.end();
	for (; itb != ite; itb++)
		std::cout << *itb << std::endl;
	itb = vec2.begin();
	ite = vec2.end();
	for (; itb != ite; itb++)
		std::cout << *itb << std::endl;
	return 0;
}

static int test_erase(void)
{
	std::string filename = std::string(FILE_NAME) + "_erase_vector";
	freopen(filename.c_str(), "w", stdout);

	int_vector vec;
	for (int i = 0; i < 100; i++)
		vec.push_back(rand() % 10000);

	initialize__time();
	int_vector::iterator itb = vec.begin();
	while (itb != vec.end())
	{
		if (rand() % 2)
			itb = vec.erase(itb);
		else
			++itb;
	}
	vec.erase(vec.begin(), vec.begin() + (vec.size() / 2));
	print_delta_time();

	itb = vec.begin();
	for (; itb != vec.end(); itb++)
		std::cout << *itb << std::endl;
	return 0;
}

static int test_construct(void)
{
	std::string filename = std::string(FILE_NAME) + "_construct_vector";
	freopen(filename.c_str(), "w", stdout);

	initialize__time();
	int_vector vec;
	int_vector vec2(100000, -5);
	int_vector vec3(vec2.begin(), vec2.end());
	int_vector vec4(vec3);
	print_delta_time();

	
	int_vector::iterator itb = vec2.begin();
	for (; itb != vec2.end(); ++itb)
		std::cout << *itb << std::endl;
	itb = vec3.begin();
	for (; itb != vec3.end(); itb++)
		std::cout << *itb << std::endl;
	itb = vec4.begin();
	for (; itb != vec4.end(); itb++)
		std::cout << *itb << std::endl;
	return 0;
}

static int test_access(void)
{	
	std::string filename = std::string(FILE_NAME) + "_access_vector";
	freopen(filename.c_str(), "w", stdout);

	int_vector vec;
	for (int i = 0; i < 100; i++)
		vec.push_back(rand() % 10000);
	std::cout << vec.front() << std::endl;
	std::cout << vec.back() << std::endl;
	for (int i = 0; i < 10; i++)
		std::cout << vec[rand() % vec.size()] << std::endl;
	for (int i = 0; i < 10; i++)
		std::cout << vec.at(rand() % vec.size()) << std::endl;
	return 0;
}

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Please just put 1 argument to seed the randomness." << std::endl;
		return 1;
	}
	tester_setup(av[1]);
	test_construct();
	test_access();
	test_insert();
	test_erase();

	return 0;
}