#include "Speaker.hpp"
#include <SDL2/SDL.h>

wj::Speaker::Speaker() : _running(false)
{}

wj::Speaker::~Speaker()
{}

void wj::Speaker::subscribe(Channel c, Listener *l)
{
    std::lock_guard<std::mutex> lock(_channel_lock);
    _channels[c].push_back(l);
}

void wj::Speaker::broadcast(
    Channel c, Message m,
    const void *data, std::size_t size)
{
    BroadcastRequest *br = new BroadcastRequest;
    br->channel = c;
    br->message = m;
    memcpy(br->data, data, size);

    std::lock_guard<std::mutex> lock(_request_lock);
    _requests.push_back(br);
}

void wj::Speaker::run()
{
    _running = true;
    while (_running)
    {
        SDL_Delay(10);

        while (_requests.size() > 0)
        {
            BroadcastRequest *r;
            {
                std::lock_guard<std::mutex> lock(_request_lock);
                r = _requests.front();
                _requests.pop_front();
            }

            std::lock_guard<std::mutex> lock(_channel_lock);
            for (auto listener : _channels[r->channel])
            {
                listener->handle_message(r->channel, r->message, r->data);
            }

            delete r;
        }
    }
}

void wj::Speaker::exit()
{
    _running = false;
}
