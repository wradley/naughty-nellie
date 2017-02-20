#include "src/util/VM.hpp"
#include "src/systems/PositionSystem.hpp"
#include "src/util/FList.hpp"
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

    printf("\n\n%s\n", position_sys.debug_define_to_string().c_str());

    return 0;
}
