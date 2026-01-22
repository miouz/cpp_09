#include "BitcoinExchange.hpp"

void BitcoinExchange::displayValueFromLine(const std::string& line) const
{

}

void BitcoinExchange::displayValueFromFile(const std::string& fileName) const
{
	std::ifstream input(fileName.c_str(), std::ios::in);
	std::string	line;

	if (!input.is_open())
		throw std::runtime_error("couldn't open input file");
	while (std::getline(input, line))
	{
		try {
		displayValueFromLine(line);
		} catch (std::exception& e) {
			std::cout << "Error: " << std::endl;
		}
	}
}
