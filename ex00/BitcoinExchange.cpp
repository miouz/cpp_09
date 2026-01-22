#include "BitcoinExchange.hpp"


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

BitcoinExchange::~BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other): dataBase_(other.dataBase_) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this == &other)
		return *this;
	dataBase_ = other.dataBase_;
	return *this;
}
