#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <string>

/**
 * Simple wrapper around Linux socket
 */
class Socket
{
public:
    Socket();
    ~Socket();

    Socket(const Socket &other) = delete;
    Socket(Socket &&other);

    void Bind(int port);
    void Listen();
    void Connect(std::string addr, int port);

    Socket Accept();

    size_t Read(void *buf, size_t count);
    size_t Write(void *buf, size_t count);

private:
    Socket(int fd);

private:
    int fd_;
    static constexpr int BACKLOG = 64;
};

#endif
