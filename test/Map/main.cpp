/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:29:59 by ldelmas           #+#    #+#             */
/*   Updated: 2022/09/05 11:50:27 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.hpp"

t_timeval current_time;

/*
			map	&operator=(const map &x);
			iterator							begin(void);
			const_iterator						begin(void) const;
			iterator							end(void);
			const_iterator						end(void) const;
			reverse_iterator					rbegin(void);
			const_reverse_iterator				rbegin(void) const;
			reverse_iterator					rend(void);
			const_reverse_iterator				rend(void) const;
			bool								empty(void) const;
			size_type							size(void) const;
			size_type							max_size(void) const;
			mapped_type							&operator[](const key_type& k);
			void								swap(map& x);
			void								clear(void);
			key_compare							key_comp(void) const;
			value_compare						value_comp(void) const;
			iterator							find(const key_type& k);
			const_iterator						find(const key_type& k) const;
			size_type							count(const key_type& k) const;
			iterator							lower_bound(const key_type& k);
			const_iterator						lower_bound(const key_type& k) const;
			iterator							upper_bound(const key_type& k);
			const_iterator						upper_bound(const key_type& k) const;
			pair<const_iterator,const_iterator>	equal_range(const key_type& k) const;
			pair<iterator,iterator>				equal_range(const key_type& k);
*/

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

	int_map::iterator itb = m.end();
	int_map::iterator itb2, itb3;
	while (itb == m.end())
		itb = m.find(rand() % 100);
	
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
	return 0;
}