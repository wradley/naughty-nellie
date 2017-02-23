#ifndef __LIST_H__
#define __LIST_H__

#include <cstdint>
#include <string>

namespace wj
{
    template <typename T>
    class List
    {
    public:
        virtual             ~List() {}
        virtual T&          operator[] (uint64_t index) = 0;
        virtual bool        exists(uint64_t index) = 0;
        virtual void        remove(uint64_t index) = 0;
        virtual void        clear() = 0;
        virtual std::string debug_to_string() = 0;
    };
};

#endif /* end of include guard: __LIST_H__ */
