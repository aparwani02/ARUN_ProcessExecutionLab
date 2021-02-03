#include "shell_utils.h"


#include <string>
#include <vector>

/**
 * Interrupt Handler which outputs and exits the program for Control-C
 */
void handle_SIGINT(int signum){
    std::cout << std::endl << "Shell Exiting..." << std::endl;
    exit(signum);
}

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
std::vector<Process> parseString(std::string input ){

    // Verify that the string ends with a newline
    if( input.back() != '\n'){
        input += '\n';
    }
    
    std::vector<Process> processes;

    // Create our first process to populate
    // We use a pointer here since we'll be making new ones throughout execution
    Process currProcess; 

    // Used to tokenized the string
    bool endProcess = false;            // Detected end of a Process
    int startCopy = 0;                  // Starting index of copy
    int index = 0;                      // Ending index of copy

    // Detecting quotes:  -1 = not found, 2 = entered quotes, -2 = exited quotes
    int inSingleQuotes = -1;
    int inDoubleQuotes = -1;

    // We iterate through the string to decrease time complexity
    std::string::iterator it = input.begin();
    while( it != input.end() ){

        // Detecting first entry into quotes
        if( *it == '\"' && inSingleQuotes < 0 ){
            inDoubleQuotes *= -2;
        }
        if( *it == '\'' && inDoubleQuotes < 0 ){
            inSingleQuotes *= -2;
        }

        if( inSingleQuotes < 0 && inDoubleQuotes < 0 ){
            // Not in quotes, so check for process ending characters
            if( *it == '|' || *it == '<' || *it == '>' ){
                endProcess = true;
            }

            // Process, word, or line as ended 
            if( endProcess || *it == ' ' || *it == '\n' ){

                // Capture the detected substring of the command string
                std::string argStr = input.substr(startCopy, index-startCopy);
                startCopy = index + 1;
                
                // We're exiting quotes, so we need to take them off our string
                if( inSingleQuotes < -1 || inDoubleQuotes < -1 ){
                    argStr = argStr.substr(1,argStr.size()-2);
                    inSingleQuotes = inDoubleQuotes = -1;
                }

                if( argStr.size() > 0 ){
                    // Command hasn't been set, so this is first word of a process
                    if( currProcess.getCommand().size() == 0 ){
                        currProcess.setCommand(argStr);
                    }
                    else {
                        // Argument otherwise, so add it to our list
                        currProcess.addArgument(argStr);
                    }
                }
            }

            // We've ended a process...
            if( endProcess ){
                // .. with a non-empty command. So add it to our process list
                //    and clear out the Process to populate a new one
                if( currProcess.getCommand().size() > 0 ){

                    // Calls the copy constructor!
                    processes.push_back(currProcess);
                    currProcess.clear();
                }
                // reset parsing
                endProcess = false;
            }

        }

        // Keep track of our index and iterate forward
        // We keep track of both because iterators are faster than index access
        index++;
        it++;
    }

    // Capture a process which completes with the end of the line
    if( !endProcess && currProcess.getCommand().size() > 0 ){
        // Quotes matched, so add it to our list
        if( inDoubleQuotes < 0 && inSingleQuotes < 0 ){
            processes.push_back(currProcess);
        }
        else {
            // Quote mismatch!
            throw std::out_of_range("Mismatched Quotes");
        }
    }

    return processes;
}