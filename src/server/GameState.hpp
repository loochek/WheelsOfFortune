#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <string>
#include <vector>
#include "../shared/NetworkMessages.hpp"

static constexpr int DEFAULT_LIVES_COUNT = 10;

/**
 * One-use game state
 */
class GameState
{
public:
    /**
     * \param word Game word
     * \param lives Lives count
     */
    GameState(std::string word, int lives = DEFAULT_LIVES_COUNT);
    
    GameState(const GameState &other) = default;

    /**
     * Starts the new game
     */
    void Start(ServerMessage &response);

    /**
     * Updates game state according to client request 
     * and fills server response
     * 
     * \param request Client request
     * \param response Server responce to fill
     * 
     * \return True if game is finished, false otherwise
     */
    bool Step(ClientMessage &request, ServerMessage &response);

private:
    void FillResponse(ServerMessage &response, GameStatus status);

private:
    enum class InternalState
    {
        NotStarted,
        InProgress,
        Finished
    };

    std::string word_;
    std::string player_word_;
    std::vector<bool> letters_;
    int lives_left_;

    InternalState intl_state_;
};

#endif
