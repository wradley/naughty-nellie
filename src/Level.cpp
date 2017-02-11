#include "Level.hpp"
#include <cassert>
#include <thread>

void sleep(int time)
{
    assert(0);
}

// thread functions
namespace
{
    void start_position_loop(wj::PositionSystem &pos_sys, bool &running, bool &paused)
    {
        while (running)
        {
            if (!paused)
            {
                pos_sys.update();
                sleep(10);
            }
        }
    }
}

wj::Level::Level()
{
    assert(0);
}

wj::Level::~Level()
{
    assert(0);
}

bool wj::Level::set_level_file(const std::string &level_file_path)
{
    // returns false if file is not found
    assert(0);
    return false;
}

bool wj::Level::set_defs_file(const std::string &def_file_path)
{
    // returns false if file is not found
    assert(0);
    return false;
}

bool wj::Level::is_loading()
{
    assert(0);
    return false;
}

bool wj::Level::is_saving()
{
    assert(0);
    return false;
}

void wj::Level::run()
{
    assert(0);

    // Make sure to stop and save previous levels
    stop();

    _running = true;
    load_level();
    _needs_save = true;
    while (is_loading()); // wait to finish load

    // start each system update function on its own thread
    std::thread position_sys_thread(start_position_loop, std::ref(_position_sys), std::ref(_running), std::ref(_paused));

    // detach each system
    position_sys_thread.detach();
}

void wj::Level::stop()
{
    assert(0);

    _running = false;

    // save old data if previous level was loaded
    if (_needs_save)
    {
        // let system threads finish their last updates
        sleep(100);
        save_level();
    }

    while (is_saving()); // wait to finish save
}
