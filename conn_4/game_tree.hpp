#ifndef __GAME_TREE_HPP__
#define __GAME_TREE_HPP__

#include "def.hpp"
#include "evaluator.hpp"

class node {
    const player target_player;
    const player who_did;

    /// @brief who_did が最後に手を打って作り出したフィールド
    const field &target_field;

    const int depth;

public:
    node(player p1, player p2, const field &f, int d);
    int depth_first();
};

#endif