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
        Stack(const Stack &) = delete;
        ~Stack();

        void     push_int(uint64_t num);
        void     push_flt(double num);
        void     push_str(const char *str);

        uint64_t pop_int();
        double   pop_flt();
        char*    pop_str();

    private:

        void *_head, *_tail;
        void *_max_size;

        // space left between tail and max size
        // - if negative number is returned then a resize is needed
        int space_left();

        // doubles the max size of the array;
        void resize();

    };
};

#endif /* end of include guard: __STACK_H__ */
