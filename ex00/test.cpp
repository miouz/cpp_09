#include "test.hpp"
#include <fstream>

void testEx01()
{
	int array[4] = {0, 7, 3890, -56};

	PRINT_HEADER("TEST FOR SPAN CLASS");
	{
		Span span4(4);
		span4.addNumber(array, array + sizeof(array)/sizeof(int));
		span4.printElements();
		
		PRINT_SUBHEADER("test for copy constructor's deep copy");
		Span span4Copy(span4);
		span4Copy.printElements();
		
		PRINT_SUBHEADER("test for = operator's deep copy");
		Span span0 = span4;
		span0.printElements();
	}


	PRINT_HEADER("TEST FOR ADDNUMBER");
	{
		Span span4(4);
		span4.addNumber(array, array + sizeof(array)/sizeof(int));
		span4.printElements();
		PRINT_SUBHEADER("add 1 number exceed max capacity");
		try {
			span4.addNumber(100);
		} catch (std::exception& e) {
			std::cout << e.what()<<std::endl;
		}

		PRINT_SUBHEADER("add 10 numbers successfully");
		int array10[10] = {0,1,2,3,4,5,6,7,8,9};
		Span span19(19);
		try {
			span19.addNumber(array10, array10+10);
			span19.printElements();
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;	
		}

		PRINT_SUBHEADER("add 10 numbers exceed max capacity");
		try {
			span19.addNumber(array10, array10+10);
			span19.printElements();
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;	
		}

		PRINT_SUBHEADER("add 10 000 numbers successfully once");
		try {
			std::vector<int> intVec(10000, -56);
			Span span10000(10000);
			span10000.addNumber(intVec.begin(), intVec.end() - 1);
			std::cout << "added 10000 numbers\n";
		} catch (std::exception& e) {
			std::cout << e.what() << std::endl;
		};
	}


	PRINT_HEADER("TEST FOR SHORTEST SPAN");
	{
		PRINT_SUBHEADER("empty element can't find shortest span");
		{
			Span emptySpan;
			try {
			std::cout << emptySpan.shortestSpan();
			} catch (std::exception& e) {
			std::cout << e.what()<<std::endl;
			}
		}

		PRINT_SUBHEADER("only 1 element can't find shortest span");
		{
			Span span1(1);
			span1.addNumber(10);
			try {
			std::cout << span1.shortestSpan();
			} catch (std::exception& e) {
				std::cout << e.what()<< std::endl;
			}

		PRINT_SUBHEADER("find shortest span of 4 element array");
		{
			Span span(1000000);
			span.addNumber(array, array+4);
			span.printElements();
			try {
			std::cout << span.shortestSpan()<< "\n";
			span.addNumber(-1);
			span.printElements();
			std::cout << "shortest span is: "<< span.shortestSpan()<< "\n";
			} catch (std::exception& e) {
				std::cout << e.what()<< std::endl;
			}
		PRINT_SUBHEADER("add 10000 times number 0");
			std::vector<int> arr9(10000, 0);
			span.addNumber(arr9.begin(), arr9.end() - 1);
			std::cout << "expected shortest is 0 \n";
			try {
			std::cout <<"shortest span is: "<< span.shortestSpan()<< "\n";
			} catch (std::exception& e) {
				std::cout << e.what()<< std::endl;
			}

		}
		}
	}


	PRINT_HEADER("TEST FOR LONGEST SPAN");
	{
		PRINT_SUBHEADER("empty element can't find longest span");
		{
			Span emptySpan;
			try {
			emptySpan.longestSpan();
			} catch (std::exception& e) {
					std::cout << e.what()<<std::endl;
			}
		}

		PRINT_SUBHEADER("only 1 element can't find longtest span");
		{
			Span span1(1);
			span1.addNumber(10);
			try {
			std::cout << span1.longestSpan();
			} catch (std::exception& e) {
				std::cout << e.what()<< std::endl;
			}

		PRINT_SUBHEADER("find longest span of 4 element array");
		{
			Span span(1000000);
			span.addNumber(array, array+4);
			span.printElements();
			try {
			std::cout << span.longestSpan()<< "\n";
			span.addNumber(-1);
			span.printElements();
			std::cout << "longest span is: "<< span.longestSpan()<< "\n";
			} catch (std::exception& e) {
				std::cout << e.what()<< std::endl;
				}
			
		PRINT_SUBHEADER("add 10000 times number 7890000");
			std::vector<int> arr9(10000, 7890000);
			span.addNumber(arr9.begin(), arr9.end() - 1);
			std::cout << "expected longest is 7890056 \n";
			try {
			std::cout <<"longest span is: "<< span.longestSpan()<< "\n";
			} catch (std::exception& e) {
				std::cout << e.what()<< std::endl;
			}

		
		}
	}
}
