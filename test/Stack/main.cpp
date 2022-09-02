/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 11:49:23 by ldelmas           #+#    #+#             */
/*   Updated: 2022/09/02 14:30:09 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils.hpp"

t_timeval current_time;

static int	test_insert(void)
{
	std::string filename = std::string(FILE_NAME) + "_insert_stack";
	freopen(filename.c_str(), "w", stdout);

	initialize__time();
	int_stack	stk;
	for (int i = 0; i <  100000; i++)
		stk.push(rand() % 100000);
	print_delta_time();

	while (!stk.empty())
	{
		std::cout << stk.top() << std::endl;
		stk.pop();
	}
	return 0;
}

static int	test_erase(void)
{
	std::string filename = std::string(FILE_NAME) + "_erase_stack";
	freopen(filename.c_str(), "w", stdout);

	int_stack	stk, stk2;
	for (int i = 0; i <  100000; i++)
		stk.push(rand() % 100000);

	initialize__time();
	while (stk.size() > 4000)
		stk.pop();
	print_delta_time();

	for (int i = 0; i <  200; i++)
		stk.push(rand() % 200);
	std::cout << (stk == stk2) << std::endl;
	std::cout << (stk != stk2) << std::endl;
	std::cout << (stk < stk2) << std::endl;
	std::cout << (stk <= stk2) << std::endl;
	std::cout << (stk >= stk2) << std::endl;
	std::cout << (stk > stk2) << std::endl;
	while (!stk.empty())
	{
		std::cout << stk.top() << std::endl;
		stk.pop();
	}
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
	test_erase();
	return 0;
}