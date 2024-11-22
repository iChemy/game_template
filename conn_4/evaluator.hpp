#ifndef __EVALUATOR_HPP__
#define __EVALUATOR_HPP__

#include "def.hpp"

/// @brief とても大きなスコア. 勝ちを表す
const int VERY_BIG_SCORE = 10000000;

class evaluator
{
private:
    const field &target_field;
public:
    evaluator(const field &f);

    /// @brief 指定されたプレイヤーに対する盤面の評価を返す
    /// @param p プレイヤー
    /// @return 指定したプレイヤーに対する盤面のスコア
    int evaluate(player p) const;
};


#endif