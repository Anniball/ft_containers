/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lucas <lucas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:46:08 by ldelmas           #+#    #+#             */
/*   Updated: 2022/09/05 17:50:40 by lucas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void	tester_setup(char *seed)
{
	gettimeofday(&current_time, NULL);
	srand(std::atoi(seed));
}

void	print_delta_time(void)
{
	long long previous_total = current_time.tv_sec * 1000000 + current_time.tv_usec;
	gettimeofday(&current_time, NULL);
	long long new_total = current_time.tv_sec * 1000000 + current_time.tv_usec;
	std::cout << new_total - previous_total << std::endl;
}


void	initialize__time(void)
{
	gettimeofday(&current_time, NULL);
}
