#!/bin/bash

#color variables
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[0;37m'
RESET='\033[0m'

PROGRAM="./PmergeMe"

if [ ! -f $PROGRAM ]; then
	printf "${RED} Error: $PROGRAM do not exit\n${RESET}"
	exit 1
fi

run_test(){
	local discription="$1"
	shift
	local args="$@"
	local output="$($PROGRAM $args 2>&1)"

	printf "${YELLOW}Test: ${GREEN}[$discription] Case: [$args]\n${RESET}"
	printf "%s\n" "$output"
	printf "\n"
}

printf "${GREEN}==========NO ARGUMENTS TEST=============${RESET}\n"
$PROGRAM

printf "${GREEN}==========INVALID ARGUMENTS TEST=============${RESET}\n"
run_test "empty string" ""
run_test "invalid input" 10 ab 900 3
run_test "negatif integer" 100 -1 -3
run_test "integer overflow" 1 0 2147483648

printf "${GREEN}==========SORTING NO ERROR=============${RESET}\n"
run_test "1 integer" 0
run_test "2 integers" 98 25
run_test "3 integers" 692 253 0
run_test "4 integers" 920 0 45 890
run_test "7 integers" 5 20 0 987654 258 36 7
run_test "copies" 0 9 456 0 0 9 2
run_test "3000 numbers" `shuf -i 1-100000 -n 3000 | tr "\n" " "`
