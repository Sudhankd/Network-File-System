#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>


#define MAX_STRGSERVERS 100

struct Storage_Server{
    int Sno;
    char ip[25];
    int port_NS;
    int port_SS;
    // Trie accessible_paths;
};

typedef struct Storage_Server SS;                                                                                       

SS storage_servers[MAX_STRGSERVERS];

// int strg_count;
char *NM_ip = "127.0.0.1";
// int count = 0; // index of which storage server is being connected

typedef struct TrieNode *Trie;

struct TrieNode
{
    struct TrieNode *children[26];
    // int EndofWord;
};

Trie strgs[MAX_STRGSERVERS];

Trie CreateNode()
{
    Trie T = (Trie)malloc(sizeof(struct TrieNode));
    for (int i = 0; i < 26; i++)
    {
        T->children[i] = NULL;
    }
    // T->EndofWord = 0;
    // T->children[letter - 97]->EndofWord = 0;
    return T;
}

void Insert_to_Trie(Trie T, char *str)
{
    Trie temp = T;
    for (int i = 0; i < strlen(str); i++)
    {
        int idx = str[i] - 97;
        if (temp->children[idx] == NULL)
            temp->children[idx] = CreateNode();
        temp = temp->children[idx];
    }
    // temp->EndofWord = 1;
}

int Search(Trie T, char *str)
{
    Trie temp = T;
    for (int i = 0; i < strlen(str); i++)
    {
        int idx = str[i] - 97;
        if (temp->children[idx] != NULL)
            temp = temp->children[idx];
        else
            return 0;
    }
    return 1;
}

// void start_namingserver();

