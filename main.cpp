#include "src/util/VM.hpp"
#include "src/systems/PositionSystem.hpp"
#include "src/util/ds/List.hpp"
#include "src/util/ds/Queue.hpp"
using namespace wj;

struct Test
{
    Test(int n = 0) { num = n; }
    int num;
    std::string to_string()
    {
        return std::to_string(num);
    }
};

int main(int argc, char const *argv[])
{
    PositionSystem position_sys;

    VM vm(position_sys);
    if (vm.run("game/defines/test.define"))
    {
        printf("File ran\n");
    } else {
        printf("File not ran\n");
    }

    position_sys.instantiate_ent(0, 0, {1,1}, 0, 2);
    position_sys.instantiate_ent(1, 1, {0,0}, 0, 2);
    position_sys.instantiate_ent(2, 1, {0,0}, 0, 2);
    position_sys.instantiate_ent(3, 1, {0,0}, 0, 2);

    printf("\nDEFINE:\n%s\n", position_sys.debug_define_to_string().c_str());
    printf("\nINSTAN:\n%s\n", position_sys.debug_instance_to_string().c_str());

    position_sys.mod_ent_pos(0, {1000, 1000});
    position_sys.update();

    printf("\nINSTAN:\n%s\n", position_sys.debug_instance_to_string().c_str());

    return 0;
}
