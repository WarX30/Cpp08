#include "../include/easyfind.hpp"

#include <exception>
#include <vector>
#include <iostream>

int	main(void)
{
	std::vector<int> v;

	int i = 0;
	while (i <= 50)
	{
		i += 10;
		v.push_back(i);
	}

	try {
		std::vector<int>::iterator it = easyfind(v, -50);
		std::cout << "\033[32mValue found " << *it << "\033[0m" << std::endl;
	} catch (std::exception &e) {
		std::cout << "\033[31m" << e.what() << "\033[0m" << std::endl;
	}
	
	return (0);
}
