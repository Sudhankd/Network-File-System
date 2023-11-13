#include "headers.h"

int add_storage_server(char *ip, int NS_port, int client_port, int Sno)
{
    storage_servers[Sno].Sno = Sno;
    strcpy(storage_servers[Sno].ip, ip);
    storage_servers[Sno].port_NS = NS_port;
    storage_servers[Sno].port_SS = client_port;

    char *server_ip = "127.0.0.1";
    int server_port = NS_port;

    // Create a socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Define server address to connect
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    server_addr.sin_port = htons(server_port);

    // Connect to the server
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Connection failed");
        close(client_socket);
        exit(EXIT_FAILURE);
    }


}