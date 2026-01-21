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

	if (file.is_open() == false)
		throw std::invalid_argument("could not open file.");
	while (std::getline(file, line))
	{
		if (isValidDataLine(line) == false)
			std::cout << "line " << dataBase_.size() << " format is not correct: "
				<< line <<" \" continued" << "\n";
		else
			addLineToDataBase(line);
	}
}

bool BitcoinExchange::isValidDataLine(const std::string& line) const
{
	std::string::iterator = line.find('|');


}
void BitcoinExchange::addLineToDataBase(const std::string& line)
{

}
