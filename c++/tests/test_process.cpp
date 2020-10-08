#include <vector>
#include <sstream>

#include "catch.hpp"

// Include the cpp file we're testing
#include "process.h"

// Testing the Constructor
TEST_CASE( "Process::Constructor Default", "[classic]") {
    GIVEN("Process::Constructor Default"){
        Process process;

        CHECK(process.getCommand() == "");
        CHECK(process.numArguments() == 0);
    }
}

TEST_CASE( "Process::Constructor - One Arg", "[classic]") {
    GIVEN("Process::Constructor - One Arg"){
        Process process("command");

        CHECK(process.getCommand() == "command");
        CHECK(process.numArguments() == 0);
    }
}

TEST_CASE( "Process::Constructor - Two Arg (string, vector)", "[classic]") {
    GIVEN("Process::Constructor - Two Arg (string, vector)"){
        std::vector<std::string> args;
        args.push_back("argument");
        Process process("command", args);

        CHECK(process.getCommand() == "command");
        CHECK(process.numArguments() == 1);
        CHECK(process.getArgument(0) == "argument");
    }
}

TEST_CASE( "Process::Constructor - Two Arg (string, 2 string vector)", "[classic]") {
    GIVEN("Process::Constructor - Two Arg (string, 2 string vector)"){
        std::vector<std::string> args;
        args.push_back("argument");
        args.push_back("argument1");
        Process process("command", args);

        CHECK(process.getCommand() == "command");
        CHECK(process.numArguments() == 2);
        CHECK(process.getArgument(0) == "argument");
        CHECK(process.getArgument(1) == "argument1");
    }
}

TEST_CASE( "Process::Constructor - Two Arg (string, string)", "[classic]") {
    GIVEN("Process::Constructor - Two Arg (string, string)") {
        Process process("command", "arg");

        CHECK(process.getCommand() == "command");
        CHECK(process.numArguments() == 1);
        CHECK(process.getArgument(0) == "arg");
    }
}

TEST_CASE( "Process::Copy Constructor - No Args", "[classic]") {
    GIVEN("Process::Copy Constructor - No Args") {
        Process process("command");
        Process examine( process );

        CHECK(examine.getCommand() == "command");
        CHECK(examine.numArguments() == 0);
    }
}
TEST_CASE( "Process::Copy Constructor - One Arg", "[classic]") {
    GIVEN("Process::Copy Constructor - One Arg") {
        Process process("command", "arg");
        Process examine( process );

        CHECK(examine.getCommand() == "command");
        CHECK(examine.numArguments() == 1);
        CHECK(examine.getArgument(0) == "arg");
    }
}
TEST_CASE( "Process::Copy Constructor - Two Args", "[classic]") {
    GIVEN("Process::Copy Constructor - Two Args") {
        std::vector<std::string> args;
        args.push_back("arg1");
        args.push_back("arg2");
        
        Process process("command", args);
        Process examine( process );

        CHECK(examine.getCommand() == "command");
        CHECK(examine.numArguments() == 2);
        CHECK(examine.getArgument(0) == "arg1");
        CHECK(examine.getArgument(1) == "arg2");
    }
}

TEST_CASE( "Process::Clear - Zero Args", "[classic]") {
    GIVEN("Process::Clear - Zero Args") {
        
        Process process("command");
        process.clear();

        CHECK(process.getCommand() == "");
        CHECK(process.numArguments() == 0);
    }
}

TEST_CASE( "Process::Clear - One Arg", "[classic]") {
    GIVEN("Process::Clear - One Arg") {
        std::vector<std::string> args;
        args.push_back("arg1");
        
        Process process("command", args);
        process.clear();

        CHECK(process.getCommand() == "");
        CHECK(process.numArguments() == 0);
    }
}

TEST_CASE( "Process::Clear - Two Args", "[classic]") {
    GIVEN("Process::Clear - Two Args") {
        std::vector<std::string> args;
        args.push_back("arg1");
        args.push_back("arg2");
        
        Process process("command", args);
        process.clear();

        CHECK(process.getCommand() == "");
        CHECK(process.numArguments() == 0);
    }
}

TEST_CASE( "Process::Clear - Ignore Command", "[classic]") {
    GIVEN("Process::Clear - Ignore Command") {
        std::vector<std::string> args;
        args.push_back("arg1");
        
        Process process("command", args);
        process.clear(false);

        CHECK(process.getCommand() == "command");
        CHECK(process.numArguments() == 0);
    }
}

TEST_CASE( "Process::setCommand/getCommand - Empty String", "[classic]") {
    GIVEN("Process::setCommand/getCommand - Empty String") {
        Process process("command");
        process.setCommand("");

        CHECK(process.getCommand() == "");
    }
}

TEST_CASE( "Process::setCommand/getCommand - Non-Empty String", "[classic]") {
    GIVEN("Process::setCommand/getCommand - Non-Empty String") {
        Process process("command");
        process.setCommand("testCommand");

        CHECK(process.getCommand() == "testCommand");
    }
}

TEST_CASE( "Process::addArgument - Zero Start", "[classic]") {
    GIVEN("Process::addArgument - Zero Start") {
        Process process("command");
        process.addArgument("arg");

        CHECK(process.numArguments() == 1 );
        CHECK(process.getArgument(0) == "arg");
    }
}

TEST_CASE( "Process::addArgument - One Start", "[classic]") {
    GIVEN("Process::addArgument - One Start") {
        std::vector<std::string> args;
        args.push_back("arg");

        Process process("command", args);
        process.addArgument("testArg");

        CHECK(process.numArguments() == 2 );
        CHECK(process.getArgument(1) == "testArg");
    }
}

TEST_CASE( "Process::addArgument - Two Start", "[classic]") {
    GIVEN("Process::addArgument - Two Start") {
        std::vector<std::string> args;
        args.push_back("arg");
        args.push_back("arg1");

        Process process("command", args);
        process.addArgument("testArg");

        CHECK(process.numArguments() == 3 );
        CHECK(process.getArgument(2) == "testArg");
    }
}

TEST_CASE( "Process::getArguments - Zero Start", "[classic]") {
    GIVEN("Process::getArguments - Zero Start") {
        Process process("command");
        std::vector<std::string> args = process.getArguments();
        CHECK(args.size() == 0);
    }
}

TEST_CASE( "Process::getArguments - One Start", "[classic]") {
    GIVEN("Process::getArguments - One Start") {
        std::vector<std::string> args;
        args.push_back("arg");

        Process process("command", args);
        args = process.getArguments();
        CHECK(args.size() == 1);
    }
}

TEST_CASE( "Process::getArguments - Two Start", "[classic]") {
    GIVEN("Process::getArguments - Two Start") {
        std::vector<std::string> args;
        args.push_back("arg");
        args.push_back("arg1");

        Process process("command", args);
        args = process.getArguments();
        CHECK(args.size() == 2);
    }
}

TEST_CASE( "Process::getArgument - Two Start - Get Zero", "[classic]") {
    GIVEN("Process::getArgument - Two Start - Get Zero") {
        std::vector<std::string> args;
        args.push_back("arg");
        args.push_back("arg1");

        Process process("command", args);
        CHECK(process.getArgument(0) == "arg");
    }
}

TEST_CASE( "Process::getArgument - Three Start - Get Middle", "[classic]") {
    GIVEN("Process::getArgument - Three Start - Get Middle") {
        std::vector<std::string> args;
        args.push_back("arg");
        args.push_back("arg1");
        args.push_back("arg2");

        Process process("command", args);
        CHECK(process.getArgument(1) == "arg1");
    }
}

TEST_CASE( "Process::getArgument - Three Start - Get Last", "[classic]") {
    GIVEN("Process::getArgument - Three Start - Get Last") {
        std::vector<std::string> args;
        args.push_back("arg");
        args.push_back("arg1");
        args.push_back("arg2");

        Process process("command", args);
        CHECK(process.getArgument(2) == "arg2");
    }
}

TEST_CASE( "Process::getArgument - Three Start - Cause Exception", "[classic]") {
    GIVEN("Process::getArgument - Three Start - Cause Exception") {
        std::vector<std::string> args;
        args.push_back("arg");
        args.push_back("arg1");
        args.push_back("arg2");

        Process process("command", args);
        REQUIRE_THROWS_AS(process.getArgument(4), std::out_of_range);
    }
}

TEST_CASE( "Process::Cast to String - Two Args", "[classic]") {
    GIVEN("Process::Cast to String - Two Args") {
        std::vector<std::string> args;
        args.push_back("arg");
        args.push_back("arg1");
        
        std::string checkString = "Command: command\nArguments\n0: arg\n1: arg1\n";
        Process process("command", args);

        CHECK( ((std::string)process) == checkString );
    }
}

TEST_CASE( "Process::Cast to String - No Args", "[classic]") {
    GIVEN("Process::Cast to String - No Args") {
        std::string checkString = "Command: command\nArguments\n";
        Process process("command");

        CHECK( ((std::string)process) == checkString );
    }
}

TEST_CASE( "Process::operator[] - Two Start - Get Zero", "[classic]") {
    GIVEN("Process::operator[] - Two Start - Get Zero") {
        std::vector<std::string> args;
        args.push_back("arg");
        args.push_back("arg1");

        Process process("command", args);
        CHECK(process[0] == "arg");
    }
}

TEST_CASE( "Process::operator[] - Three Start - Get Middle", "[classic]") {
    GIVEN("Process::operator[] - Three Start - Get Middle") {
        std::vector<std::string> args;
        args.push_back("arg");
        args.push_back("arg1");
        args.push_back("arg2");

        Process process("command", args);
        CHECK(process[1] == "arg1");
    }
}

TEST_CASE( "Process::operator[] - Three Start - Get Last", "[classic]") {
    GIVEN("Process::operator[] - Three Start - Get Last") {
        std::vector<std::string> args;
        args.push_back("arg");
        args.push_back("arg1");
        args.push_back("arg2");

        Process process("command", args);
        CHECK(process[2] == "arg2");
    }
}

TEST_CASE( "Process::operator[] - Three Start - Cause Exception", "[classic]") {
    GIVEN("Process::operator[] - Three Start - Cause Exception") {
        std::vector<std::string> args;
        args.push_back("arg");
        args.push_back("arg1");
        args.push_back("arg2");

        Process process("command", args);
        REQUIRE_THROWS_AS(process[4], std::out_of_range);
    }
}

TEST_CASE( "Process::operator<< - Two Args", "[classic]") {
    GIVEN("Process::operator<< - Two Args") {
        std::vector<std::string> args;
        args.push_back("arg");
        args.push_back("arg1");
        
        std::string checkString = "Command: command\nArguments\n0: arg\n1: arg1\n";
        Process process("command", args);

        std::stringstream out;
        out << process;

        CHECK( (out.str()) == checkString );
    }
}

TEST_CASE( "Process::operator<< - No Args", "[classic]") {
    GIVEN("Process::operator<< - No Args") {
        std::string checkString = "Command: command\nArguments\n";
        Process process("command");

        std::stringstream out;
        out << process;

        CHECK( (out.str()) == checkString );
    }
}