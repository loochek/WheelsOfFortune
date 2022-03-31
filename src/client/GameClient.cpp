#include <iostream>
#include <cassert>
#include "GameClient.hpp"

void GameClient::Run(std::string server_addr, int port)
{
    std::cout << "Trying to connect..." << std::endl;
    sock_.Connect(server_addr, port);

    ServerMessage response = {0};
    ClientMessage request  = {0};

    bool game_finished = false;
    while (!game_finished)
    {
        // Receive server response
        size_t bytes_read = sock_.Read(static_cast<void*>(&response), sizeof(ServerMessage));
        assert(bytes_read == sizeof(ServerMessage));

        // Interact with user
        game_finished = UserInteract(response, request);
        if (game_finished)
            break;

        // Send client request
        size_t bytes_written = sock_.Write(static_cast<void*>(&request), sizeof(ClientMessage));
        assert(bytes_written == sizeof(ClientMessage));
    };
}

bool GameClient::UserInteract(ServerMessage &response, ClientMessage &request)
{
    bool game_finished = false;

    switch (response.status)
    {
    case RESP_START:
        std::cout << "Let's play!" << std::endl;
        break;

    case RESP_ALREADY_OPENED:
        std::cout << "This letter was already opened!" << std::endl;
        break;

    case RESP_NOT_PRESENT:
        std::cout << "You are wrong! Social credit--" << std::endl;
        break;

    case RESP_VICTORY:
        std::cout << "You win! :)" << std::endl;
        game_finished = true;
        break;

    case RESP_DEFEAT:
        std::cout << "No social credit left. Game over :(" << std::endl;
        game_finished = true;
        break;
    }

    std::cout << "Word: " << response.player_word << std::endl;
    std::cout << response.lives_left << " social credit left" << std::endl;

    std::cout << "Enter letter: ";
    std::cin >> request.letter;

    return game_finished;
}
