/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:31:25 by ldelmas           #+#    #+#             */
/*   Updated: 2022/09/05 15:51:08 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.hpp"

t_timeval current_time;

static int test_construct(void)
{
	std::string filename = std::string(FILE_NAME) + "_construct_set";
	freopen(filename.c_str(), "w", stdout);

	initialize__time();
	int_set m;
	for (int i = 0; i < 100000; i++)
		m.insert(rand() % 100000);
	int_set m2(m.begin(), m.end());
	int_set m3(m2);
	print_delta_time();

	m.clear();
	int_set::iterator itb = m.begin();
	for (; itb != m.end(); ++itb)
		std::cout << *itb << std::endl;
	itb = m2.begin();
	for (; itb != m2.end(); itb++)
		std::cout << *itb << std::endl;
	itb = m3.begin();
	for (; itb != m3.end(); itb++)
		std::cout << *itb << std::endl;
	return 0;
}


static int	test_insert(void)
{
	std::string filename = std::string(FILE_NAME) + "_insert_set";
	freopen(filename.c_str(), "w", stdout);

	int_set m, m2;

	initialize__time();
	for (int i = 0; i < 100000; i++)
		m.insert(rand() % 100000);
	m2.insert(m.begin(), m.end());
	print_delta_time();
	
	int_set::iterator it = m.begin();
	int_set::iterator ite = m.end();
	for (; it != ite; it++)
		std::cout << *it << std::endl;
	return 0;
}

static int test_erase(void)
{
	std::string filename = std::string(FILE_NAME) + "_erase_set";
	freopen(filename.c_str(), "w", stdout);

	int_set m, m2, m3;
	for (int i = 0; i < 10; i++)
		m.insert(rand() % 100);
	m2 = m;
	m3 = m;

	int_set::iterator itb = ++(++(++(m.begin())));
	int_set::iterator itb2, itb3;
	
	initialize__time();
	while (itb != m.end())
	{
		int_set::iterator tmp = itb;
		++itb;
		m.erase(tmp);
	}
	for (size_t i = 0; i < m2.size(); i++)
		m2.erase(rand() % 100);
	m3.erase(m3.begin(), m3.end());	
	print_delta_time();

	itb = m.begin();
	itb2 = m2.begin();
	itb3 = m3.begin();
	for (; itb != m.end(); itb++)
		std::cout << *itb << std::endl;
	for (; itb2 != m2.end(); itb2++)
		std::cout << *itb2 << std::endl;
	std::cout << m3.size() << std::endl;
	return 0;
}

static int test_lookup(void)
{
	std::string filename = std::string(FILE_NAME) + "_lookup_set";
	freopen(filename.c_str(), "w", stdout);
	
	int_set m;
	int random_size =  rand() % 100000;
	for (int i = 0; i < random_size; i++)
		m.insert(rand() % 100000);
	int_set::iterator it = m.begin();

	initialize__time();
	for (; it != m.end(); it++)
	{
		m.count(*it);
		m.find(*it);
		m.equal_range(*it);
		m.lower_bound(*it);
		m.upper_bound(*it);
	}
	print_delta_time();

	it = m.begin();
	for (; it != m.end(); it++)
	{
		std::cout << m.count(*it) << " ";
		std::cout << *(m.find(*it)) << " ";
		std::cout << *(m.equal_range(*it).second) << " ";
		std::cout << *(m.lower_bound(*it)) << " ";
		if (++it != m.end())
			std::cout << *(m.upper_bound(*(--it))) << std::endl;
		else --it;
	}
	return 0;
}

static int test_size(void)
{
	std::string filename = std::string(FILE_NAME) + "_size_set";
	freopen(filename.c_str(), "w", stdout);
	
	int_set m, m2, m3;
	for (int i = 0; i < 100000; i++)
		m.insert(rand() % 100000);
	m2 = m;
	m.swap(m3);

	std::cout << m.empty() << std::endl;
	std::cout << m.size() << std::endl;
	std::cout << m2.empty() << " " << m2.size() << std::endl;
	std::cout << m3.empty() << " " << m3.size() << std::endl;
	int_set::iterator it = m.begin();
	for (; it != m.end(); it++)
		std::cout << *it << std::endl;
	it = m2.begin();
	for (; it != m2.end(); it++)
		std::cout << *it << std::endl;
	it = m3.begin();
	for (; it != m3.end(); it++)
		std::cout << *it << std::endl;
	return 0;
}

static int test_iterator(void)
{
	std::string filename = std::string(FILE_NAME) + "_iter_set";
	freopen(filename.c_str(), "w", stdout);

	int_set m;
	for (int i = 0; i < 10000; i++)
		m.insert(rand() % 100000);

	std::cout << "1" << std::endl;
	int_set::iterator itb = m.begin();
	int_set::iterator ite = m.end();
	int_set::reverse_iterator ritb = m.rbegin();
	int_set::reverse_iterator rite = m.rend();
	std::cout << (*itb) << std::endl;
	std::cout << (*(--ite))<< std::endl;
	std::cout << (*(++itb)) << std::endl;
	std::cout << (*(ritb)) << std::endl;
	std::cout << (*(--rite)) << std::endl;
	std::cout << (*(++ritb)) << std::endl;
	std::cout << (ite == itb) << std::endl;
	std::cout << (ite != itb) << std::endl;
	return 0;
}

static int test_comparison(void)
{
	std::string filename = std::string(FILE_NAME) + "_compar_set";
	freopen(filename.c_str(), "w", stdout);

	int_set m, m2, m3;
	for (int i = 0; i < 100; i++)
		m.insert(rand() % 100);
	for (int i = 0; i < 100; i++)
		m2.insert(rand() % 100);
	for (int i = 0; i < 100; i++)
		m3.insert(rand() % 100);
	
	std::cout << "1" << std::endl;
	std::cout << (m == m2) << (m2 == m3) << (m == m3) << std::endl;
	std::cout << (m != m2) << (m2 != m3) << (m != m3) << std::endl;
	std::cout << (m < m2) << (m2 < m3) << (m < m3) << std::endl;
	std::cout << (m <= m2) << (m2 <= m3) << (m <= m3) << std::endl;
	std::cout << (m > m2) << (m2 > m3) << (m > m3) << std::endl;
	std::cout << (m >= m2) << (m2 >= m3) << (m >= m3) << std::endl;

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
	test_insert();
	test_erase();
	test_lookup();
	test_size();
	test_iterator();
	test_comparison();
	return 0;
}