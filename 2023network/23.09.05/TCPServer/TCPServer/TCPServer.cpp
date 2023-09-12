#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <thread>
#include <vector>
#include <iostream>
#include <string>


// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "8081"

struct client_type {
    int id;
    SOCKET socket;
};

const int MAX_CLIENTS = 5;

int process_client(client_type& new_client, std::vector<client_type>& client_array, std::thread& thread)
{
    std::string msg = "";
    char tempmsg[DEFAULT_BUFLEN] = "";

    while (true) {
        memset(tempmsg, 0, DEFAULT_BUFLEN);
        if (new_client.socket != 0) {
            int iResult = recv(new_client.socket, tempmsg, DEFAULT_BUFLEN, 0);

            if (iResult != SOCKET_ERROR) {
                if (strcmp("", tempmsg)) {
                    msg = "Client # " + std::to_string(new_client.id) + ": " + tempmsg;
                    std::cout << msg << '\n';

                    for (int i = 0; i < MAX_CLIENTS; i++)
                    {
                        if (client_array[i].socket != INVALID_SOCKET) {
                            if (new_client.id != i) {
                                iResult = send(client_array[i].socket, msg.c_str(), strlen(msg.c_str()), 0);
                            }
                        }
                    }
                }
            }
            else
            {
                msg = "Client #" + std::to_string(new_client.id) + " Disconnected";
                std::cout << msg << '\n';

                closesocket(new_client.socket);
                client_array[new_client.id].socket = INVALID_SOCKET;

                for (int i = 0; i < MAX_CLIENTS; i++)
                {
                    if (client_array[i].socket != INVALID_SOCKET)
                    {
                        iResult = send(client_array[i].socket, msg.c_str(), strlen(msg.c_str()), 0);
                    }
                }

                break;
            }
        }
    }

    thread.detach();
    return 0;
}

int __cdecl main(void)
{
    // ���� �ʱ�ȭ -> ���� ���� -> ��Ʈ��ũ ��� -> ���� �ݱ� -> ���� ����

    WSADATA wsaData; // ���� ������ ����ü
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET; // Ŭ���̾�Ʈ�� �޾Ƶ��̱� ���� ����
    //SOCKET ClientSocket = INVALID_SOCKET; // Ŭ���̾�Ʈ�� ����ϴ� ����

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    //int iSendResult;
    //char recvbuf[DEFAULT_BUFLEN];
    //int recvbuflen = DEFAULT_BUFLEN;

    std::string msg = "";
    std::vector<client_type> client(MAX_CLIENTS);
    int num_clients = 0;
    int temp_id = -1;
    std::thread my_thread[MAX_CLIENTS];


    // Initialize Winsock
    // ���� �ʱ�ȭ

    std::cout << "Initializing Winsock...\n";
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP(��Ʈ������) UDP(�����ͱ׷� ����)
    hints.ai_protocol = IPPROTO_TCP; // TCP ���
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    std::cout << "Setting up Server...\n";
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    setsockopt(ListenSocket, SOL_SOCKET, SO_REUSEADDR, "1", sizeof(int));
    setsockopt(ListenSocket, IPPROTO_TCP, TCP_NODELAY, "1", sizeof(int));

    // Create a SOCKET for the server to listen for client connections.
    // Ŭ���̾�Ʈ�� ������ �� �ֵ��� ������ ���� ����
    std::cout << "Creating Server Socket...\n";
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    // �� ���� ���μ��� �� ���� ��Ʈ ����
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    // ���ε� �� Ŭ���̾�Ʈ ��û �����ϰ� ������
    std::cout << "Listening...\n";
    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    for (int i = 0; i < MAX_CLIENTS; ++i)
    {
        client[i] = { -1, INVALID_SOCKET };
    }

    while (true) {
        SOCKET incoming = INVALID_SOCKET;
        incoming = accept(ListenSocket, NULL, NULL);
        if (incoming == INVALID_SOCKET) continue;

        num_clients = -1;

        for (int i = 0; i < MAX_CLIENTS; ++i)
        {
            if (client[i].socket == INVALID_SOCKET && temp_id == -1)
            {
                client[i].socket = incoming;
                client[i].id = i;
                temp_id = i;
            }
            if (client[i].socket != INVALID_SOCKET) {
                num_clients++;
            }
        }

        if (temp_id != -1) {
            std::cout << "Client #" << client[temp_id].id << " Accepted\n";
            msg = std::to_string(client[temp_id].id);
            send(client[temp_id].socket, msg.c_str(), strlen(msg.c_str()), 0);
            my_thread[temp_id] = std::thread(process_client, std::ref(client[temp_id]), std::ref(client), std::ref(my_thread[temp_id]));
        }
        else {
            msg = "Server is Full";
            send(incoming, msg.c_str(), strlen(msg.c_str()), 0);
            std::cout << msg << '\n';
        }
    }

    closesocket(ListenSocket);

    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        my_thread[i].detach();
        closesocket(client[i].socket);
    }

    WSACleanup();

    return 0;
}