#include <thread>
#include <iostream>
#include <cassert>
#include "GameServer.hpp"
#include "GameState.hpp"

GameServer::GameServer(int port) : lives_count_(DEFAULT_LIVES_COUNT)
{
    serv_sock_.Bind(port);
    serv_sock_.Listen();

    std::cout << "Server is listening on port " << port << std::endl;
}

void GameServer::Run()
{
    while (true)
    {
        Socket client_sock = serv_sock_.Accept();
        std::thread client_handler_thread(&GameServer::ClientHandler, this, std::move(client_sock));
        client_handler_thread.detach();
    }
}

void GameServer::ClientHandler(Socket socket)
{
    try
    {
        std::cout << "New client connected" << std::endl;

        ServerMessage response = {0};
        ClientMessage request  = {0};
        GameState state(words_[rand() % words_.size()], lives_count_);
        
        state.Start(response);

        bool game_finished = false;
        while (!game_finished)
        {
            // Send server response
            size_t bytes_written = socket.Write(static_cast<void*>(&response), sizeof(ServerMessage));
            assert(bytes_written == sizeof(ServerMessage));

            // Receive client request
            size_t bytes_read = socket.Read(static_cast<void*>(&request), sizeof(ClientMessage));
            assert(bytes_read == sizeof(ClientMessage));

            // Make step in the game logic
            game_finished = state.Step(request, response);
        }

        // Send server final response
        size_t bytes_written = socket.Write(static_cast<void*>(&response), sizeof(ServerMessage));
        assert(bytes_written == sizeof(ServerMessage));
    }
    catch (const std::exception &e)
    {
        std::cout << "Exception occured in the handler thread: " << e.what() << std::endl;
    }
}
