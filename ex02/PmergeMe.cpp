#include "PmergeMe.hpp"

static const size_t jacobsthal[11] = {1, 3, 5, 11, 21,
	43, 85, 171, 341, 683, 1365};

/**
 * @brief finds larger element of each pair and place it on the most right place
 * @detail it moves all numsInPair elements related to the number in pair to the most right position.
 * for example: [0, 10, 3, 5, 9] in a container of numsInPair = 2,
 * we get [0, 10] pairs [3, 5] , then we compare 10 and 5
 * since 10 > 5, we moves [0, 10] to the right of [3, 5], so the container becomes[3,5,0,10,9]
 *
 * @param nums the vector container containes all numbers
 * @param numsInPair number of elements in each pair
 */
void sortPair(std::vector<int>& nums, std::size_t numsInPair)
{
	for ( std::vector<int>::iterator secondNumInPair = nums.begin() + (numsInPair * 2 - 1);
		secondNumInPair < nums.end();
		secondNumInPair += numsInPair * 2)
	{
		std::vector<int>::iterator firstNumInPair = secondNumInPair - numsInPair;
		if (*firstNumInPair > *secondNumInPair)
		{
			std::vector<int>::iterator firstNumInFirstPair = firstNumInPair - (numsInPair - 1);
			std::vector<int>::iterator firstNumInSecondPair = secondNumInPair - (numsInPair - 1);
			std::swap_ranges(firstNumInFirstPair,
					firstNumInSecondPair, firstNumInSecondPair);
		}
	}
}


/**
 * @brief init mainchain A and toinsert chain B:
 * A is:  a1, a2, a3 ...
 * B is: b1, b3, b4, b5 ... 
 *
 * @param nums reference of full vector container
 * @param chainAOriginal reference of pre-allocated mainchain A
 * @param chainBOriginal reference of pre-allocated smaller pair B
 * @param numsInPair numbers of elements in a pair
 */
void initChainAB(std::vector<int>& nums, std::vector<int>& chainAOriginal, std::vector<int>& chainBOriginal,
				  std::size_t numsInPair)
{
	for (std::size_t NthPair = 0; NthPair < nums.size() / numsInPair; NthPair++)
	{
		std::vector<int>::iterator beginOnNums = nums.begin() + NthPair * numsInPair;
		std::vector<int>::iterator endOnNums = beginOnNums + numsInPair;

		//insert to B
		if (NthPair % 2 == 0)
			chainBOriginal.insert(chainBOriginal.end(), beginOnNums, endOnNums);
		//insert to A
		else
			chainAOriginal.insert(chainAOriginal.end(), beginOnNums, endOnNums);
	}
}

void BinaryInsertNthPair(std::vector<int>& nums, std::vector<int>& mainchainA, std::vector<int>& toInsertB,
						 const std::vector<int>::iterator& toCompareB, std::size_t numsInPair, std::vector<int>& insertionTrack)
{
	size_t amountOfPairsInA = mainchainA.size() / numsInPair;
	std::vector<int>::iterator sortedUntilOnA = mainchainA.begin() + amountOfPairsInA / 2 * numsInPair + numsInPair - 1;
}

/**
 * @brief split nums in 2 chain a and b, insert Nth smaller group b[N] in pairs into the main chain a , N is in jacobsthal's order
 * then copy back to nums to update the container
 *
 * @param nums the vector contains all numbers with all larger elements in pairs recursively sorted
 * @param numsInPair number of elements in each pair
 */
void insertion(std::vector<int>& nums, std::size_t numsInPair)
{
	size_t amountOfSmallerPair = (nums.size() / numsInPair) % 2 + (nums.size() / numsInPair) / 2;
	size_t amountOfBiggerPair = amountOfSmallerPair % 2 > 0 ? amountOfSmallerPair - 1 : amountOfSmallerPair;
	std::vector<int> chainAOriginal;
	chainAOriginal.reserve(amountOfBiggerPair * numsInPair);
	std::vector<int> insertionTrack(amountOfBiggerPair);
	std::vector<int> chainBOriginal;
	chainBOriginal.reserve(amountOfSmallerPair * numsInPair);
	initChainAB(nums, chainAOriginal, chainBOriginal, numsInPair);
	//clear num for using as mainchain C
	nums.clear();
	//add b1 to mainchain C
	nums.insert(nums.end(), chainBOriginal.begin(), chainBOriginal.begin() + numsInPair);


	//PRINT_TEST
	std::cout << "numsInPair is " << numsInPair << "\n";
	std::cout << "chainAOriginal:\n";
	PmergeMe::printContent(chainAOriginal);
	
	std::cout << "chainBOriginal:\n";
	PmergeMe::printContent(chainBOriginal);


	for (size_t index = 1; jacobsthal[index] <= amountOfSmallerPair; index++)
	{
		//add chainA from A[jacobsthal[index - 1] ~ to A[jacobsthal[index]] to nums to insert B into it
		size_t endOfAToSort = jacobsthal[index];
		size_t beginOfAToSort = jacobsthal[index - 1];
		std::vector<int>::iterator itBeginOfAToSort = chainAOriginal.begin() + (beginOfAToSort - 1) * numsInPair;
		std::vector<int>::iterator itEndOfAToSort = chainAOriginal.begin() + endOfAToSort * numsInPair - 1; 
		nums.insert(nums.end(), itBeginOfAToSort, itEndOfAToSort + 1);
		std::cout << "indexOfASorted " << endOfAToSort << "\n";
		for (size_t NthPairInB = jacobsthal[index]; NthPairInB > jacobsthal[index - 1]; NthPairInB--)
		{
			std::vector<int>::iterator	toCompareB = chainBOriginal.begin() + numsInPair *(NthPairInB - 2) + (numsInPair - 1);
			//PRINT_TEST
			std::cout << "index is " <<NthPairInB << "\n";
			std::cout << "toCompareB is " << *toCompareB << "\n";
			std::cout << "numsInPair is " << numsInPair << "\n";
			
			BinaryInsertNthPair(nums, chainAOriginal, chainBOriginal,
					   toCompareB, numsInPair, insertionTrack);
		}
	}
}

/**
 * @brief recursive Merge Insertion sort
 *
 * @param nums the actual vector contains all index of numbers
 * @param numsInPair quantities of numbers in each pair
 */
void PmergeMe::recursiveSort(std::vector<int>& nums, std::size_t numsInPair)
{
	//PRINT_TEST
	std::cout << "numsInPair is " << numsInPair<< "\n";
	std::cout << "vector at begin of recursive:\n";
	PmergeMe::printContent(nums);

	sortPair(nums, numsInPair);

	//PRINT_TEST
	std::cout << "after sortPair:\n";
	PmergeMe::printContent(nums);
	if (nums.size() / numsInPair == 2)
		return ;
	recursiveSort(nums, numsInPair * 2);
	insertion(nums, numsInPair);
}
