#include "src/util/VM.hpp"
#include "src/systems/PositionSystem.hpp"
using namespace wj;


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

    return 0;
}
