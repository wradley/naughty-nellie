#include "src/Level.hpp"
using namespace wj;

int main(int argc, char const *argv[])
{
    Level l;
    l.load_define("game/defines/test.define");
    l.run("game/levels/Level_1");
    l.stop();
    printf("Got here\n");

    return 0;
}
