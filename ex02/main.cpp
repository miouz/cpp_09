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

void printArgs(char** argv)
{
	while(*(++argv))
		std::cout << std::setw(5) << *argv << ' ';
	std::cout << "\n";
}

unsigned long long getUtime()
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (static_cast<unsigned long long>(tv.tv_sec) * 1000000.0
		+ static_cast<unsigned long long>(tv.tv_usec));
}

int main(int argc, char** argv)
{
	try {
		std::cout <<"Before: ";
		printArgs(argv);
		count = 0;
		std::vector<int> numsVector;
		unsigned long long startVecTime = getUtime();
		PmergeMe::getNumsFromArg(argc, argv, numsVector);
		PmergeMe::recursiveSort(numsVector, 1);
		unsigned long long vecTime = getUtime() - startVecTime;
		std::cout <<"After:  ";
		PmergeMe::printContent(numsVector);
		std::cout << "Max comparaison counts should be:"
			<< F(argc -1) << "\n"
			<<"Real time comparaison counts: "
			<< count << "\n"
			<< "Time to process a range of " << argc -1 
			<< " elements with [ std::vector<int> ]  " << vecTime << " microseconds"<< "\n";


		count = 0;
		std::deque<int> numsDeque;
		unsigned long long startDeqTime = getUtime();
		PmergeMe::getNumsFromArg(argc, argv, numsDeque);
		PmergeMe::recursiveSort(numsDeque, 1);
		unsigned long long deqTime = getUtime() - startDeqTime;
		std::cout << "Time to process a range of " << argc -1 
			<< " elements with [ std::deque<int> ]   " << deqTime << " microseconds"<< "\n";

	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}
