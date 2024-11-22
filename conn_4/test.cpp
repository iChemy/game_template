#include <cassert>
#include <iostream>
#include "def.hpp"
#include "bitfield_operation.hpp"
#include "play.hpp"

void test_field() {
    {
        field f = field();

        for (int i = 0; i < FIELD_ROW_NUMBER; i++) {
            assert(f.is_pilable(0));
            assert(f.pile(0, player::RED) == 0);
        }
        assert(!f.is_pilable(0));

        assert(f.is_win(player::RED));
        assert(!f.is_win(player::BLUE));
        assert(f.is_game_set() == playing_state::RED_WIN);
    }

    {
        field f = field();

        f.pile(0, player::RED);
        f.pile(4, player::BLUE);

        assert(f.get_state(0, 0) == field_state::RED);
        assert(f.get_state(0, 4) == field_state::BLUE);

        assert(f.get_state(0,3) == field_state::EMPTY);
    }
}

int main()
{
    test_field();
    return 0;
}
