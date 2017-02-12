#ifndef __VM_H__
#define __VM_H__

#include "Stack.hpp"
#include <string>

namespace wj
{
    class VM
    {
    public:

        VM();
        ~VM();

        bool run(const char *file);
        bool run(const std::string &file);

    private:

        Stack _stack;

    };
};

#endif /* end of include guard: __VM_H__ */
