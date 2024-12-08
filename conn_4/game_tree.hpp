#ifndef __GAME_TREE_HPP__
#define __GAME_TREE_HPP__

#include "def.hpp"
#include "evaluator.hpp"

struct node_res_t
{
    int score; // target_player にとってのスコア
    char col; // それを実現する列 (root node 以外では需要ない...)
};


class node {
    const player target_player;
    /// @brief 誰が手を打とうとしているか
    const player who_play;

    /// @brief フィールド (親から生成された)
    const field &target_field;

    const int depth;

protected:
    evaluator e;

public:
    node(player p1, player p2, const field &f, int d);
    node_res_t depth_first();
};

class random_node: public node {
public:
    random_node(player p1, player p2, const field &f, int d);   
    node_res_t depth_first(); 
};

#endif