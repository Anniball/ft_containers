/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:47:03 by ldelmas           #+#    #+#             */
/*   Updated: 2022/08/31 16:20:25 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>

#ifdef TESTED_NAMESPACE
# define FILE_NAME "std"
# include <vector>
#endif

#ifndef TESTED_NAMESPACE
# define TESTED_NAMESPACE ft
# define FILE_NAME "ft"
# include "../cont/Vector.hpp"
#endif

typedef struct timeval t_timeval;
typedef TESTED_NAMESPACE::vector<int> int_vector;

extern t_timeval current_time;

/*
	UTILS PROTOTYPES
*/

void	tester_setup(char *seed);
void	print_delta_time(void);
