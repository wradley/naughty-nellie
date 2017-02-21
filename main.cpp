#include "src/util/VM.hpp"
#include "src/systems/PositionSystem.hpp"
#include "src/util/SList.hpp"
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
    // PositionSystem position_sys;
    //
    // VM vm(position_sys);
    // if (vm.run("game/defines/test.define"))
    // {
    //     printf("File ran\n");
    // } else {
    //     printf("File not ran\n");
    // }
    //
    // printf("\n\n%s\n", position_sys.debug_define_to_string().c_str());

    SList<Test> list;
    list[100] = 100;
    list[2] = 2;
    list[89] = 89;
    list[1000] = 1000;
    printf("%s\n", list.debug_to_string().c_str());

    return 0;
}
