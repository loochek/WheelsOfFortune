#ifndef NETWORK_MESSAGES_HPP
#define NETWORK_MESSAGES_HPP

#include <cstdint>
#include "GameCommon.hpp"

struct ClientMessage
{
    char letter;
} __attribute__((packed));

struct ServerMessage
{
    uint8_t  status;
    uint8_t  lives_left;
    char     player_word[MAX_WORD_SIZE + 1];
} __attribute__((packed));

#endif
