#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

bool isValidArg(char ** argv)
{
	std::string arg1(argv[1]);
	std::string arg2(argv[2]);
	
	if (arg1.find(".csv") == arg1.size() - 4 && arg2.empty() == false)
		return true;
	return false;
}

int main(int argc, char **argv)
{
	if ( argc != 3 || isValidArg(argv) == false)
	{
		std::cout << "Error: need one .csv file and one input file\n";
		exit(1);
	}

	try {
		BitcoinExchange rate(argv[1]);
		rate.displayValueFromFile(argv[2]);
	} catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		exit(1);	
	}
	return EXIT_SUCCESS;
}
