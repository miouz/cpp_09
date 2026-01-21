#include "BitcoinExchange.hpp"

/**
 * @brief constructor parse line by line to set the dataBase
 *
 * @param fileName fileName passed as seconde argument of program
 * @warning throw invalid_argument exception if cant open file
 */
BitcoinExchange::BitcoinExchange(const std::string& fileName)
{
	std::fstream file(fileName, std::ios::in);

	if (file.is_open() == false)
		throw std::invalid_argument("could not open file.");
	
}
