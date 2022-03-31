#include <cassert>
#include <cstring>
#include "GameState.hpp"

static constexpr int  ALPHABET_SIZE      = 26;
static constexpr char CLOSED_LETTER_MARK = '*';

GameState::GameState(std::string word, int lives) :
    intl_state_ (InternalState::NotStarted),
    word_       (word),
    player_word_(word.length(), CLOSED_LETTER_MARK),
    letters_    (ALPHABET_SIZE),
    lives_left_ (lives)
{
    assert(0 < word_.length() && word_.length() <= MAX_WORD_SIZE);
    assert(lives >= 0);
}

void GameState::Start(ServerMessage &response)
{
    assert(intl_state_ == InternalState::NotStarted);
    FillResponse(response, RESP_START);
    intl_state_ = InternalState::InProgress;
}

bool GameState::Step(ClientMessage &request, ServerMessage &response)
{
    assert(intl_state_ == InternalState::InProgress);
    assert('a' <= request.letter && request.letter <= 'z');

    if (letters_[request.letter - 'a'])
    {
        FillResponse(response, RESP_ALREADY_OPENED);
        return false;
    }

    if (word_.find(request.letter) == std::string::npos)
    {
        lives_left_--;
        if (lives_left_ < 0)
        {
            FillResponse(response, RESP_DEFEAT);
            intl_state_ = InternalState::Finished;
            return true;
        }
        else
        {
            FillResponse(response, RESP_NOT_PRESENT);
            return false;
        }
    }
    
    letters_[request.letter - 'a'] = true;
    for (int idx = 0; idx < word_.length(); idx++)
    {
        if (word_[idx] == request.letter)
            player_word_[idx] = request.letter;
    }

    if (word_ == player_word_)
    {
        FillResponse(response, RESP_VICTORY);
        intl_state_ = InternalState::Finished;
        return true;   
    }
    else
    {
        FillResponse(response, RESP_OPENED);
        return false;
    }
}

void GameState::FillResponse(ServerMessage &response, GameStatus status)
{
    response.status = status;
    response.lives_left = lives_left_;
    strncpy(response.player_word, player_word_.c_str(), MAX_WORD_SIZE);
}
