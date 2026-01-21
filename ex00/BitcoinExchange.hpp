#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <list>
#include <string>
#include <ios>
#include <fstream>

class BitcoinExchange
{
private:
	std::list<std::string> dataBase_;
public:
	BitcoinExchange(const std::string& fileName);
	~BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);

	void setDataBase(const std::string& fileName);
	bool isValidLine(std::list<std::string>::const_iterator& line) const;
	void outputLine(std::list<std::string>::const_iterator& line) const;
};

#endif // !BITCOINEXCHANGE_HPP
