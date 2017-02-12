#include "VM.hpp"
#include <cassert>
#include <fstream>

wj::VM::VM()
{}

wj::VM::~VM()
{}

namespace
{
    int get_command(const std::string &line)
    {
        // numbers can be at most 4 digits
        int i = 1;

        while (true)
        {
            if (line[i] == ' ' || line[i] == '\0') break;
            ++i;

            // make sure something less than 4 digits was found
            if (i > 3)
            {
                printf("VM get_command - command was larger than 4 digits\n");
                assert(0);
            }
        }

        return std::stoi(line.substr(0, i));
    }

    std::string get_value(const std::string &line)
    {
        // look for space
        int i = 0;
        for (auto c : line)
        {
            if (c == ' ') break;
            ++i;
        }
        return line.substr(i+1);
    }
};


bool wj::VM::run(const char *file)
{
    std::string f(file);
    return run(f);
}


bool wj::VM::run(const std::string &file)
{
    int command;
    std::ifstream fin(file);
    if (!fin.is_open()) return false;

    // read file line by line
    std::string line;
    while (std::getline(fin, line))
    {
        // get the command
        printf("%s\n", line.c_str());
        command = get_command(line);
        printf("command: %i\n", command);

        // process the command
        std::string str1;
        double dbl1;
        int64_t int1;
        switch (command)
        {
        case 0: // push int
            _stack.push_int(std::stoll(get_value(line)));
            break;
        case 1: // push flt
            _stack.push_flt(std::stod(get_value(line)));
            break;
        case 2: // push str
            _stack.push_str(get_value(line).c_str());
            break;
        case 3: // temp for testing
            str1 = _stack.pop_str();
            dbl1 = _stack.pop_flt();
            int1 = _stack.pop_int();
            printf("[%s] [%f] [%lli]\n", str1.c_str(), dbl1, int1);
            break;

        default:
            printf("WARNING [VM run] -> unrecognized command, default used.\n");
            break;
        }
    }

    return true;
}
