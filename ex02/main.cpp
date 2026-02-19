#include "PmergeMe.hpp"
#include <vector>
#include <deque>
#include <ctime>
#include <sys/time.h>
#include <cmath>


int F(int n)
{
    int sum = 0;
    for (int k = 1; k <= n; ++k) {
        double value = (3.0 / 4.0) * k;
        sum += static_cast<int>(ceil(log2(value)));
    }
    return sum;
}

void printBefore(int argc, char** argv)
{
	std::vector<int> toPrint;
	PmergeMe::getNumsFromArg(argc, argv, toPrint);
	std::cout <<"Before: ";
	PmergeMe::printContent(toPrint);
}

unsigned long long getUtime()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (static_cast<unsigned long long>(tv.tv_sec) * 1000000
		+ static_cast<unsigned long long>(tv.tv_usec));
}

int main(int argc, char** argv)
{
	try {
		printBefore(argc, argv);

		count = 0;
		std::vector<int> numsVector;
		unsigned long long startVecTime = getUtime();
		PmergeMe::getNumsFromArg(argc, argv, numsVector);
		PmergeMe::recursiveSort(numsVector, 1);
		unsigned long long vecTime = getUtime() - startVecTime;
		std::cout <<"After:  ";
		PmergeMe::printContent(numsVector);
		std::cout << "Time to process a range of "
			<< argc -1 << " elements with [std::vector<int>]: " << vecTime
			<< " us, max comparaison count: "
			<< F(argc -1) << ", real count " << count
			<< "\n";


		count = 0;
		std::deque<int> numsDeque;
		unsigned long long startDeqTime = getUtime();
		PmergeMe::getNumsFromArg(argc, argv, numsDeque);
		PmergeMe::recursiveSort(numsDeque, 1);
		unsigned long long deqTime = getUtime() - startDeqTime;
		std::cout << "Time to process a range of "
			<< argc -1 << " elements with [std::deque<int>]:  " << deqTime
			<< " us, max comparaison count: "
			<< F(argc -1) << ", real count " << count
			<< "\n";

	} catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}
