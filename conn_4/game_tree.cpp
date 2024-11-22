#include "def.hpp"
#include "evaluator.hpp"
#include "game_tree.hpp"

node::node(player p1, player p2, const field &f, int d):
    target_player(p1), who_did(p2), target_field(f), depth(d)
{}

int node::depth_first() {
    if (depth == 0) {
        evaluator e(target_field);

        // 手を打った人にとっての価値
        return e.evaluate(target_player);
    } else {
        // who_did が勝ちの手を打った
        if (target_field.is_win(who_did)) {
            if (who_did == target_player) {
                return VERY_BIG_SCORE;
            } else {
                return -1 * VERY_BIG_SCORE;
            }
        }

        int score = (target_player != who_did) ? -1 * VERY_BIG_SCORE : VERY_BIG_SCORE;

        for (char i = 0; i < FIELD_COL_NUMBER; i++) {

            if (target_field.is_pilable(i)) {
                field f = field(target_field);
                f.pile(i, OPPOSITE_PLAYER(who_did));

                node child = node(target_player, OPPOSITE_PLAYER(who_did), f, depth - 1);

                int child_score = child.depth_first();

                if (target_player == who_did) {
                    if (score > child_score) {
                        score = child_score;
                    }
                } else {
                    if (score < child_score) {
                        score = child_score;
                    }
                }
            }
        }

        return score;
    }
}