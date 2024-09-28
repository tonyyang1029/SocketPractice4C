//
// Created by Tony Yang on 2024/9/23.
//

#include <string.h>
#include <printf.h>
#include <stdbool.h>
#include "socket.h"

int main(void) {
    int server_socket = server_create();
    if (server_socket < 0) {
        return -1;
    }

    int client_socket = server_listen(server_socket);
    if (client_socket < 0) {
        return -1;
    }

    char *str = "Greeting from server!\n";
    socket_write(client_socket, str, strlen(str));

    char data[1000] = {0};
    socket_read(client_socket, data, sizeof(data) - 1);
    printf("[Client]: %s \n", data);

    while (true)
    {
        char data[1000] = {0};
        socket_read(client_socket, data, sizeof(data) - 1);
        printf("[Client]: %s \n", data);
        if (strcmp(data, "Bye-Bye") == 0) break;

        str = "Good boy\n";
        socket_write(client_socket, str, strlen(str));
    }

    //socket_destroy(client_socket);
    socket_destroy(server_socket);
}