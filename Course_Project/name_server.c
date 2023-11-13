#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define MAX_STRGSERVERS 100


char *NM_ip = "127.0.0.1";

int count = 0;

int server_socket[MAX_STRGSERVERS];
struct sockaddr_in server_addr[MAX_STRGSERVERS];
struct sockaddr_in client_addr[MAX_STRGSERVERS];
socklen_t client_addr_len[MAX_STRGSERVERS];
int client_socket[MAX_STRGSERVERS];

int main()
{

    char *server_ip = NM_ip;
    while (1)
    {
        int server_port = 5000 + count;

        // Create a socket
        server_socket[count] = socket(AF_INET, SOCK_STREAM, 0);
        if (server_socket[count] == -1)
        {
            perror("Socket creation failed");
            exit(EXIT_FAILURE);
        }

        // Bind the socket to the server address
        
        server_addr[count].sin_family = AF_INET;
        server_addr[count].sin_addr.s_addr = inet_addr(server_ip);
        server_addr[count].sin_port = htons(server_port);

        int opt = 1;
        setsockopt(server_socket[count], SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
        if (bind(server_socket[count], (struct sockaddr *)&server_addr[count], sizeof(server_addr[count])) == -1)
        {
            perror("Binding failed");
            close(server_socket[count]);
            exit(EXIT_FAILURE);
        }

        // Listen for incoming connections
        if (listen(server_socket[count], 5) == -1)
        {
            perror("Listening failed");
            close(server_socket[count]);
            exit(EXIT_FAILURE);
        }

        printf("TCP server is listening on %s:%d\n", server_ip, server_port);

        // Accept incoming connections
        
        client_addr_len[count] = sizeof(client_addr[count]);
        client_socket[count] = accept(server_socket[count], (struct sockaddr *)&client_addr[count], &client_addr_len[count]);

        if (client_socket[count] == -1)
        {
            perror("Accepting connection failed");
            close(server_socket[count]);
            exit(EXIT_FAILURE);
        }

        printf("Accepted connection from %s:%d\n", inet_ntoa(client_addr[count].sin_addr), ntohs(client_addr[count].sin_port));

        // accepting clients
        count++;
    }

}
