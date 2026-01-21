#include <iostream>
#include <string>
#include "Span.hpp"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"

#define PRINT_HEADER(text) \
    std::cout << "\n" << BLUE << "========== " << text << " ==========" << RESET << "\n\n"

#define PRINT_SUBHEADER(text) \
    std::cout << YELLOW << "--- " << text << " ---" << RESET << "\n"


void testEx01();
