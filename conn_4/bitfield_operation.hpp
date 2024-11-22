#ifndef __BIT_FIELD_OPERATION__
#define __BIT_FIELD_OPERATION__

#include "def.hpp"

const unsigned long long BIT_FIELD_MASK = ~(((0b1ULL << 22) - 1));

const unsigned long long RIGHT_SHIFT_MASK = ~(
    (0b1ULL << 63) | 
    (0b1ULL << 56) | 
    (0b1ULL << 49) | 
    (0b1ULL << 42) | 
    (0b1ULL << 35) | 
    (0b1ULL << 28) | 
    ((0b1ULL << 22) - 1)
);

const unsigned long long LEFT_SHIFT_MASK = ~(
    (0b1ULL << 57) | 
    (0b1ULL << 50) | 
    (0b1ULL << 43) | 
    (0b1ULL << 36) | 
    (0b1ULL << 29) | 
    (0b1ULL << 22) | 
    ((0b1ULL << 22) - 1)
);


/**
 * 0000111
 * 0000011
 * 0000001
 * 1000000
 * 1100000
 * 1110000
 * 
 */
const unsigned long long RIGHT_TOP_AND_LEFT_BOTTOM_MASK = ~(
    (0b111ULL << 57) |
    (0b11ULL << 50) |
    (0b1ULL << 43) |
    (0b1ULL << 42) |
    (0b11ULL << 48) |
    (0b111ULL << 54) |
    ((0b1ULL << 22) - 1)
);

/**
 * 1110000
 * 1100000
 * 1000000
 * 0000001
 * 0000011
 * 0000111
 * 
 */
const unsigned long long LEFT_TOP_RIGHT_BOTTOM_MASK = ~(
    (0b111ULL << 61) |
    (0b11ULL << 55) |
    (0b1ULL << 49) |
    (0b1ULL << 36) |
    (0b11ULL << 29) |
    (0b111ULL << 22) |
    ((0b1ULL << 22) - 1)
);

bool is_four_in_a_row(bit_field bf);

bit_field right_perturbation(bit_field bf);

bit_field left_perturbation(bit_field bf);

bit_field upward_perturbation(bit_field bf);

bit_field downward_perturbation(bit_field bf);

bit_field right_up_perturbation(bit_field bf);

bit_field right_down_perturbation(bit_field bf);

bit_field left_up_perturbation(bit_field bf);

bit_field left_down_perturbation(bit_field bf);

// TODO: そのようなハードウェア命令が用意されていそうならそれに置き換える

/// @brief 引数に与えられたビットフィールド内に1が何個立っているかを数える.
/// @param value ビットフィールド
/// @return 1の個数
int count_ones(bit_field value);

/// @brief ２連続に並んでいる数を概算する
/// @param bf 
/// @return 
int two_in_a_row_count(bit_field bf);


int three_in_a_row_count(bit_field bf);

int four_in_a_row_count(bit_field bf);

#endif