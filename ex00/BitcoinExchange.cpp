#include "BitcoinExchange.hpp"

static const float inputValueMin = 0;
static const float inputValueMax = 1000;

/**
 * @brief constructor parse line by line to set the dataBase
 *
 * @param fileName fileName passed as seconde argument of program
 * @warning throw invalid_argument exception if cant open file
 */
BitcoinExchange::BitcoinExchange(const std::string& fileName)
{
	setDataBase(fileName);
}

