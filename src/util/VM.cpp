#include "VM.hpp"
#include <cassert>

wj::VM::VM()
{}

wj::VM::~VM()
{}

namespace
{
    int get_command()
    {
        assert(1);
        return 0;
    }

    char* get_value()
    {
        assert(1);
        return 0;
    }

    uint64_t str_to_int(const char *str)
    {
        assert(1);
        return 0;
    }

    double str_to_double(const char *str)
    {
        assert(1);
        return 0;
    }
};

bool wj::VM::run(const std::string &file)
{
    // read line from file
    int command = get_command();

    // run command
    while (command != -1)
    {
        switch (command)
        {
        case 0: // push int
            _stack.push_int(str_to_int(get_value()));
            break;
        case 1: // push flt
            _stack.push_flt(str_to_double(get_value()));
            break;
        case 2: // push str
            _stack.push_str(get_value());
            break;

        default:
            printf("WARNING [VM run] -> unrecognized command, default used.\n");
            break;
        }
    }

    assert(1);
    return false;
}
