/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:46:08 by ldelmas           #+#    #+#             */
/*   Updated: 2022/08/31 16:27:59 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.hpp"

void	tester_setup(char *seed)
{
	gettimeofday(&current_time, NULL);
	srand(std::stoi(seed));
}

void	print_delta_time(void)
{
	long long previous_total = current_time.tv_sec * 1000 + current_time.tv_usec;
	gettimeofday(&current_time, NULL);
	long long new_total = current_time.tv_sec * 1000 + current_time.tv_usec;
	std::cout << "time : " << new_total - previous_total << std::endl;
}
