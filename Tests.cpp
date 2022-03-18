/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Tests.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldelmas <ldelmas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 15:05:14 by ldelmas           #+#    #+#             */
/*   Updated: 2021/11/24 15:45:58 by ldelmas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>

int main(void)
{
	std::vector<int> myVector;
	std::cout << myVector.max_size() << std::endl;
	// std::cout << myVector.capacity() << std::endl;
	for (int i = 0; i < 10; i++)
	{
		myVector.push_back(42);
		std::cout << myVector.capacity() << std::endl;
	}
	myVector.clear();
		// std::cout << myVector.capacity() << std::endl;
	// std::cout <<  myVector.data() << "	" << *myVector.data() << std::endl;
	// myVector.reserve(8000);
	// std::cout <<  myVector.data() << "	" << *myVector.data() << std::endl;

	// myVector.resize(25, 19);
	// std::cout << myVector.capacity() << std::endl;
	// for (int i = 0; i < 25; i++)
	// 	std::cout << myVector[i] << std::endl;

	//RESERVE TESTS
	// myVector.reserve(145);
	// std::cout << myVector.capacity() << std::endl;
	// myVector.reserve(23);
	// std::cout << myVector.capacity() << std::endl;
	return (0);
}