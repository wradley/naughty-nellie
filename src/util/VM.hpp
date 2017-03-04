#ifndef __VM_H__
#define __VM_H__

#include "Stack.hpp"
#include <string>
#include "../systems/PositionSystem.hpp"
#include "../systems/GraphicsSystem.hpp"

namespace wj
{
    class VM
    {
    public:

        VM();
        ~VM();

        inline void init(PositionSystem *p) {_position_sys = p;}
        inline void init(GraphicsSystem *g) {_graphics_sys = g;}

        bool run(const char *file);
        bool run(const std::string &file);

    private:

        Stack _stack;

        // Systems
        PositionSystem *_position_sys;
        GraphicsSystem *_graphics_sys;

    };
};

/* List of all commands

Normal commands
0) push int (int64_t)
1) push float (double)
2) push string

Position System commands
100) define an entity (expects [bool no_clip, ..., flt b, flt a, int num_verts, int ent_def_id] in this order)
                        - needs a polygon so you must give the number of verts
                        - pos_sys.define_ent(uint64_t ent_def_id, Poly collider);

*/

#endif /* end of include guard: __VM_H__ */
