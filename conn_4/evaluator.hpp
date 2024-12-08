#ifndef __EVALUATOR_HPP__
#define __EVALUATOR_HPP__

#include <random>
#include "def.hpp"

/// @brief とても大きなスコア. 勝ちを表す
const int VERY_BIG_SCORE = 10000000;

class evaluator
{
private:
    const field *target_field;
public:
    evaluator(const field &f);
    evaluator(std::nullptr_t);

    void set_field(const field &f);

    /// @brief 指定されたプレイヤーに対する盤面の評価を返す
    /// @param p プレイヤー
    /// @return 指定したプレイヤーに対する盤面のスコア
    int evaluate(player p) const;
};

class random_evaluator: public evaluator {
private:
    std::random_device rd;
    mutable std::default_random_engine engine;
    mutable std::normal_distribution<double> dist;
    static constexpr double noise_magnitude = 6.0; // ノイズの最大値
public:
    random_evaluator(const field &f);
    random_evaluator(std::nullptr_t);

    void set_field(const field &f);

    /// @brief 指定されたプレイヤーに対する盤面の評価を返す
    /// @param p プレイヤー
    /// @return 指定したプレイヤーに対する盤面のスコア
    int evaluate(player p) const;
};


#endif