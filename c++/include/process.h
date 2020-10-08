#ifndef _PROCESS_H_
#define _PROCESS_H_

#include <string>
#include <iostream>
#include <vector>

/**
 * Represents an executable process with arguments.
 * @author Brian Sea
 */
class Process {
    
    private:
        // The command to exectute and command-line arguments
        std::string command;
        std::vector<std::string> arguments;

    public:
        Process(const std::string &command = "");
        Process(const std::string &command, const std::string argument);
        Process(const std::string &command, const std::vector<std::string> &arguments);
        Process(const Process& copy);
        ~Process();

        /**
         * Reset and clear the processes commands and arguments
         * 
         * @param clearCommand true to clear the command also
         */
        void clear( bool clearCommand = true);

        /**
         * Set and get the command
         */
        void setCommand(const std::string &command);
        const std::string& getCommand() const;

        /**
         * Add to the argument list for this process
         */
        void addArgument(const std::string &arg);


        /** 
         * Get the number of arguments in this process
         * @return number of arguments >= 0
         */
        const int numArguments() const;

        /**
         * Get read-only versions of the arguments
         * @return a read-only vector of the arguments
         */
        const std::vector<std::string>& getArguments() const;

        /**
         * Get read-only version of an argument at a particular 
         * index [0...size-1]
         * 
         * @param index index of the argument to get [0...size-1]
         * @return a read-only version of the argument requested
         * @throw out_of_range exception if index is outside the list
         */
        const std::string& getArgument( long unsigned index ) const;

        /**
         * Overloaded casting to a string
         * Allows for the conversion from a Process to a string
         */
        operator std::string() const;

        /**
         * Overload the [] operator to access specfic arguments
         * @return a read-only version of the argument requested
         * @throw out_of_range exceptif if the index is outside the list 
         */
        const std::string &operator[](long unsigned index) const;

        /**
         * Overload the << operator to allow output to a stream
         */
        friend std::ostream& operator<<( std::ostream &out, const Process &p);
};

#endif