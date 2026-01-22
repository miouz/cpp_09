#include "BitcoinExchange.hpp"
#include <cstdlib>
#include <iostream>
#include <stdexcept>

std::string getFileName(int argc, char **argv)
{
	if (argc != 2)
		throw std::invalid_argument("could not open file");
	std::string fileName(argv[1]);
	return (fileName);
}

int main(int argc, char **argv)
{
	
	try {
		std::string fileName = getFileName(argc, argv);
		BitcoinExchange btc("data.csv");
		btc.displayValueFromFile(fileName);
	} catch (std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
		exit(1);	
	}
	return EXIT_SUCCESS;
}
