#ifndef __PLAY_HPP__
#define __PLAY_HPP__

#include "def.hpp"

class play {
protected:
    field f;
    player current_player;

    void turn_change();
    int wait_input();
public:
    play();
    void start();
};

class ai_play: public play {
private:
    int depth;
    bool is_ai_turn();
public:
    ai_play(int d);
    void start();
};

#endif