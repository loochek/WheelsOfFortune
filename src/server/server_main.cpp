#include "GameServer.hpp"

int main()
{
    GameServer server(5555);
    
    server.AddWord("amogus");
    server.AddWord("interesting");
    server.AddWord("palindrome");

    server.Run();
    return 0;
}
