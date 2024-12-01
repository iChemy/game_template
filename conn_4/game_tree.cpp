#include "def.hpp"
#include "evaluator.hpp"
#include "game_tree.hpp"

node::node(player p1, player p2, const field &f, int d):
    target_player(p1), who_play(p2), target_field(f), depth(d)
{}

node_res_t node::depth_first() {
    if (depth == 0) {
        evaluator e(target_field);

        // 手を打った人にとっての価値
        return {.score=e.evaluate(target_player), .col=0};
    } else {
        // who_play の相手が打ったということ
        if (target_field.is_win(OPPOSITE_PLAYER(who_play))) {
            if (who_play == target_player) { // who_playはすでに敗北している
                return {.score = -1 * VERY_BIG_SCORE, .col=0};
            } else {
                return {.score = VERY_BIG_SCORE, .col=0};
            }
        }

        // target == who_play なら より大きいスコアを採用していくので
        int score = (target_player == who_play) ? -1 * VERY_BIG_SCORE - 1 : VERY_BIG_SCORE + 1;
        char col = 0;
        for (char i = 0; i < FIELD_COL_NUMBER; i++) {

            if (target_field.is_pilable(i)) {
                field f = field(target_field);
                f.pile(i, who_play);

                node child = node(target_player, OPPOSITE_PLAYER(who_play), f, depth - 1);

                // who_play がその手を打った場合のスコア
                int child_score = child.depth_first().score;

                
                if (target_player == who_play) {
                    // 自分はより大きいスコアの手を打つので
                    if (child_score > score) {
                        score = child_score;
                        col = i;
                    }
                } else {
                    // who_play が敵なので 自分が最高の手を選ぶ必要がある
                    if (score > child_score) {
                        score = child_score;
                        col = i;
                    }
                }
            }
        }

        return {score, col};
    }
}