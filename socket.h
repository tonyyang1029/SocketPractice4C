//
// Created by Tony Yang on 2024/9/23.
//

#ifndef SOCKETPRACTICE_SOCKET_H
#define SOCKETPRACTICE_SOCKET_H

#define SOCKET_ADDR     "127.0.0.1"
#define SOCKET_PORT     1234

int server_create(void);
int server_listen(int);
int client_create(void);
ssize_t socket_write(int, const char *, unsigned int);
ssize_t socket_read(int, char*, unsigned int);
void socket_destroy(int );

#endif //SOCKETPRACTICE_SOCKET_H
