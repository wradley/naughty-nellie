#ifndef __STACK_H__
#define __STACK_H__

#include <string>
#include <cstdint>

namespace wj
{
    enum DataType
    {
        INT = 0, FLT, STR
    };

    class Stack
    {
    public:

        Stack();
        Stack(const Stack &) = delete;
        ~Stack();

        void        push_int(int64_t num);
        void        push_flt(double num);
        void        push_str(const char *str);

        int64_t     pop_int();
        double      pop_flt();
        std::string pop_str();

        std::string debug_to_string();

    private:

        void *_head, *_tail;
        void *_max_size_ptr;
        uint64_t _max_size;

        // space left between tail and max size
        // - if negative number is returned then a resize is needed
        int space_left();

        // doubles the max size of the array;
        void resize();

        // Pushes a type on the stack to be used for debug info
        void push_type(DataType type);

    };
};

#endif /* end of include guard: __STACK_H__ */
