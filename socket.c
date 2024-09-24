//
// Created by Tony Yang on 2024/9/23.
//

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "socket.h"

#define LOG_LEVEL_NONE      0
#define LOG_LEVEL_ERROR     1
#define LOG_LEVEL_WARN      2
#define LOG_LEVEL_INFO      3
#define LOG_LEVEL_DBG       4
#define LOG_LEVEL           LOG_LEVEL_DBG

#if (LOG_LEVEL >= LOG_LEVEL_ERROR)
#define SOCKET_LOGE(...)    printf(__VA_ARGS__)
#else
#define SOCKET_LOGE(...)
#endif

#if (LOG_LEVEL >= LOG_LEVEL_WARN)
#define SOCKET_LOGW(...)    printf(__VA_ARGS__)
#else
#define SOCKET_LOGW(...)
#endif

#if (LOG_LEVEL >= LOG_LEVEL_INFO)
#define SOCKET_LOGI(...)    printf(__VA_ARGS__)
#else
#define SOCKET_LOGI(...)
#endif

#if (LOG_LEVEL >= LOG_LEVEL_DBG)
#define SOCKET_LOGD(...)    printf(__VA_ARGS__)
#else
#define SOCKET_LOGD(...)
#endif

int server_create(void)
{
    int server_socket;
    struct sockaddr_in sockAddrIn;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        SOCKET_LOGE("%s-%d: server creation error. socket=%d \n", __func__, __LINE__, server_socket);
        return server_socket;
    }

    sockAddrIn.sin_family = AF_INET;
    sockAddrIn.sin_addr.s_addr = htonl(INADDR_ANY);
    sockAddrIn.sin_port = htons(SOCKET_PORT);
    if (bind(server_socket, (const struct sockaddr *) &sockAddrIn, sizeof(sockAddrIn)) < 0 )
    {
        SOCKET_LOGE("%s-%d: bind error.", __func__, __LINE__);
        return -1;
    }

    return server_socket;
}

int server_listen(int server_socket)
{
    SOCKET_LOGD("%s: start to listen. \n", __func__);
    listen(server_socket, SOMAXCONN);

    SOCKET_LOGD("%s: start to accept. \n", __func__ );
    struct sockaddr_in sockAddIn;
    socklen_t sockAddInSize = sizeof(sockAddIn);
    return accept(server_socket, (struct sockaddr *) &sockAddIn, &sockAddInSize);
}

int client_create(void)
{
    int client_socket;
    struct sockaddr_in sockAddrIn;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0)
    {
        SOCKET_LOGE("%s-%d: client creation error. \n", __func__, __LINE__);
        return client_socket;
    }

    sockAddrIn.sin_family = AF_INET;
    sockAddrIn.sin_addr.s_addr = inet_addr(SOCKET_ADDR);
    sockAddrIn.sin_port = htons(SOCKET_PORT);
    if (connect(client_socket, (const struct sockaddr *) &sockAddrIn, sizeof(sockAddrIn)) < 0)
    {
        SOCKET_LOGE("%s-%d: client connection error. \n", __func__, __LINE__);
        return -1;
    }

    return client_socket;
}

ssize_t socket_write(int socket, const char *data, unsigned int len)
{
    SOCKET_LOGD("%s \n", __func__ );
    return write(socket, data, len);
}

ssize_t socket_read(int socket, char *data, unsigned int len)
{
    SOCKET_LOGD("%s \n", __func__);
    return read(socket, data, len);
}

void socket_destroy(int socket)
{
    SOCKET_LOGD("%s \n", __func__);
    close(socket);
}