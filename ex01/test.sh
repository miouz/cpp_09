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

PROGRAM="./RPN"

if [ ! -f $PROGRAM ]; then
	printf "${RED} Error: $PROGRAM do not exit\n${RESET}"
	exit 1
fi

run_test(){
	local input="$1"
	local discription="$2"
	local output=$($PROGRAM "$input")

	printf "${YELLOW}Test: ${GREEN}[$input] Case: [$discription]\n${RESET}"
	printf "%s\n" "$output"
	printf "\n"
}

printf "${GREEN}==========NO ARGUMENTS TEST=============${RESET}\n"
$PROGRAM

printf "${GREEN}==========INVALID ARGUMENTS TEST=============${RESET}\n"
run_test "" "empty string test"
run_test " a b + " "invalid input: no digit"
run_test " 100 10 +" "invalid input: more than 1 digit"
run_test " + + " "invalid input: operator before number"
run_test "-1 -3 * " "negatif one digit"

printf "${GREEN}==========CALCULATE ERROR TEST=============${RESET}\n"
run_test "1 0 / " "division by zero"
run_test "1 0 0 + / " "division by zero"
run_test "9 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 * 9 *" "int overflow"


printf "${GREEN}==========NO ERROR TEST=============${RESET}\n"
run_test "5 1 2 + 4 * + 3 -" "expected: 14"
run_test "1 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 + 1 +" "expected 20"
