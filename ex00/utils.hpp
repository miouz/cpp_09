#ifndef UTILS_CPP
#define UTILS_CPP

#include <string>
#include <cerrno>
#include <iostream>

bool isLeapYear(unsigned int year);
void getValidPositiveFloatInRange(std::string& str, float& result, float min, float max);
void getValidIntInRange(std::string& str, int& result, long int min, long int max);
bool isValidDate(std::string& date);
bool isValidRate(std::string& rate);

#endif // !UTILS_CPP
