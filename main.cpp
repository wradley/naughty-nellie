#include "src/util/VM.hpp"
using namespace wj;


int main(int argc, char const *argv[])
{
    VM vm;
    if (vm.run("game/defines/test.define"))
    {
        printf("File ran\n");
    } else {
        printf("File not ran\n");
    }

    return 0;
}
