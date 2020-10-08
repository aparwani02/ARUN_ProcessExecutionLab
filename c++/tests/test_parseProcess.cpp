#include <vector>

#include "catch.hpp"

// Include the cpp file we're testing
#include "shell_utils.cpp"
#include "process.h"

TEST_CASE( "Parse: One Command - Zero Args", "[classic]") {
    GIVEN("Parse: One Command - Zero Args"){
        std::string commandString = "du";
        std::vector<Process> processes = parseString(commandString);
        CHECK( processes.size() == 1 );
        CHECK( processes[0].numArguments() == 0 );
    }
}

TEST_CASE( "Parse: One Command - Zero Args With Empty String", "[classic]") {
    GIVEN("Parse: One Command - Zero Args With Empty String"){
        std::string commandString = "du \"\"";
        std::vector<Process> processes = parseString(commandString);
        CHECK( processes.size() == 1 );
        CHECK( processes[0].numArguments() == 0 );
    }
}

TEST_CASE( "Parse: One Command - One Args", "[classic]") {
    GIVEN("Parse: One Command - One Args"){
        std::string commandString = "du -l";
        std::vector<Process> processes = parseString(commandString);
        CHECK( processes.size() == 1 );
        CHECK( processes[0].numArguments() == 1 );
    }
}

TEST_CASE( "Parse Counting: Two Command With Spaces", "[classic]") {
    GIVEN("Parse: Two Command With Spaces"){
        std::string commandString = "du -l | ps aux";
        std::vector<Process> processes = parseString(commandString);
        CHECK( processes.size() == 2 );
    }
}

TEST_CASE( "Parse Counting: Two Commands With No Spaces", "[classic]") {
    GIVEN("Parse: Two Commands With No Spaces"){
        std::string commandString = "du -l|ps aux";
        std::vector<Process> processes = parseString(commandString);
        CHECK( processes.size() == 2 );
    }
}

TEST_CASE( "Parse Counting: Two Commands With Mixed Spaces", "[classic]") {
    GIVEN("Parse: Two Commands With Mixed Spaces"){
        std::string commandString = "du -l| ps aux";
        std::vector<Process> processes = parseString(commandString);
        CHECK( processes.size() == 2 );
    }
}

TEST_CASE( "Parse Counting: Three Commands With Mixed Spaces", "[classic]") {
    GIVEN("Parse: Three Commands With Mixed Spaces"){
        std::string commandString = "du -l| ps aux | grep argument";
        std::vector<Process> processes = parseString(commandString);
        CHECK( processes.size() == 3 );
    }
}

TEST_CASE( "Parse Counting: Three Commands With Spaces Zero Args", "[classic]") {
    GIVEN("Parse: Three Commands With Spaces Zero Args"){
        std::string commandString = "du | ps | grep";
        std::vector<Process> processes = parseString(commandString);
        CHECK( processes.size() == 3 );
    }
}

TEST_CASE( "Parse Counting: Three Commands No Spaces One Arg", "[classic]") {
    GIVEN("Parse: Three Commands With No Spaces One Arg"){
        std::string commandString = "du -l| ps aux| grep argument";
        std::vector<Process> processes = parseString(commandString);
        CHECK( processes.size() == 3 );
    }
}

TEST_CASE( "Parse Counting: Three Commands Mixed Spaces One Arg", "[classic]") {
    GIVEN("Parse: Three Commands With Mixed Spaces One Arg"){
        std::string commandString = "du -l | ps aux |grep argument";
        std::vector<Process> processes = parseString(commandString);
        CHECK( processes.size() == 3 );
    }
}

TEST_CASE( "Parse Counting: Three Commands Trailing Spaces One Arg", "[classic]") {
    GIVEN("Parse: Three Commands With Trailing Spaces One Arg"){
        std::string commandString = "du -l |ps aux |grep argument   ";
        std::vector<Process> processes = parseString(commandString);
        CHECK( processes.size() == 3 );
    }
}
    
TEST_CASE( "Parse Counting: Three Commands Leading Spaces One Arg", "[classic]") {
    GIVEN("Parse: Three Commands With Leading Spaces One Arg"){
        std::string commandString = "   du -l |ps aux |grep argument";
        std::vector<Process> processes = parseString(commandString);
        CHECK( processes.size() == 3 );
    }
}

TEST_CASE( "Parse Counting: Three Commands Mixed Spaces Less Than Greater", "[classic]") {
    GIVEN("Parse Counting: Three Commands Mixed Spaces Less Than Greater"){
        std::string commandString = "du -l <ps aux >grep argument";
        std::vector<Process> processes = parseString(commandString);
        CHECK( processes.size() == 3 );
    }
}
    
TEST_CASE( "Parse Counting: Three Commands Mixed Spaces Greater Than Less", "[classic]") {
    GIVEN("Parse Counting: Three Commands Mixed Spaces Greater Than Less"){
        std::string commandString = "du -l >ps aux <grep argument";
        std::vector<Process> processes = parseString(commandString);
        CHECK( processes.size() == 3 );
    }
}

// Verify Correct Commands in Parsed Processes
TEST_CASE( "Parse Commands: One Command One Arg", "[classic]") {
    GIVEN("Parse Commands: One Command One Arg"){
        std::string commandString = "du -l";
        std::vector<Process> processes = parseString(commandString);
        CHECK( processes[0].getCommand() == "du" );
    }
}

TEST_CASE( "Parse Commands: Three Commands One Arg", "[classic]") {
    GIVEN("Parse Commands: Three Commands One Arg"){
        std::string commandString = "du -l | ps aux | grep argument";
        std::vector<Process> processes = parseString(commandString);

        std::string correctCommands[] = {"du", "ps", "grep"};
        for( std::vector<Process>::size_type i = 0; i < processes.size(); i++ ){
            CHECK( processes[i].getCommand() == correctCommands[i] );
        }
    }
}

// Verify correct arguments in parsed processes
TEST_CASE( "Parse Arguments: One Command Two Arg", "[classic]") {
    GIVEN("Parse Arguments: One Command Two Arg"){
        std::string commandString = "du -l apple";
        std::vector<Process> processes = parseString(commandString);

        std::string correctArguments[][5] = {
            {"-l", "apple", "END_ARGS"}
        };
        for( std::vector<Process>::size_type i = 0; i < processes.size(); i++ ){
            std::string *arg = correctArguments[i];
            for( int j = 0; *arg != "END_ARGS"; j++ ) {
                CHECK( processes[i].getArgument(j) == *arg );
                arg++;
            }
        }
    }
}

TEST_CASE( "Parse Arguments: Three Command Variable Arg", "[classic]") {
    GIVEN("Parse Arguments: Three Command Variable Arg"){
        std::string commandString = "du -l | ps aux apple | grep argument";
        std::vector<Process> processes = parseString(commandString);

        std::string correctArguments[][5] = {
            {"-l", "END_ARGS"},
            {"aux", "apple", "END_ARGS"},
            {"argument", "END_ARGS"}
        };
        for( std::vector<Process>::size_type i = 0; i < processes.size(); i++ ){
            std::string *arg = correctArguments[i];
            for( int j = 0; *arg != "END_ARGS"; j++ ) {
                CHECK( processes[i].getArgument(j) == *arg );
                arg++;
            }
        }
    }
}

TEST_CASE( "Parse Arguments: Three Command Zero Arg", "[classic]") {
    GIVEN("Parse Arguments: Three Command Zero Arg"){
        std::string commandString = "du | ps | grep";
        std::vector<Process> processes = parseString(commandString);

        for( std::vector<Process>::size_type i = 0; i < processes.size(); i++ ){
            CHECK( processes[i].getArguments().size() == 0 );
        }
    }
}

// Cause Exceptions To Occur Via Mismatched Quotes
TEST_CASE( "MisMatch Quotes: One Command", "[classic]") {
    GIVEN("MisMatch Quotes: One Command"){
        std::string commandString = "du \"mismatch";
        REQUIRE_THROWS_AS(parseString(commandString), std::out_of_range);
    }
}

TEST_CASE( "MisMatch Quotes: Two Commands", "[classic]") {
    GIVEN("MisMatch Quotes: Two Commands"){
        std::string commandString = "du \"mismatch | welcome";
        REQUIRE_THROWS_AS(parseString(commandString), std::out_of_range);
    }
}

TEST_CASE( "MisMatch Quotes: Two Commads Three quotes", "[classic]") {
    GIVEN("MisMatch Quotes: Two Commads Three quotes"){
        std::string commandString = "du \"mismatch | welcome\" | ps welcome \"bob";
        REQUIRE_THROWS_AS(parseString(commandString), std::out_of_range);
    }
}