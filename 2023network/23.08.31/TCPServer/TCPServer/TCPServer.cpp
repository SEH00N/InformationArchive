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
    SOCKET ClientSocket = INVALID_SOCKET; // Ŭ���̾�Ʈ�� ����ϴ� ����

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    // ���� �ʱ�ȭ
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
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections.
    // Ŭ���̾�Ʈ�� ������ �� �ֵ��� ������ ���� ����
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
    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    // ��û Ŭ���̾�Ʈ �㰡. �̶� Ŭ���̾�Ʈ ���ϰ� ���� ��
    ClientSocket = accept(ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET) {
        printf("accept failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // No longer need server socket
    closesocket(ListenSocket);

    // Receive until the peer shuts down the connection
    do {
        // Ŭ���̾�Ʈ�κ��� �����͸� �޾ƿ´�
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        printf("%d", iResult);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);

            // Echo the buffer back to the sender
            // Ŭ���̾�Ʈ���� ������ ������
            iSendResult = send(ClientSocket, recvbuf, iResult, 0);
            if (iSendResult == SOCKET_ERROR) {
                printf("send failed with error: %d\n", WSAGetLastError());
                closesocket(ClientSocket);
                WSACleanup();
                return 1;
            }
            printf("Bytes sent: %d\n", iSendResult);
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            WSACleanup();
            return 1;
        }

    } while (iResult > 0);

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    // ���� �ݱ�
    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}