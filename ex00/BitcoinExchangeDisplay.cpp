#include "BitcoinExchange.hpp"

static const float evaluateValueMin = 0;
static const float evaluateValueMax = 1000;

float BitcoinExchange::getRateOfDay(const std::string& date) const
{
	std::map<std::string, float>::const_iterator it = dataBase_.upper_bound(date);
	if (it == dataBase_.begin())
		throw std::invalid_argument("date too early: " + date);
	return (--it)->second;	
}

void BitcoinExchange::displayValueFromLine(const std::string& line) const
{
	size_t barPos = line.find("|");
	if (barPos == std::string::npos)
		throw std::invalid_argument("bad input => " + line);
	std::string date = line.substr(0, barPos);
	std::string value = line.substr(barPos + 1);
	float valueNum = 0;

	if (isValidDate(date) == false)
		throw std::invalid_argument("bad date format: " + date);
	getValidPositiveFloatInRange(value, valueNum, evaluateValueMin, evaluateValueMax );
	float rate = getRateOfDay(date);
	double outputValue = rate * valueNum;
	std::cout << date << "=>" << value << " = " << outputValue << std::endl;
}

void BitcoinExchange::displayValueFromFile(const std::string& fileName) const
{
	std::ifstream input(fileName.c_str(), std::ios::in);
	std::string	line;
	bool isFirstLine = true;

	if (!input.is_open())
		throw std::runtime_error("couldn't open input file");
	while (std::getline(input, line))
	{
		if(isFirstLine == true)
		{
			isFirstLine = false;
			continue;
		}
		try {
		displayValueFromLine(line);
		} catch (std::exception& e) {
			std::cout << "Error: " << e.what()<< std::endl;
		}
	}
}
