/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 14:29:59 by ldelmas           #+#    #+#             */
/*   Updated: 2022/09/02 15:08:59 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.hpp"

t_timeval current_time;

static int	test_insert(void)
{
	std::string filename = std::string(FILE_NAME) + "_insert_map";
	freopen(filename.c_str(), "w", stdout);

	int_map m;
	initialize__time();
	for (int i = 0; i < 100000; i++)
		m.insert(int_pair(rand() % 100000, rand() % 10000));
	print_delta_time();
	
	int_map::iterator it = m.begin();
	int_map::iterator ite = m.end();
	for (; it != ite; it++)
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
	test_insert();
	return 0;
}