#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <deque>
#include <cassert>

// internals made from std::deque... will change soon

namespace wj
{
    template <typename T>
    class Queue
    {
    public:

        Queue() {}
        ~Queue() { _queue.clear(); }

        void push(T data)
        {
            _queue.push_back(data);
        }

        T pop()
        {
            assert(!is_empty());
            T val = _queue.front();
            _queue.pop_front();
            return val;
        }

        bool is_empty() { return (_queue.size() == 0) ? true : false; }

    private:

        std::deque<T> _queue;

    };
};

#endif /* end of include guard: __QUEUE_H__ */
