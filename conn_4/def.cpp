#include <iostream>
#include "def.hpp"
#include "bitfield_operation.hpp"

field::field() {
    for (char i = 0; i < FIELD_COL_NUMBER; i++) {
        pile_counter[(unsigned char)i] = 0;
    }

    red = 0ULL; blue = 0ULL;
}

field_state field::get_state(char row, char col) const {
    char linear_idx = FIELD_COL_NUMBER * row + col;

    if (red & (0b1ULL << (63 - linear_idx))) {
        return field_state::RED;
    } else if (blue & (0b1ULL << (63 - linear_idx))) {
        return field_state::BLUE;
    } else {
        return field_state::EMPTY;
    }
}

int field::pile(char col, player p) {
    if (col >= FIELD_COL_NUMBER || col < 0) {
        return -1;
    }
    char row = pile_counter[(unsigned char)col];

    if (row >= FIELD_ROW_NUMBER) {
        return -1;
    }

    pile_counter[(unsigned char)col] += 1;

    char linear_idx = FIELD_COL_NUMBER * row + col;
    unsigned long long mask = 0b01ULL << (63 - linear_idx);

    if (p == player::RED) {
        red |= mask;
    } else {
        blue |= mask;
    }

    return 0;
}

void field::display() const {
    for (int i = 0; i < FIELD_COL_NUMBER; i++) {
        std::cout << "| " << i << " ";
    }
    std::cout << "|\n";

    for (char i = FIELD_ROW_NUMBER - 1; i >= 0; i--) {
        for (char j = 0; j < FIELD_COL_NUMBER; j++) {
            field_state s = get_state(i, j);
            switch (s)
            {
            case field_state::RED:
                std::cout << "| o ";
                break;
            case field_state::BLUE:
                std::cout << "| x ";
                break;
            default:
                std::cout << "|   ";
                break;
            }
        }
        std::cout << "|\n";
    }
}

bool field::is_win(player p) const {
    if (p == player::RED) {
        return is_four_in_a_row(red);
    } else {
        return is_four_in_a_row(blue);
    }
}

playing_state field::is_game_set() const {
    if (is_four_in_a_row(red)) {
        return playing_state::RED_WIN;
    } else if (is_four_in_a_row(blue)) {
        return playing_state::BLUE_WIN;
    } else {
        return playing_state::UNSET;
    }
}

bit_field field::get_bit_field(player p) const {
    if (p == player::RED) {
        return red;
    } else {
        return blue;
    }
}

bool field::is_pilable(char col) const {
    if (col >= FIELD_COL_NUMBER || col < 0) {
        return false;
    }

    if (pile_counter[(unsigned char)col] >= FIELD_ROW_NUMBER) {
        return false;
    }

    return true;
}