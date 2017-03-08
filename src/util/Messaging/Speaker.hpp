#ifndef __SPEAKER_H__
#define __SPEAKER_H__

#include <mutex>
#include <deque>
#include <map>
#include <vector>
#include "MessagingEnums.hpp"
#include "Listener.hpp"

namespace wj
{
    struct BroadcastRequest;

    class Speaker
    {
    public: // public functions

        Speaker();
        ~Speaker();

        void subscribe(Channel c, Listener *l);

        void broadcast(
            Channel c,
            Message m,
            const void *data = 0,
            std::size_t data_size = 0);

        // Starts/ends Messaging system
        void run();
        void exit();

    private: // private state

        std::map<Channel, std::vector<Listener*>> _channels;
        std::deque<BroadcastRequest*> _requests;
        std::mutex _request_lock, _channel_lock;
        bool _running;

    private: // deleted functions

        Speaker(const Speaker &) = delete;
        void operator= (const Speaker &) = delete;
    };



    struct BroadcastRequest
    {
        Channel channel;
        Message message;
        void *data;
    };
};

#endif /* end of include guard: __SPEAKER_H__ */
