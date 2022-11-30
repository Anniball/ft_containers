/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:29:59 by ldelmas           #+#    #+#             */
/*   Updated: 2022/11/30 15:27:52 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.hpp"

t_timeval current_time;

static int test_construct(void)
{
	std::string filename = std::string(FILE_NAME) + "_construct_map";
	freopen(filename.c_str(), "w", stdout);

	initialize__time();
	int_map m;
	for (int i = 0; i < 100000; i++)
		m.insert(int_pair(rand() % 100000, rand() % 10000));
	int_map m2(m.begin(), m.end());
	int_map m3(m2);
	print_delta_time();

	m.clear();
	int_map::iterator itb = m.begin();
	for (; itb != m.end(); ++itb)
		std::cout << itb->first << " "  << itb->second << std::endl;
	itb = m2.begin();
	for (; itb != m2.end(); itb++)
		std::cout << itb->first << " "  << itb->second << std::endl;
	itb = m3.begin();
	for (; itb != m3.end(); itb++)
		std::cout << itb->first << " "  << itb->second << std::endl;
	return 0;
}


static int	test_insert(void)
{
	std::string filename = std::string(FILE_NAME) + "_insert_map";
	freopen(filename.c_str(), "w", stdout);

	int_map m, m2;

	initialize__time();
	for (int i = 0; i < 100000; i++)
		m.insert(int_pair(rand() % 100000, rand() % 10000));
	m2.insert(m.begin(), m.end());
	print_delta_time();
	
	int_map::iterator it = m.begin();
	int_map::iterator ite = m.end();
	for (; it != ite; it++)
		std::cout << it->first << " " << it->second << std::endl;
	return 0;
}

static int test_erase(void)
{
	std::string filename = std::string(FILE_NAME) + "_erase_map";
	freopen(filename.c_str(), "w", stdout);

	int_map m, m2, m3;
	for (int i = 0; i < 10; i++)
		m.insert(int_pair(rand() % 100, rand() % 10000));
	m2 = m;
	m3 = m;

	int_map::iterator itb = ++(++(++(m.begin())));
	int_map::iterator itb2, itb3;
	
	initialize__time();
	while (itb != m.end())
	{
		int_map::iterator tmp = itb;
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
		std::cout << itb->first << " " << itb->second << std::endl;
	for (; itb2 != m2.end(); itb2++)
		std::cout << itb2->first << " " << itb2->second << std::endl;
	std::cout << m3.size() << std::endl;
	return 0;
}

static int test_access(void)
{
	std::string filename = std::string(FILE_NAME) + "_access_map";
	freopen(filename.c_str(), "w", stdout);

	int_map m;
	initialize__time();
	for (int i = 0; i < 10000; i++)
		m[rand() % 10000] = rand() % 10000;
	print_delta_time();

	int_map::iterator it =  m.begin();
	for (; it != m.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;
	return 0;
}

static int test_lookup(void)
{
	std::string filename = std::string(FILE_NAME) + "_lookup_map";
	freopen(filename.c_str(), "w", stdout);
	
	int_map m;
	int random_size =  rand() % 100000;
	for (int i = 0; i < random_size; i++)
		m.insert(int_pair(rand() % 100000, rand() % 10000));
	int_map::iterator it = m.begin();

	initialize__time();
	for (; it != m.end(); it++)
	{
		m.count(it->first);
		m.find(it->first);
		m.equal_range(it->first);
		m.lower_bound(it->first);
		m.upper_bound(it->first);
	}
	print_delta_time();

	it = m.begin();
	for (; it != m.end(); it++)
	{
		std::cout << m.count(it->first) << " ";
		std::cout << (m.find(it->first))->second << " ";
		std::cout << (m.equal_range(it->first).first)->second << " ";
		std::cout << (m.lower_bound(it->first))->second << " ";
		if (++it != m.end())
			std::cout << (m.upper_bound((--it)->first))->second << std::endl;
		else --it;
	}
	return 0;
}

static int test_size(void)
{
	std::string filename = std::string(FILE_NAME) + "_size_map";
	freopen(filename.c_str(), "w", stdout);
	
	int_map m, m2, m3;
	for (int i = 0; i < 100000; i++)
		m.insert(int_pair(rand() % 100000, rand() % 10000));
	m2 = m;
	m.swap(m3);

	std::cout << m.empty() << std::endl;
	std::cout << m.size() << std::endl;
	std::cout << m2.empty() << " " << m2.size() << std::endl;
	std::cout << m3.empty() << " " << m3.size() << std::endl;
	int_map::iterator it = m.begin();
	for (; it != m.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;
	it = m2.begin();
	for (; it != m2.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;
	it = m3.begin();
	for (; it != m3.end(); it++)
		std::cout << it->first << " " << it->second << std::endl;
	return 0;
}

static int test_iterator(void)
{
	std::string filename = std::string(FILE_NAME) + "_iter_map";
	freopen(filename.c_str(), "w", stdout);

	int_map m;
	for (int i = 0; i < 10000; i++)
		m.insert(int_pair(rand() % 100000, rand() % 10000));

	int_map::iterator itb = m.begin();
	int_map::iterator ite = m.end();
	int_map::reverse_iterator ritb = m.rbegin();
	int_map::reverse_iterator rite = m.rend();
	std::cout << (*itb).first << std::endl;
	std::cout << (*(--ite)).first<< std::endl;
	std::cout << (*(++itb)).first << std::endl;
	std::cout << (*(ritb)).first << std::endl;
	std::cout << (*(--rite)).first << std::endl;
	std::cout << (*(++ritb)).first << std::endl;
	std::cout << (ite == itb) << std::endl;
	std::cout << (ite != itb) << std::endl;
	return 0;
}

static int test_comparison(void)
{
	std::string filename = std::string(FILE_NAME) + "_compar_map";
	freopen(filename.c_str(), "w", stdout);

	int_map		m, m2, m3;
	greater_map	m4, m5, m6;
	
	for (int i = 0; i < 100; i++)
		m.insert(int_pair(rand() % 100, rand() % 100));
	for (int i = 0; i < 100; i++)
		if (!m.empty()) m.erase(rand() % 100);
	for (int i = 0; i < 100; i++)
		m.insert(int_pair(rand() % 100, rand() % 100));
	for (int i = 0; i < 100; i++)
		m2.insert(int_pair(rand() % 100, rand() % 100));
	for (int i = 0; i < 100; i++)
		if (!m.empty()) m2.erase(rand() % 100);
	for (int i = 0; i < 100; i++)
		m2.insert(int_pair(rand() % 100, rand() % 100));
	for (int i = 0; i < 100; i++)
		m3.insert(int_pair(rand() % 100, rand() % 100));
	for (int i = 0; i < 100; i++)
		if (!m.empty()) m3.erase(rand() % 100);
	for (int i = 0; i < 100; i++)
		m3.insert(int_pair(rand() % 100, rand() % 100));
	
	for (int i = 0; i < 100; i++)
		m4.insert(int_pair(rand() % 100, rand() % 100));
	for (int i = 0; i < 100; i++)
		if (!m.empty()) m4.erase(rand() % 100);
	for (int i = 0; i < 100; i++)
		m4.insert(int_pair(rand() % 100, rand() % 100));
	for (int i = 0; i < 100; i++)
		m5.insert(int_pair(rand() % 100, rand() % 100));
	for (int i = 0; i < 100; i++)
		if (!m.empty()) m5.erase(rand() % 100);
	for (int i = 0; i < 100; i++)
		m5.insert(int_pair(rand() % 100, rand() % 100));
	for (int i = 0; i < 100; i++)
		m6.insert(int_pair(rand() % 100, rand() % 100));
	for (int i = 0; i < 100; i++)
		if (!m.empty()) m6.erase(rand() % 100);
	for (int i = 0; i < 100; i++)
		m6.insert(int_pair(rand() % 100, rand() % 100));
	
	std::cout << "1" << std::endl;
	std::cout << (m == m2) << (m2 == m3) << (m == m3) << std::endl;
	std::cout << (m != m2) << (m2 != m3) << (m != m3) << std::endl;
	std::cout << (m < m2) << (m2 < m3) << (m < m3) << std::endl;
	std::cout << (m <= m2) << (m2 <= m3) << (m <= m3) << std::endl;
	std::cout << (m > m2) << (m2 > m3) << (m > m3) << std::endl;
	std::cout << (m >= m2) << (m2 >= m3) << (m >= m3) << std::endl;

	std::cout << (m == m2) << (m2 == m3) << (m == m3) << std::endl;
	std::cout << (m != m2) << (m2 != m3) << (m != m3) << std::endl;
	std::cout << (m < m2) << (m2 < m3) << (m < m3) << std::endl;
	std::cout << (m <= m2) << (m2 <= m3) << (m <= m3) << std::endl;
	std::cout << (m > m2) << (m2 > m3) << (m > m3) << std::endl;
	std::cout << (m >= m2) << (m2 >= m3) << (m >= m3) << std::endl;
	
	int i = 0;
	for (int_map::iterator it = m.begin(); i < 10 ;i++, it++)
		std::cout << it->first << " " << it->second << std::endl;
	i = 0;
	for (int_map::iterator it = m2.begin(); i < 10 ;i++, it++)
		std::cout << it->first << " " << it->second << std::endl;
	i = 0;
	for (int_map::iterator it = m3.begin(); i < 10 ;i++, it++)
		std::cout << it->first << " " << it->second << std::endl;
	i = 0;
	for (int_map::iterator it = --m.end(); i < 10 ;i++, it--)
		std::cout << it->first << " " << it->second << std::endl;
	i = 0;
	for (int_map::iterator it = --m2.end(); i < 10 ;i++, it--)
		std::cout << it->first << " " << it->second << std::endl;
	i = 0;
	for (int_map::iterator it = --m3.end(); i < 10 ;i++, it--)
		std::cout << it->first << " " << it->second << std::endl;

 	i = 0;
	for (greater_map::iterator it = m4.begin(); i < 10 ;i++, it++)
		std::cout << it->first << " " << it->second << std::endl;
	i = 0;
	for (greater_map::iterator it = m5.begin(); i < 10 ;i++, it++)
		std::cout << it->first << " " << it->second << std::endl;
	i = 0;
	for (greater_map::iterator it = m6.begin(); i < 10 ;i++, it++)
		std::cout << it->first << " " << it->second << std::endl;
	i = 0;
	for (greater_map::iterator it = --m4.end(); i < 10 ;i++, it--)
		std::cout << it->first << " " << it->second << std::endl;
	i = 0;
	for (greater_map::iterator it = --m5.end(); i < 10 ;i++, it--)
		std::cout << it->first << " " << it->second << std::endl;
	i = 0;
	for (greater_map::iterator it = --m6.end(); i < 10 ;i++, it--)
		std::cout << it->first << " " << it->second << std::endl;


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
	test_access();
	test_lookup();
	test_size();
	test_iterator();
	test_comparison();
	return 0;
}