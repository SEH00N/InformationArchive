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
    // 윈속 초기화 -> 소켓 생성 -> 네트워크 통신 -> 소켓 닫기 -> 윈속 종료

    WSADATA wsaData; // 윈속 데이터 구조체
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET; // 클라이언트를 받아들이기 위한 소켓
    SOCKET ClientSocket = INVALID_SOCKET; // 클라이언트와 통신하는 소켓

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    // 윈속 초기화
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_STREAM; // TCP(스트림소켓) UDP(데이터그램 소켓)
    hints.ai_protocol = IPPROTO_TCP; // TCP 사용
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections.
    // 클라이언트가 접속할 수 있도록 리스닝 소켓 생성
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    // 수 많은 프로세스 중 서버 포트 지정
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    // 바인드 후 클라이언트 요청 가능하게 리스닝
    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    // 요청 클라이언트 허가. 이때 클라이언트 소켓과 연결 됨
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
        // 클라이언트로부터 데이터를 받아온다
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        printf("%d", iResult);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);

            // Echo the buffer back to the sender
            // 클라이언트한테 데이터 보내기
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
    // 소켓 닫기
    closesocket(ClientSocket);
    WSACleanup();

    return 0;
}