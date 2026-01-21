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

void BitcoinExchange::setDataBase(const std::string& fileName)
{
	std::fstream file(fileName, std::ios::in);
	std::string	line;
	size_t	lineNum = 0;

	if (file.is_open() == false)
		throw std::invalid_argument("could not open file.");
	while (std::getline(file, line))
	{
		lineNum++;
		if (lineNum == 1)
			continue;
		if (isValidDataLine(line) == false)
			std::cout << "line " << lineNum << " format is not correct: "
				<< line <<" \" continued" << "\n";
		else
			addLineToDataBase(line);
	}
}

bool isValidDate(std::string& date)
{
	try {
		std::string year = date.substr(0, 4);
		std::string month = date.substr(6, 8);
		std::string day = date.substr(10, 12);
		if (*(date.begin()+ 5) == '-'
			&& *(date.begin()+ 9) == '-'
			&& year >= "2009" && year <= "2999"
			&& month >= "01" && month <= "12"
			&& day >= "01" && day <= "31")
			return true;
		return false;
	} catch (...) {
		return false;
	}
}

bool BitcoinExchange::isValidDataLine(const std::string& line) const
{
	size_t commaPos = line.find(",");
	if (commaPos == std::string::npos)
		return false;
	std::string date = line.substr(0, commaPos);
	std::string rate = line.substr(commaPos + 1);

		if (isValidDate(date) == true
			&& isValidRate(rate) == true)
			return true;
	return false;

}
void BitcoinExchange::addLineToDataBase(const std::string& line)
{

}

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
