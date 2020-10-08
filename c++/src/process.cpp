#include "process.h"

#include <sstream>

Process::Process(const std::string &command) {
    this->command = command;
}

Process::Process(const std::string &command, const std::string argument){
    this->command = command;
    this->arguments.push_back(argument);
}

Process::Process(const std::string &command, const std::vector<std::string> &arguments){
    this->command = command;
    for( std::string arg : arguments ){
        this->arguments.push_back(arg);
    }
}

Process:: Process(const Process & copy ){
    this->command = copy.getCommand();
    for( int i = 0; i < copy.numArguments(); i++ ){
        this->addArgument(copy[i]);
    }
}

Process::~Process(){
}

void Process::clear(bool clearCommand){
    if( clearCommand ) {
        this->command = "";
    }

    this->arguments.clear();
}

void Process::setCommand(const std::string &command){
    this->command = command;
}
const std::string& Process::getCommand() const{
    return this->command;
}

const int Process::numArguments() const {
    return this->arguments.size();
}

void Process::addArgument(const std::string &arg){
    this->arguments.push_back(arg);
}

const std::vector<std::string>& Process::getArguments() const{
    return this->arguments;
}
const std::string& Process::getArgument( const long unsigned index ) const{
    // Note: at() could throw an out_of_range exception
    return this->arguments.at(index);
}

Process::operator std::string() const {

    std::ostringstream stringStream;

    // Attach the process command to the stream
    stringStream << "Command: " << this->command <<'\n';
    stringStream << "Arguments\n";

    // Iterate through the arguments and send them to the stream
    int spot = 0;
    std::vector<std::string>::const_iterator it = this->arguments.begin();
    while( it != this->arguments.end() ){
        stringStream << spot << ": " << *it << '\n';

        spot++;
        it++;
    }

    return stringStream.str();

}

const std::string &Process::operator[](const long unsigned index) const{
    return this->getArgument(index);
}

std::ostream& operator<<( std::ostream &out, const Process &p ){
    // Send the string version of the Process to the out stream
    return out << (std::string)p;
}