#include<iostream>
#include<string>
#include<csignal>

#include "process.h"
#include "shell_utils.h"

int main( int argc, char* argv[] ){
    // Setup an interrupt handler for SIGINT (Control-C)
    signal(SIGINT, handle_SIGINT);

    std::string input;
    std::cout<<"> ";
    // Grab a line of input.  The loop doesn't run when Control-D is input.
    while(getline(std::cin, input)){
        input += '\n';

        try {

            // Try to parse the string for processes and print them to stdout
            std::vector<Process> processes = parseString(input);
            std::vector<Process>::iterator it = processes.begin();
            
            int processNum = 0;
            while( it != processes.end() ){
                std::cout <<"-------------------\n";
                std::cout <<"Process "<<processNum<<std::endl;
                std::cout <<"--------------------\n";
                std::cout << (std::string)(*it) << std::endl;

                it++;
            }
        }
        catch(std::out_of_range &oor){

            // The oor exception shouldn't happen
            std::cerr << "Error: " << oor.what() << std::endl;
        }
        
        std::cout<<"> ";  
    }

    return 0;
}