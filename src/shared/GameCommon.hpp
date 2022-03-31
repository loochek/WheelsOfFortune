#ifndef GAME_COMMON_HPP
#define GAME_COMMON_HPP

static constexpr int MAX_WORD_SIZE = 50;

enum GameStatus
{
    RESP_START,
    RESP_OPENED,
    RESP_NOT_PRESENT,
    RESP_ALREADY_OPENED,
    RESP_VICTORY,
    RESP_DEFEAT
};

#endif
