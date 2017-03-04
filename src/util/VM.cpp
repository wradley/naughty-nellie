#include "VM.hpp"
#include <cassert>
#include <fstream>
#include "Poly.hpp"

wj::VM::VM()
{}

wj::VM::~VM()
{}

namespace
{
    int get_command(const std::string &line)
    {
        // comment or empty line
        if (line[0] == '#' || line == "") return -1;

        // numbers can be at most 5 digits
        static const int MAX_DIGITS = 5;
        int i = 1;

        while (true)
        {
            if (line[i] == ' ' || line[i] == '\0') break;
            ++i;

            // make sure something less than MAX_DIGITS digits were found
            if (i >= MAX_DIGITS)
            {
                printf("VM get_command - command was larger than MAX_DIGITS digits\n");
                assert(0);
            }
        }

        return std::stoi(line.substr(0, i));
    }

    std::string get_value(const std::string &line)
    {
        int i, j;

        // look for space / start of value
        for (i = 0; i < line.size(); ++i)
        {
            if (line[i] == ' ') break;
        }

        // look for '#' (comment)
        for (j = 1; j < line.size(); ++j)
        {
            if (line[j] == '#') break;
        }

        return line.substr(i+1, j);
    }

    wj::Poly make_polygon(wj::Stack &s)
    {
        int num_verts = s.pop_int();
        wj::Poly p;
        for (int i = 0; i < num_verts; ++i)
        {
            double a = s.pop_flt();
            double b = s.pop_flt();
            p.add_vert({a, b});
        }
        return p;
    }
};


// simple wrapper for other run
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
        command = get_command(line);

        std::string str1;
        //double dbl1, dbl2, dbl3;
        int64_t int1;//, int2, int3;

        // process the command
        switch (command)
        {
        case -1: // comment or empty line
            break;
        case 0: // push int
            _stack.push_int(std::stoll(get_value(line)));
            break;
        case 1: // push flt
            _stack.push_flt(std::stod(get_value(line)));
            break;
        case 2: // push str
            _stack.push_str(get_value(line).c_str());
            break;

        case 100: // DEFINE position
            int1 = _stack.pop_int(); // define id
            if (_position_sys == nullptr) assert(0);
            _position_sys->define_ent(
                (uint64_t) int1,
                make_polygon(_stack),
                ((_stack.pop_int()==0) ? true : false)
            );
            break;

        default:
            printf("WARNING [VM run] -> unrecognized command, default used.\n");
            break;
        }
    }

    return true;
}
