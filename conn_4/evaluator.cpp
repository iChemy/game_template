#include "def.hpp"
#include "evaluator.hpp"
#include "bitfield_operation.hpp"

int count_ones(bit_field value);

evaluator::evaluator(const field &f): target_field(f) {}

int evaluator::evaluate(player p) const {
    if (target_field.is_win(p)) {
        return VERY_BIG_SCORE;
    } else if (target_field.is_win(OPPOSITE_PLAYER(p))){
        return -1 * VERY_BIG_SCORE;
    }

    int score = 0;

    bit_field me = target_field.get_bit_field(p), op = target_field.get_bit_field(OPPOSITE_PLAYER(p));

    {
        // 上下摂動
        {
            bit_field me_tmp = me & ~(upward_perturbation(op) | downward_perturbation(op)) & BIT_FIELD_MASK;

            score += two_in_a_row_count(me_tmp);

            score += three_in_a_row_count(me_tmp);

            score += four_in_a_row_count(me_tmp);
        }
        // 左右摂動
        {
            bit_field me_tmp = me & ~(right_perturbation(op) | left_perturbation(op)) & BIT_FIELD_MASK;

            score += two_in_a_row_count(me_tmp);

            score += three_in_a_row_count(me_tmp);

            score += four_in_a_row_count(me_tmp);
        }
        // \ 方向摂動
        {
            bit_field me_tmp = me & ~(left_up_perturbation(op) | right_down_perturbation(op)) & BIT_FIELD_MASK;

            score += two_in_a_row_count(me_tmp);

            score += three_in_a_row_count(me_tmp);

            score += four_in_a_row_count(me_tmp);
        }
        // / 方向摂動
        {
            bit_field me_tmp = me & ~(right_up_perturbation(op) | left_down_perturbation(op)) & BIT_FIELD_MASK;

            score += two_in_a_row_count(me_tmp);

            score += three_in_a_row_count(me_tmp);

            score += four_in_a_row_count(me_tmp);
        }
    }

    {
        // 上下摂動
        {
            bit_field op_tmp = op & ~(upward_perturbation(me) | downward_perturbation(me)) & BIT_FIELD_MASK;

            score -= two_in_a_row_count(op_tmp);

            score -= three_in_a_row_count(op_tmp);

            score -= four_in_a_row_count(op_tmp);
        }
        // 左右摂動
        {
            bit_field op_tmp = op & ~(right_perturbation(me) | left_perturbation(me)) & BIT_FIELD_MASK;

            score -= two_in_a_row_count(op_tmp);

            score -= three_in_a_row_count(op_tmp);

            score -= four_in_a_row_count(op_tmp);
        }
        // \ 方向摂動
        {
            bit_field op_tmp = op & ~(left_up_perturbation(me) | right_down_perturbation(me)) & BIT_FIELD_MASK;

            score -= two_in_a_row_count(op_tmp);

            score -= three_in_a_row_count(op_tmp);

            score -= four_in_a_row_count(op_tmp);
        }
        // / 方向摂動
        {
            bit_field op_tmp = op & ~(right_up_perturbation(me) | left_down_perturbation(me)) & BIT_FIELD_MASK;

            score -= two_in_a_row_count(op_tmp);

            score -= three_in_a_row_count(op_tmp);

            score -= four_in_a_row_count(op_tmp);
        }
    }

    return score;
}