#include <stdexcept>
#include <string>
#include <cerrno>
#include <cstring>

#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "Socket.hpp"

Socket::Socket()
{
    if ((fd_ = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        throw std::runtime_error("socket() error: " + std::string(strerror(errno)));
}

Socket::Socket(int fd) : fd_(fd) {}

Socket::Socket(Socket &&other) : fd_(other.fd_)
{
    other.fd_ = -1;
}

Socket::~Socket()
{
    close(fd_);
}

void Socket::Bind(int port)
{
    int opt = 1;
    if (setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
        throw std::runtime_error("setsockopt() error: " + std::string(strerror(errno)));
        
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(fd_, (struct sockaddr*)&addr, sizeof(struct sockaddr_in)) < 0)
        throw std::runtime_error("bind() error: " + std::string(strerror(errno)));
}

void Socket::Listen()
{
    if (listen(fd_, BACKLOG) < 0)
        throw std::runtime_error("listen() error: " + std::string(strerror(errno)));
}

Socket Socket::Accept()
{
    struct sockaddr_in client_addr = {0};
    socklen_t socklen = sizeof(struct sockaddr_in);
    int client_fd = accept(fd_, (struct sockaddr*)&client_addr, &socklen);
    if (client_fd < 0)
        throw std::runtime_error("accept() error" + std::string(strerror(errno)));

    return Socket(client_fd);
}

void Socket::Connect(std::string addr, int port)
{
    struct sockaddr_in server_addr = {0};

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    if (inet_pton(AF_INET, addr.c_str(), &server_addr.sin_addr) <= 0)
        throw std::runtime_error("inet_pton() error");

    if (connect(fd_, (struct sockaddr*)&server_addr, sizeof(struct sockaddr_in)) < 0)
        throw std::runtime_error("connect() error" + std::string(strerror(errno)));
}

size_t Socket::Read(void *buf, size_t count)
{
    ssize_t bytes_read = read(fd_, buf, count);
    if (bytes_read < 0)
        throw std::runtime_error("read() error" + std::string(strerror(errno)));

    return bytes_read;
}

size_t Socket::Write(void *buf, size_t count)
{
    ssize_t bytes_written = write(fd_, buf, count);
    if (bytes_written < 0)
        throw std::runtime_error("read() error" + std::string(strerror(errno)));

    return bytes_written;
}
