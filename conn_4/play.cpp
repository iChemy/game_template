#include <iostream>
#include <string>

#include "def.hpp"
#include "evaluator.hpp"
#include "play.hpp"
#include "stream.hpp"
#include "game_tree.hpp"

void play::turn_change() {
    current_player = OPPOSITE_PLAYER(current_player);
}

int play::wait_input() {
    std::string input;
    char col;

    std::cin >> input;
    col = (char)std::atoi(input.c_str());

    return col;
}

play::play() {
    f = field();
    current_player = player::RED;
}

void play::start() {
    std::cout << "current field" << std::endl;

    f.display();

    while (1)
    {
        std::cout << "player " << current_player << " turn" << std::endl;

        char col;
        std::cout << "select columns from 0 ~ 6" << std::endl;

        while (1)
        {
            col = wait_input();

            if (f.is_pilable(col)) {
                break;
            }
        }

        f.pile(col, current_player);

        f.display();

        evaluator e(f);
        int score = e.evaluate(current_player);
        std::cout << "score for " << current_player << ": " << score << std::endl;

        score = e.evaluate(OPPOSITE_PLAYER(current_player));
        std::cout << "score for " << OPPOSITE_PLAYER(current_player) << ": " << score << std::endl;

        if (f.is_win(current_player)) {
            std::cout << current_player << "win" << std::endl;

            break;
        }

        turn_change();
    }
}

ai_play::ai_play(int d): play(), depth(d)
{}

bool ai_play::is_ai_turn() {
    return current_player == player::BLUE;
}

void ai_play::start() {
    std::cout << "current field" << std::endl;

    f.display();
    while (1)
    {
        char col;

        if (is_ai_turn()) {
            std::cout << "AI(" << current_player << ") turn" << std::endl;

            // node n = node(player::BLUE, current_player, f, depth);

            random_node n = random_node(player::BLUE, current_player, f, depth);

            node_res_t res = n.depth_first();

            col = res.col;

            std::cout << "AI choose " << (int)col << std::endl;
        } else {
            std::cout << "player " << current_player << " turn" << std::endl;

            std::cout << "select columns from 0 ~ 6" << std::endl;
            while (1)
            {
                col = wait_input();

                if (f.is_pilable(col)) {
                    break;
                }
            }
        }

        f.pile(col, current_player);

        f.display();

        evaluator e(f);
        int score = e.evaluate(current_player);

        std::cout << "score for " << current_player << ": " << score << std::endl;

        if (f.is_win(current_player)) {
            std::cout << current_player << " win" << std::endl;

            break;
        }

        turn_change();
    }
}