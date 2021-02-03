#ifndef _SHELL_UTILS_H_
#define _SHELL_UTILS_H_

#include <vector>
#include <string>

#include "process.h"

/**
 * Interrupt Handler which outputs and exits the program for Control-C
 */
void handle_SIGINT(int signum);

/**
 * Creates Process objects out of a string with the following rules:
 * 1. Processes are separated by one of |, <, >
 * 2. Words are separated by one of |, <, >, or a space
 * 3. The first word of a process is its command
 * 4. Words after the first until the end of the process are arguments
 * 5. Single and Double quotes ignore tokenization rules and are one 'word'
 * 
 * @param input the string to parse
 * @return a series of populated Processes
 * @throw out_of_range if any quotes are mismatched
 */
std::vector<Process> parseString(std::string input);

#endif