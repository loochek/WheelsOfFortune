#include "GameClient.hpp"

int main()
{
    GameClient client;
    client.Run("127.0.0.1", 5555);

    return 0;
}
