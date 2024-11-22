#ifndef __DEF_HPP__
#define __DEF_HPP__

enum class field_state: unsigned char {
    EMPTY = 0b00,
    RED = 0b01,
    BLUE = 0b10
};

enum class player: unsigned char {
    RED = 0b01,
    BLUE = 0b10
};

#define OPPOSITE_PLAYER(p) ((player)((unsigned char)p ^ (unsigned char)0b00000011))

enum class playing_state: unsigned char {
    UNSET = 0b00,
    RED_WIN = 0b01,
    BLUE_WIN = 0b10
};

/// @brief 7 x 6 = 42 bit の フィールド. 下位 14 bit を無視する
using bit_field = unsigned long long;


const char FIELD_ROW_NUMBER = 6;
const char FIELD_COL_NUMBER = 7;

class field {
    char pile_counter[FIELD_COL_NUMBER];
    bit_field red;
    bit_field blue;
public:
    field();
    field_state get_state(char row, char col) const;
    /// @brief 指定された列に, 指定のプレイヤーが石を積む
    /// @param col 
    /// @param p 
    /// @return 失敗したら -1
    int pile(char col, player p);

    void display() const;

    /// @brief 指定したプレイヤーが勝利しているか判定する
    /// @param p プレイヤー
    /// @return 勝利していたら `true`
    bool is_win(player p) const;

    /// @brief 勝敗がついたかどうか判定する
    /// @return 勝敗がついていたら `true`
    playing_state is_game_set() const;

    /// @brief 指定したプレイヤーのビットフィールドを返す
    /// @param p プレイヤー
    /// @return 指定したプレイヤーのビットフィールド
    bit_field get_bit_field(player p) const;

    bool is_pilable(char col) const;
};

#endif