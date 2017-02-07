#ifndef __STACK_H__
#define __STACK_H__

#include <string>
#include <cstdint>

namespace wj
{
    class Stack
    {
    public:

        Stack();
        ~Stack();

        void push_int(uint64_t num);
        void push_flt(double num);
        void push_str(const std::string str);

        uint64_t pop_int();
        double pop_flt();
        std::string pop_str();

    private:

        void *_head, *_tail;
    };
};

#endif /* end of include guard: __STACK_H__ */
