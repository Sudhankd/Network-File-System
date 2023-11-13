#include "headers.h"
// #include "name_server.c"

int connected_count = 0;

int client_socket[MAX_STRGSERVERS];
struct sockaddr_in server_addr[MAX_STRGSERVERS];
int strg_count = 0;


int main()
{
    storage_servers[0].Sno = 0;
    strcpy(storage_servers[0].ip, "192.168.1.101");
    storage_servers[0].port_NS = 5000;
    storage_servers[0].port_SS = 6000;
    strgs[0] = CreateNode();
    Insert_to_Trie(strgs[0], "data");
    strg_count++;

    storage_servers[1].Sno = 1;
    strcpy(storage_servers[1].ip, "192.168.1.102");
    storage_servers[1].port_NS = 5001;
    storage_servers[1].port_SS = 6001;
    strgs[1] = CreateNode();
    Insert_to_Trie(strgs[0], "paths");
    strg_count++;

    // start_namingserver();
    while (1)
    {
        if (connected_count < strg_count)
        {

            char *server_ip = NM_ip;
            int server_port = storage_servers[connected_count].port_NS;

            // Create a socket
            client_socket[connected_count] = socket(AF_INET, SOCK_STREAM, 0);

            if (client_socket[connected_count] == -1)
            {
                // printf("%d ", storage_servers[connected_count].Sno + 1);
                perror("Socket creation failed");
                exit(EXIT_FAILURE);
            }

            // Define server address to connect

            server_addr[connected_count].sin_family = AF_INET;
            server_addr[connected_count].sin_addr.s_addr = inet_addr(server_ip);
            server_addr[connected_count].sin_port = htons(server_port);

            // Connect to the server
            if (connect(client_socket[connected_count], (struct sockaddr *)&server_addr[connected_count], sizeof(server_addr[connected_count])) == -1)
            {
                printf("%d ", storage_servers[connected_count].Sno + 1);
                perror("Connection failed");
                close(client_socket[connected_count]);
                exit(EXIT_FAILURE);
            }

            connected_count++;
            sleep(1);
        }
    }

    return 0;
}