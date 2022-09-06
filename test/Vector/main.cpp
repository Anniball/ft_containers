/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:13:30 by ldelmas           #+#    #+#             */
/*   Updated: 2022/09/06 10:33:49 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.hpp"

t_timeval current_time;

static int	test_insert(void)
{
	std::string filename = std::string(FILE_NAME) + "_insert_vector";
	freopen(filename.c_str(), "w", stdout);

	int_vector vec, vec2;
	initialize__time();
	for (int i = 0; i < 10000; i++)
		vec.push_back(rand() % 10000);
	vec.insert(vec.begin() + (rand() % vec.size()), -1);
	vec.insert(vec.begin() + (rand() % vec.size()), 10000, -1);
	vec2.insert(vec2.begin(), vec.begin(), vec.begin() + (rand() % vec.size()));
	print_delta_time();
	int_vector::const_iterator itb = vec.begin();
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
	for (int i = 0; i < 40; i++)
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
	for (int i = 0; i < 5; i++)
		vec.pop_back();
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

static int test_assign(void)
{
	std::string filename = std::string(FILE_NAME) + "_assign_vector";
	freopen(filename.c_str(), "w", stdout);
	
	int_vector vec, vec2;
	for (int i = 0; i < 10000; i++)
		vec.push_back(rand() % 100000);

	initialize__time();
	vec2.assign(vec.begin(), vec.begin() + rand() % vec.size());
	vec2.assign(500, -5);
	print_delta_time();

	int_vector::iterator itb = vec2.begin();
	for (; itb != vec2.end(); itb++)
		std::cout << *itb << std::endl;
	return 0;
}

static int test_iterator(void)
{
	std::string filename = std::string(FILE_NAME) + "_iter_vector";
	freopen(filename.c_str(), "w", stdout);

	int_vector vec;
	for (int i = 0; i < 10000; i++)
		vec.push_back(rand() % 100000);

	int_vector::iterator itb = vec.begin();
	int_vector::iterator ite = vec.end();
	int_vector::reverse_iterator ritb = vec.rbegin();
	int_vector::reverse_iterator rite = vec.rend();
	std::cout << *itb << std::endl;
	std::cout << *(ite  - 1)<< std::endl;
	std::cout << *(itb + 15) << std::endl;
	std::cout << *(ite - 15) << std::endl;
	std::cout << *(ritb + 15) << std::endl;
	std::cout << *(rite - 15) << std::endl;
	itb++;
	ite--;
	ritb++;
	rite--;
	std::cout << *itb << std::endl;
	std::cout << *ite << std::endl;
	std::cout << *ritb << std::endl;
	std::cout << *rite << std::endl;
	std::cout << ite - (itb + 2) << std::endl;
	std::cout << (ite <= itb) << std::endl;
	std::cout << (ite < itb) << std::endl;
	std::cout << (ite > itb) << std::endl;
	std::cout << (ite >= itb) << std::endl;
	std::cout << itb[2] << std::endl;
	return 0;
}

static int test_size(void)
{
	std::string filename = std::string(FILE_NAME) + "_size_vector";
	freopen(filename.c_str(), "w", stdout);

	int_vector vec, vec2, vec3, vec4;
	for (int i = 0; i < 10000; i++)
		vec.push_back(rand() % 100000);

	initialize__time();
	vec.reserve(100000000);
	vec.resize(10);
	vec.resize(1000000, -5);
	vec2 = vec;
	vec3 = vec2;
	vec2.clear();
	vec3.swap(vec4);
	print_delta_time();

	std::cout << vec.size() << std::endl;
	std::cout << vec2.size() << std::endl;
	std::cout << vec3.size() << std::endl;
	std::cout << vec4.size() << std::endl;
	std::cout << vec.empty();
	std::cout << vec2.empty();
	std::cout << vec3.empty();
	std::cout << vec4.empty();
	std::cout << vec.capacity();
	std::cout << vec2.capacity();
	std::cout << vec3.capacity();
	std::cout << vec4.capacity();
	return 0;
}

static int test_comparison(void)
{
	std::string filename = std::string(FILE_NAME) + "_compar_vector";
	freopen(filename.c_str(), "w", stdout);

	int_vector vec, vec2, vec3;
	for (int i = 0; i < 100; i++)
		vec.push_back(rand() % 100);
	for (int i = 0; i < 100; i++)
		vec2.push_back(rand() % 100);
	for (int i = 0; i < 100; i++)
		vec3.push_back(rand() % 100);
	
	std::cout << "1" << std::endl;
	std::cout << (vec == vec2) << (vec2 == vec3) << (vec == vec3) << std::endl;
	std::cout << (vec != vec2) << (vec2 != vec3) << (vec != vec3) << std::endl;
	std::cout << (vec < vec2) << (vec2 < vec3) << (vec < vec3) << std::endl;
	std::cout << (vec <= vec2) << (vec2 <= vec3) << (vec <= vec3) << std::endl;
	std::cout << (vec > vec2) << (vec2 > vec3) << (vec > vec3) << std::endl;
	std::cout << (vec >= vec2) << (vec2 >= vec3) << (vec >= vec3) << std::endl;

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
	test_assign();
	test_iterator();
	test_size();
	test_comparison();
	return 0;
}