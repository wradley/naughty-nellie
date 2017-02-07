#include "VM.hpp"


wj::VM::VM()
{}

wj::VM::~VM()
{}

bool wj::VM::run(const std::string &file)
{
    // read line from file

    // run command
    switch (command)
    {
    case 0: // push int
        
        break;

    default:
        printf("WARNING [VM run] -> unrecognized command, default used.\n");
        break;
    }
}
