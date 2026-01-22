#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>
#include <ios>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include "utils.hpp"

class BitcoinExchange
{
private:
	std::map<std::string, float> dataBase_;

	void setDataBase(const std::string& fileName);
	bool isValidDataLine(const std::string& line) const;
	void addLineToDataBase(const std::string& line);
public:
	BitcoinExchange(const std::string& fileName);
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);

	void displayValueFromFile(const std::string& fileName) const;
	void displayValueFromLine(const std::string& line) const;
};

#endif // !BITCOINEXCHANGE_HPP
