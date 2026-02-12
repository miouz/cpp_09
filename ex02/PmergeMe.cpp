#include "PmergeMe.hpp"

static size_t jacobsthalSuit[19] = {1, 3, 5, 11, 21,
	43, 85, 171, 341, 683, 1365, 2731,
	5461, 10923, 21845, 43691, 87381, 174763, 349525};

static size_t count = 0;

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
		if (++count && *firstNumInPair > *secondNumInPair)
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

std::vector<int>::iterator binaryInsertNthPair( std::vector<int>::iterator toCompareB,
											   std::size_t numsInPair, std::vector<int>& nums, std::vector<int>::iterator end)
{
	std::vector<int>::iterator begin = nums.begin() + numsInPair - 1;
	std::vector<int>::iterator middle;
	int size = 0;
	while ((end - begin)/numsInPair > 1)
	{
		size = (end - begin)/numsInPair;
		middle = begin + ((size - 1) / 2 + 1) * numsInPair;
		if (++count && *toCompareB <= *middle)
			end = middle;
		else
		 	begin = middle + numsInPair;
	}
	if (++count && *toCompareB <= *begin)
		return begin - (numsInPair - 1);
	else if (++count && begin != end && *toCompareB <= *end)
		return end - (numsInPair - 1);
	else
	 	return end + 1;
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
	std::vector<size_t> jacobsthal(jacobsthalSuit, jacobsthalSuit + 19);
	size_t amountOfTotalPair = nums.size() / numsInPair;
	size_t amountOfSmallerPair = amountOfTotalPair % 2 + amountOfTotalPair / 2;
	size_t amountOfBiggerPair = amountOfTotalPair - amountOfSmallerPair;
	std::vector<int> rested;
	if (nums.size() > amountOfTotalPair * numsInPair)
	{
		rested.reserve(nums.size() - amountOfTotalPair * numsInPair);
		rested.insert(rested.begin(),nums.begin() + (amountOfTotalPair) * numsInPair, nums.end());

	}

	#ifdef DEBUG
	{
		std::cout << "==========================================================================\n";
		std::cout << "nums is ";
		PmergeMe::printContent(nums);
		std::cout << "numsInPair is " << numsInPair << "\n";
		std::cout << "rested is ";
		PmergeMe::printContent(rested);
	}
	#endif

	std::vector<int> chainAOriginal;
	chainAOriginal.reserve(amountOfBiggerPair * numsInPair);
	std::vector<int> chainBOriginal;
	chainBOriginal.reserve(amountOfSmallerPair * numsInPair);
	initChainAB(nums, chainAOriginal, chainBOriginal, numsInPair);
	//using nums as mainchain C
	nums.clear();
	nums.reserve(chainAOriginal.size() + chainBOriginal.size() + rested.size());
	//add b1 a1 to mainchain C
	nums.insert(nums.begin(), chainBOriginal.begin(), chainBOriginal.begin() + numsInPair);
	nums.insert(nums.begin() + numsInPair, chainAOriginal.begin(), chainAOriginal.begin() + numsInPair);


	#ifdef DEBUG
	{
		std::cout << "chainAOriginal:\n";
		PmergeMe::printContent(chainAOriginal);
		std::cout << "chainBOriginal:\n";
		PmergeMe::printContent(chainBOriginal);
		std::cout << "mainchain now:\n";
		PmergeMe::printContent(nums);
		std::cout << "insertion in jacobsthal order begin\n";
		std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	}
	#endif

	for(std::vector<size_t>::const_iterator itJacob = jacobsthal.begin(); itJacob != jacobsthal.end(); itJacob++)
	{
		if (*itJacob == 1)
			continue;
		std::size_t NthPairInB = *itJacob;
		//if less than *itJacob groups but more than *(itJacob -1)
		if (*itJacob * numsInPair > chainBOriginal.size() && (*(itJacob - 1) + 1) * numsInPair <= chainBOriginal.size())
			NthPairInB = chainBOriginal.size() / numsInPair;
		//if less than &itJacob groups
		else if (*itJacob * numsInPair > chainBOriginal.size())
			break;

		//add chainA from A[NthPairInB] ~ to A[*(itJacob -1) + 1](inclus) to mainchain(the reseted vector nums) to insert B into it
		size_t endOfAToSort = NthPairInB;
		//if A[N] doesn't exist
		if (chainAOriginal.size() < NthPairInB * numsInPair)
			endOfAToSort = chainAOriginal.size() / numsInPair;
		size_t beginOfAToSort = *(itJacob - 1) + 1;
		size_t newAddedOnMainchain = nums.size();
		std::vector<int>::iterator itBeginOfAToSort = chainAOriginal.begin() + (beginOfAToSort - 1) * numsInPair;
		std::vector<int>::iterator itEndOfAToSort = chainAOriginal.begin() + endOfAToSort * numsInPair - 1; 
		nums.insert(nums.end(), itBeginOfAToSort, itEndOfAToSort + 1);
		

		#ifdef DEBUG
		{
			std::cout << "*itJacob is " << *itJacob << "\n";
			std::cout << "added A"<< beginOfAToSort <<" until A" << endOfAToSort << "to mainchain\n";
			std::cout << "to insert B"<< NthPairInB <<" until B" << *(itJacob -1) + 1 << "to mainchain\n";
			std::cout << "mainchain after A added ";
			PmergeMe::printContent(nums);
			std::cout << "==========================================================================\n";
		}
		#endif

		//creat and initialize the vector to track how many elements inserted before each A[N]
		// std::vector<int> insertionTrack(endOfAToSort - beginOfAToSort + 1, 0);
		for (size_t toInsertNthPairInB = NthPairInB; toInsertNthPairInB > *(itJacob - 1); toInsertNthPairInB--)
		{
			if (toInsertNthPairInB == 1)
				break ;
			std::vector<int>::iterator	toCompareB = chainBOriginal.begin() + numsInPair *(toInsertNthPairInB - 1) + (numsInPair - 1);

			#ifdef DEBUG
			{
				std::cout << "inserting : B" <<toInsertNthPairInB << "\n";
				std::cout << " = " << *toCompareB << "\n";
				std::cout << "numsInPair is " << numsInPair << "\n";
			}
			#endif

			//find A[N] position on mainchain nums
			std::vector<int>::iterator toCompareUntilOnA;
			std::vector<int>::iterator toCompareUntilOnMain;
			//if A[N] doesnt exist, then compare until A[N -1](inclus) on mainchain
			if (toInsertNthPairInB * numsInPair > chainAOriginal.size())
			{
				toCompareUntilOnA = chainAOriginal.end() - 1;
				toCompareUntilOnMain = std::find(nums.begin() + newAddedOnMainchain, nums.end(), *toCompareUntilOnA);

			#ifdef DEBUG
			{
				std::cout << "A" << toInsertNthPairInB << "doesnt exit:\n" << "compare using binary insertion until A" << chainAOriginal.size()/numsInPair <<" (INCLUS)"
						<< " => "<< *toCompareUntilOnMain <<"(inclus)"<< "\n";
			}
			#endif
			}
			// if A[N] exits, then compare until A[N](exclus) on mainchain
			else {
				toCompareUntilOnA = chainAOriginal.begin() + toInsertNthPairInB * numsInPair - 1;
				toCompareUntilOnMain = std::find(nums.begin() + newAddedOnMainchain, nums.end(), *toCompareUntilOnA);
				toCompareUntilOnMain -= numsInPair;
			#ifdef DEBUG
			{
					std::cout << "newAddedOnMainchain = " << newAddedOnMainchain << "\n"
						<< "find begin from " << *(nums.begin() + newAddedOnMainchain) << "until " << *(nums.end() -1) <<"\n";
				std::cout << "A" << toInsertNthPairInB << "EXIST:\n" << "compare using binary insertion BEFORE A" << *toCompareUntilOnA <<" (EXCLUS)"
						<< " => "<< *toCompareUntilOnMain <<"(inclus)"<< "\n";
			}
			#endif
			}

			//binary research from B1, A1, A2... until A[N]-numsInPair(inclus)
			std::vector<int>::iterator toInsertOnMain = binaryInsertNthPair(toCompareB, numsInPair, nums, toCompareUntilOnMain);
		#ifdef DEBUG
			std::cout << "to insert at place of " << *toInsertOnMain << "\n";
		#endif
			if (toInsertOnMain <= nums.begin() + newAddedOnMainchain)
				newAddedOnMainchain += numsInPair;
			nums.insert(toInsertOnMain, toCompareB - (numsInPair - 1), toCompareB + 1 );
		#ifdef DEBUG
			std::cout << "after insertion of B is ";
			PmergeMe::printContent(nums);
			std::cout << "==========================================================================\n";
		#endif
		}
		
	}
	nums.insert(nums.end(),rested.begin(), rested.end());
}

/**
 * @brief recursive Merge Insertion sort
 *
 * @param nums the actual vector contains all index of numbers
 * @param numsInPair quantities of numbers in each pair
 */
void PmergeMe::recursiveSort(std::vector<int>& nums, std::size_t numsInPair)
{
	sortPair(nums, numsInPair);
	if (nums.size() / numsInPair == 2)
		return ;
	recursiveSort(nums, numsInPair * 2);
	insertion(nums, numsInPair);
	std::cout << "COMPARASION:" << count <<"\n";
}
