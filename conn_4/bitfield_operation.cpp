#include "def.hpp"
#include "bitfield_operation.hpp"

bool is_four_in_a_row(bit_field bf) {
    {
        bit_field tmp = bf & (bf >> 1) & RIGHT_SHIFT_MASK; // 2連続横並びの検出
        tmp &= (tmp >> 1) & RIGHT_SHIFT_MASK; // 3連続横並びの検出
        tmp &= (tmp >> 1) & RIGHT_SHIFT_MASK; // 4連続横並びの検出

        if (tmp) {
            return true;
        }
    }

    {
        bit_field tmp = bf & (bf >> 7) & BIT_FIELD_MASK; // 2連続縦並びの検出
        tmp &= (tmp >> 7) & BIT_FIELD_MASK; // 3連続縦並びの検出
        tmp &= (tmp >> 7) & BIT_FIELD_MASK; // 4連続縦並びの検出

        if (tmp) {
            return true;
        }
    }

    {
        bit_field tmp = bf & (bf >> 8) & RIGHT_SHIFT_MASK; // 2連続\並びの検出
        tmp &= (tmp >> 8) & RIGHT_SHIFT_MASK; // 3連続\並びの検出
        tmp &= (tmp >> 8) & RIGHT_SHIFT_MASK; // 4連続\並びの検出

        if (tmp) {
            return true;
        }
    }

    {
        bit_field tmp = bf & (bf >> 6) & LEFT_SHIFT_MASK; // 2連続/並びの検出
        tmp &= (tmp >> 6) & LEFT_SHIFT_MASK; // 3連続/並びの検出
        tmp &= (tmp >> 6) & LEFT_SHIFT_MASK; // 4連続/並びの検出

        if (tmp) {
            return true;
        }
    }


    return false;
}

bit_field right_perturbation(bit_field bf) {
    return bf |= ((bf >> 1) & RIGHT_SHIFT_MASK);
}

bit_field left_perturbation(bit_field bf) {
    return bf |= ((bf << 1) & LEFT_SHIFT_MASK);
}

bit_field upward_perturbation(bit_field bf) {
    return bf |= ((bf << 7) & BIT_FIELD_MASK);
}

bit_field downward_perturbation(bit_field bf) {
    return bf |= ((bf >> 7) & BIT_FIELD_MASK);
}

bit_field right_up_perturbation(bit_field bf) {
    return bf |= ((bf << 6) & RIGHT_SHIFT_MASK);
}

bit_field right_down_perturbation(bit_field bf) {
    return bf |= ((bf >> 8) & RIGHT_SHIFT_MASK);
}

bit_field left_up_perturbation(bit_field bf) {
    return bf |= ((bf << 8) & LEFT_SHIFT_MASK);
}

bit_field left_down_perturbation(bit_field bf) {
    return bf |= ((bf >> 6) & LEFT_SHIFT_MASK);
}

// TODO: そのようなハードウェア命令が用意されていそうならそれに置き換える

/// @brief 引数に与えられたビットフィールド内に1が何個立っているかを数える.
/// @param value ビットフィールド
/// @return 1の個数
int count_ones(bit_field value) {
    int count = 0;
    value &= BIT_FIELD_MASK;

    while (value) {
        value &= (value - 1); // 最下位の1ビットをクリア
        count++;
    }

    return count;
}

int two_in_a_row_count(bit_field bf) {
    int score = 0;

    {
        score += count_ones(bf & ((bf >> 1) & RIGHT_SHIFT_MASK));
    }
    {
        score += count_ones(bf & ((bf >> 7) & BIT_FIELD_MASK));
    }
    {
        // \ 方向
        score += count_ones(bf & ((bf >> 8) & RIGHT_SHIFT_MASK) & RIGHT_TOP_AND_LEFT_BOTTOM_MASK);
    }
    {
        // /方向
        score += count_ones(bf & ((bf >> 6) & LEFT_SHIFT_MASK) & LEFT_TOP_RIGHT_BOTTOM_MASK);
    }

    return score;
}

int three_in_a_row_count(bit_field bf) {
    int score = 0;

    {
        bit_field tmp = bf & ((bf >> 1) & RIGHT_SHIFT_MASK);
        score += count_ones(tmp & ((tmp >> 1) & RIGHT_SHIFT_MASK));
    }
    {
        bit_field tmp = bf & ((bf >> 7) & BIT_FIELD_MASK);
        score += count_ones(tmp & ((tmp >> 7) & BIT_FIELD_MASK));
    }
    {
        bit_field tmp = bf & ((bf >> 8) & RIGHT_SHIFT_MASK);
        // \ 方向
        score += count_ones(tmp & ((tmp >> 8) & RIGHT_SHIFT_MASK) & RIGHT_TOP_AND_LEFT_BOTTOM_MASK);
    }
    {
        bit_field tmp = bf & ((bf >> 6) & LEFT_SHIFT_MASK);
        // /方向
        score += count_ones(tmp & ((tmp >> 6) & LEFT_SHIFT_MASK) & LEFT_TOP_RIGHT_BOTTOM_MASK);
    }

    return score;
}

int four_in_a_row_count(bit_field bf) {
    int score = 0;

    {
        bit_field tmp = bf & ((bf >> 1) & RIGHT_SHIFT_MASK);
        tmp &= ((tmp >> 1) & RIGHT_SHIFT_MASK);
        score += count_ones(tmp & ((tmp >> 1) & RIGHT_SHIFT_MASK));
    }
    {
        bit_field tmp = bf & ((bf >> 7) & BIT_FIELD_MASK);
        tmp &= ((tmp >> 7) & BIT_FIELD_MASK);
        score += count_ones(tmp & ((tmp >> 7) & BIT_FIELD_MASK));
    }
    {
        bit_field tmp = bf & ((bf >> 8) & RIGHT_SHIFT_MASK);
        // \ 方向
        tmp &= ((tmp >> 8) & RIGHT_SHIFT_MASK);
        score += count_ones(tmp & ((tmp >> 8) & RIGHT_SHIFT_MASK) & RIGHT_TOP_AND_LEFT_BOTTOM_MASK);
    }
    {
        bit_field tmp = bf & ((bf >> 6) & LEFT_SHIFT_MASK);
        tmp &= ((tmp >> 6) & LEFT_SHIFT_MASK);
        // /方向
        score += count_ones(tmp & ((tmp >> 6) & LEFT_SHIFT_MASK) & LEFT_TOP_RIGHT_BOTTOM_MASK);
    }

    return score;
}