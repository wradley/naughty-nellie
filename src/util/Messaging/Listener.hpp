#ifndef __LISTENER_H__
#define __LISTENER_H__

#include "MessagingEnums.hpp"

namespace wj
{
    class Listener
    {
    public:
        virtual ~Listener() {}
        virtual void handle_message(Channel c, Message m, const void *data) = 0;
    };
};

#endif /* end of include guard: __LISTENER_H__ */
