#ifndef __LEVEL_H__
#define __LEVEL_H__

#include <string>
#include <mutex>
#include "systems/PositionSystem.hpp"
#include "systems/GraphicsSystem.hpp"
#include "util/VM.hpp"
#include "util/ds/List.hpp"

namespace wj
{
    struct EntData
    {
        uint64_t def_id;
        double x, y, rotation;
        uint8_t layer;
    };

    class Level
    {
    public:

        Level();
        ~Level();

        // Loads a define file into the engine
        void load_define(std::string def_filepath);

        // can simply run another level without calling stop
        void run(std::string level_filepath);

        // saves a level out to the file used to load level
        void save();

        // Use when quitting the application
        void stop();

        // exits application
        void exit();

    private:

        void load_level();
        std::string _level_filename;
        List<EntData> _ent_data;

        // frees all systems
        void free_systems();

        // initialize the virtual machine with all the systems
        void init_vm();

        // Game states
        bool _running, _paused;

        // Systems
        PositionSystem *_position_sys;
        GraphicsSystem *_graphics_sys;

        // Virtual Machine
        VM _vm;

        // Locks
        std::mutex _save_lock, _level_lock;
    };
};

#endif /* end of include guard: __LEVEL_H__ */
