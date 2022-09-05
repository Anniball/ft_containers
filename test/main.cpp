/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 16:30:15 by ldelmas           #+#    #+#             */
/*   Updated: 2022/09/05 11:50:50 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include "utils.hpp"
#include <list>

std::list<double>	ratios;

static int	execute_tester(std::string str, std::string seed)
{
	const char *str_seed = seed.c_str();
	const char *env[3] = {str.c_str(), str_seed, NULL};
	int status = 0;
	int pid = fork();
	if (pid < 0)
	{
		std::cout << "Forking of the process failed. Your session is probably full." << std::endl;
		return 1;
	}
	else if (!pid)
		execv(env[0], (char**)env);
	else
		waitpid(pid, &status, 0);
	if (status)
		std::cerr << "CRASH on " << str << std::endl;
	return status;
}

static void	print_class_header(std::string name)
{
	Color::Modifier def(Color::FG_DEFAULT);
	std::cout << def << "\t\t-----" << name << "-----" << std::endl;
	std::cout << "METHOD\t\tRESULT\t\tTIMING" << std::endl;
}

static void	print_timing(std::string ft_time, std::string std_time)
{
	Color::Modifier red(Color::FG_RED);
	Color::Modifier green(Color::FG_GREEN);
	double ratio = std::stod(ft_time) / std::stod(std_time);
	ratios.push_back(ratio);
	if (ratio < 20) std::cout << green << ratio  << std::endl;
	else std::cout << red << ratio  << std::endl;
}

static int	compare_files(std::string std, std::string ft, std::string method)
{
	Color::Modifier def(Color::FG_DEFAULT);
	std::cout << def << method << "\t\t";
	Color::Modifier red(Color::FG_RED);
	Color::Modifier green(Color::FG_GREEN);
	try
	{
		std::ifstream ifs_std(std);
		std::ifstream ifs_ft(ft);

		std::string std_time, ft_time, std_str, ft_str;
		std::getline(ifs_std, std_time);
		std::getline(ifs_ft, ft_time);

		std_str = std::string(std::istreambuf_iterator<char>(ifs_std), std::istreambuf_iterator<char>());
		ft_str = std::string(std::istreambuf_iterator<char>(ifs_ft), std::istreambuf_iterator<char>());
		std_str = std_str.substr(std_str.find("\n"), std_str.size());
		ft_str = ft_str.substr(ft_str.find("\n"), ft_str.size());
		int cmp = std_str.compare(ft_str);
		if (!cmp) std::cout << green << "OK\t\t";
		else std::cout << red << "DIFF\t\t" << cmp; 

		print_timing(ft_time, std_time);
		remove(std.c_str());
		remove(ft.c_str());
		return 0;
	}
	catch(const std::exception& e)
	{
		std::cout << "Error, wrong file or non existing." << std::endl;
		return 1;
	}
}

static void	print_global_timing(void)
{
	Color::Modifier def(Color::FG_DEFAULT);
	Color::Modifier red(Color::FG_RED);
	Color::Modifier green(Color::FG_GREEN);
	std::cout << def << "Global ratio (FT / STD) :\t";
	double total = 0;
	for (std::list<double>::iterator it  = ratios.begin(); it != ratios.end(); it++)
		total += *it;
	total /= ratios.size();
	if (total > 20)
		std::cout << red << total << std::endl << std::endl;
	else
		std::cout << green << total << std::endl << std::endl;
	ratios.clear();
}

int			main(void)
{
	srand(time(NULL));
	int seed = rand() % 1000000;

	print_class_header("VECTOR");
	if (!execute_tester("./Vector/ft_vec_test", std::to_string(seed))
		&& !execute_tester("./Vector/std_vec_test", std::to_string(seed)))
	{
		compare_files("std_construct_vector", "ft_construct_vector", "Constr");
		compare_files("std_access_vector", "ft_access_vector", "Access");
		compare_files("std_insert_vector", "ft_insert_vector", "Insert");
		compare_files("std_erase_vector", "ft_erase_vector", "Erase");
		compare_files("std_assign_vector", "ft_assign_vector", "Assign");
		compare_files("std_iter_vector", "ft_iter_vector", "Iter");
		compare_files("std_size_vector", "ft_size_vector", "Size");
		print_global_timing();
	}

	print_class_header("STACK");
	if (!execute_tester("./Stack/ft_stk_test", std::to_string(seed))
		&& !execute_tester("./Stack/std_stk_test", std::to_string(seed)))
	{
		compare_files("std_insert_stack", "ft_insert_stack", "Insert");
		compare_files("std_erase_stack", "ft_erase_stack", "Erase");
		print_global_timing();
	}

	print_class_header("MAP");
	if (!execute_tester("./Map/ft_map_test", std::to_string(seed))
		&& !execute_tester("./Map/std_map_test", std::to_string(seed)))
	{
		compare_files("std_construct_map", "ft_construct_map", "Constr");
		compare_files("std_insert_map", "ft_insert_map", "Insert");
		compare_files("std_erase_map", "ft_erase_map", "Erase");
		print_global_timing();
	}
	return 0;
}