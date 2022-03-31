#ifndef GAME_SERVER_HPP
#define GAME_SERVER_HPP

#include <string>
#include <vector>
#include "../shared/Socket.hpp"

class GameServer
{
public:
    GameServer(int port);

    void Run();

    inline void AddWord(const std::string &word)
    {
        words_.push_back(word);
    }

    inline void SetLivesCount(int lives)
    {
        lives_count_ = lives;
    }

private:
    void ClientHandler(Socket socket);

private:
    Socket serv_sock_;
    std::vector<std::string> words_;
    int lives_count_;
};

#endif
