# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/31 14:52:42 by ldelmas           #+#    #+#              #
#    Updated: 2022/09/02 15:01:43 by ldelmas          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = clang++

CFLAGS = -Wall -Wextra -Werror -std=c++98

UTILS = utils.cpp

STD_NAMESPACE = std

TST_SRC = main.cpp
VEC_SRC = ./Vector/main.cpp ${UTILS}
STK_SRC = ./Stack/main.cpp ${UTILS}
MAP_SRC = ./Map/main.cpp ${UTILS}
SET_SRC = ./Set/main.cpp ${UTILS}

TEST_NAME = tester
FT_VEC_NAME = ./Vector/ft_vec_test
FT_STK_NAME = ./Stack/ft_stk_test
FT_MAP_NAME = ./Map/ft_map_test
FT_SET_NAME = ./Set/ft_set_test
STD_VEC_NAME = ./Vector/std_vec_test
STD_STK_NAME = ./Stack/std_stk_test
STD_MAP_NAME = ./Map/std_map_test
STD_SET_NAME = ./Set/std_set_test

TEST_OBJ = ${TST_SRC:cpp=o}

STD_VEC_OBJ = ${VEC_SRC:cpp=o}
STD_STK_OBJ = ${STK_SRC:cpp=o}
STD_MAP_OBJ = ${MAP_SRC:cpp=o}
STD_SET_OBJ = ${SET_SRC:cpp=o}

FT_VEC_OBJ = ${VEC_SRC:cpp=b}
FT_STK_OBJ = ${STK_SRC:cpp=b}
FT_MAP_OBJ = ${MAP_SRC:cpp=b}
FT_SET_OBJ = ${SET_SRC:cpp=b}

%.o: %.cpp
	@${CC} ${CFLAGS} -c $< -o $@ -DTESTED_NAMESPACE=std

%.b: %.cpp
	@${CC} ${CFLAGS} -c $< -o $@ 

all : ${TEST_NAME} ${FT_VEC_NAME} ${STD_VEC_NAME} ${FT_STK_NAME} ${STD_STK_NAME} ${FT_MAP_NAME} ${STD_MAP_NAME} clean#${SET_NAME}

${TEST_NAME}: ${TEST_OBJ}
	@${CC} ${CFLAGS} -o ${TEST_NAME} ${TEST_OBJ}

${FT_VEC_NAME}:  ${FT_VEC_OBJ}
	@${CC} ${CFLAGS} -o ${FT_VEC_NAME} ${FT_VEC_OBJ}
${FT_STK_NAME}:  ${FT_STK_OBJ}
	@${CC} ${CFLAGS} -o ${FT_STK_NAME} ${FT_STK_OBJ}
${FT_MAP_NAME}:  ${FT_MAP_OBJ}
	@${CC} ${CFLAGS} -o ${FT_MAP_NAME} ${FT_MAP_OBJ}
${FT_SET_NAME}:  ${FT_SET_OBJ}
	@${CC} ${CFLAGS} -o ${FT_SET_NAME} ${FT_SET_OBJ}
	
${STD_VEC_NAME}:  ${STD_VEC_OBJ}
	@${CC} ${CFLAGS} -o ${STD_VEC_NAME} ${STD_VEC_OBJ} 
${STD_STK_NAME}:  ${STD_STK_OBJ}
	@${CC} ${CFLAGS} -o ${STD_STK_NAME} ${STD_STK_OBJ}
${STD_MAP_NAME}:  ${STD_MAP_OBJ}
	@${CC} ${CFLAGS} -o ${STD_MAP_NAME} ${STD_MAP_OBJ}
${STD_SET_NAME}:  ${STD_SET_OBJ}
	@${CC} ${CFLAGS} -o ${STD_SET_NAME} ${STD_SET_OBJ}

	
clean :
	@rm -f ${TEST_OBJ} ${FT_VEC_OBJ} ${FT_STK_OBJ} ${FT_MAP_OBJ} ${FT_SET_OBJ} \
	${STD_VEC_OBJ} ${STD_STK_OBJ} ${STD_MAP_OBJ} ${STD_SET_OBJ}

fclean : clean
	@rm -f ${TEST_NAME} ${FT_VEC_NAME} ${FT_STK_NAME} ${FT_MAP_NAME} ${FT_SET_NAME} \
	${STD_VEC_NAME} ${STD_STK_NAME} ${STD_MAP_NAME} ${STD_SET_NAME}

.PHONY: all clean fclean

