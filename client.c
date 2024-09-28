//
// Created by Tony Yang on 2024/9/23.
//

#include <printf.h>
#include <string.h>
#include "socket.h"

int main(void)
{
    int client_socket = client_create();
    if (client_socket < 0)
    {
        return -1;
    }

    char data[64] = {0};
    socket_read(client_socket, data, sizeof(data) - 1);
    printf("Client received message from server: %s \n", data);

    const char *str = "Greeting from client!\n";
    socket_write(client_socket, str, strlen(str));

    socket_destroy(client_socket);
}