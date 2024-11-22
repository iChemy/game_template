#include <cassert>
#include <iostream>
#include "def.hpp"
#include "bitfield_operation.hpp"
#include "play.hpp"

int main()
{
    ai_play ai = ai_play(5);

    ai.start();

    return 0;
}
