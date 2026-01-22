#include "BitcoinExchange.hpp"

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
	size_t commaPos = line.find(",");
	std::string date = line.substr(0, commaPos);
	std::string rate = line.substr(commaPos + 1);

	dataBase_[date] = std::atof(rate.c_str());
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
		{
			std::cout << "line " << lineNum << " format is not correct: "
				<< line <<" continued" << "\n";
		}
		else
			addLineToDataBase(line);
	}
}
