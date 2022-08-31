/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:13:30 by ldelmas           #+#    #+#             */
/*   Updated: 2022/08/31 16:28:06 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.hpp"

t_timeval current_time;

static int	test_insert(int_vector vec)
{
	std::string filename = std::string(FILE_NAME) + "_insert_vector";
	freopen(filename.c_str(), "w", stdout);

	for (int i = 0; i < 100000; i++)
		vec.push_back(rand() % 100000);
	print_delta_time();
	int_vector::iterator itb = vec.begin();
	int_vector::iterator ite = vec.end();
	for (; itb != ite; itb++)
		std::cout << *itb << std::endl;
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
	int_vector vec;
	test_insert(vec);

	return 0;
}