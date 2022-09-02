/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:47:03 by ldelmas           #+#    #+#             */
/*   Updated: 2022/09/02 14:56:42 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cstdio>
#include <ostream>
#include <list>

#ifdef TESTED_NAMESPACE
# define FILE_NAME "std"
# include <vector>
# include <stack>
# include <map>
#endif

#ifndef TESTED_NAMESPACE
# define TESTED_NAMESPACE ft
# define FILE_NAME "ft"
# include "../cont/Vector.hpp"
# include "../cont/Stack.hpp"
# include "../cont/Map.hpp"
#endif

typedef struct timeval						t_timeval;
typedef TESTED_NAMESPACE::vector<int>		int_vector;
typedef TESTED_NAMESPACE::stack<int>		int_stack;
typedef TESTED_NAMESPACE::map<int, int>		int_map;
typedef TESTED_NAMESPACE::pair<int, int>	int_pair;

extern t_timeval			current_time;

namespace Color
{
    enum Code
	{
        FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };

    class Modifier
	{
        Code code;
    public:
        Modifier(Code pCode) : code(pCode) {}
        friend std::ostream&
        operator<<(std::ostream& os, const Modifier& mod) {
            return os << "\033[" << mod.code << "m";
        }
    };
}

/*
	UTILS PROTOTYPES
*/

void	tester_setup(char *seed);
void	print_delta_time(void);
void	initialize__time(void);
