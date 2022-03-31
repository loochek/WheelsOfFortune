#ifndef GAME_CLIENT_HPP
#define GAME_CLIENT_HPP

#include <string>
#include "../shared/Socket.hpp"
#include "../shared/NetworkMessages.hpp"

class GameClient
{
public:
    void Run(std::string server_addr, int port);

private:
    bool UserInteract(ServerMessage &response, ClientMessage &request);

private:
    Socket sock_;
};

#endif
