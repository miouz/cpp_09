#include "utils.hpp"

bool isLeapYear(unsigned int year)
{
	if ((year % 4 == 0 && year % 100 != 0)
		|| year % 400 == 0)
		return true;
	return false;
}

void getValidFloatInRange(std::string& str, float& result, float min, float max)
{
	errno = 0;
	char *endptr;
	float num = std::strtof(str.c_str(), &endptr);
	if (*endptr != '\0'
		|| endptr == str.c_str()
		|| errno != 0
		|| num < min
		|| num > max)
		throw std::runtime_error("not valid number in range");
	result = num;
}

void getValidIntInRange(std::string& str, int& result, long int min, long int max)
{
	errno = 0;
	char *endptr;
	long int num = std::strtol(str.c_str(), &endptr, 10);
	if (*endptr != '\0'
		|| endptr == str.c_str()
		|| errno != 0
		|| num < min
		|| num > max)
		throw std::runtime_error("not valid number in range");
	result = static_cast<int>(num);
}

bool isValidDate(std::string& date)
{
	try {
		std::string year = date.substr(0, 4);
		std::string month = date.substr(6, 8);
		std::string day = date.substr(10, 12);
		int yearNum = 0;
		int monthNum = 0;
		int dayNum= 0;
		int daysRange[12] = {31, 28, 31, 30, 31,
				30, 31, 31, 30, 31, 30, 31};

		if (date[5] == '-'
			&& date[9] == '-')
		{
			getValidIntInRange(year, yearNum, 2009, 2999);
			getValidIntInRange(month, monthNum, 1, 12);
			getValidIntInRange(day, dayNum, 1, daysRange[monthNum - 1]);
			if (monthNum == 2 && isLeapYear(yearNum) && dayNum != 29)
				return false;
			return true;
		}
		return false;
	} catch (...) {
		return false;
	}
}

bool isValidRate(std::string& rate)
{
	try {
		float result;
		getValidFloatInRange(rate, result,
			std::numeric_limits<float>::min(), std::numeric_limits<float>::max());
		return true;
	} catch (...) {
		return false;
	}
}
