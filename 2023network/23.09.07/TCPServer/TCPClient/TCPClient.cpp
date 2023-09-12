//﻿#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <thread>
#include <string>

using namespace std;

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "8081"
#define IP_ADDRESS "localhost"

struct client_type {
    SOCKET socket;
    int id;
    char received_msg[DEFAULT_BUFLEN];
};

//스레드가 서버로부터 메세지를 받는 함수
//recv만 함
int process_client(client_type& new_client) {
    while (1) {
        memset(new_client.received_msg, 0, DEFAULT_BUFLEN);
        if (new_client.socket != 0) {
            int iResult = recv(new_client.socket, new_client.received_msg,
                DEFAULT_BUFLEN, 0);
            if (iResult != SOCKET_ERROR) {
                cout << new_client.received_msg << endl;
            }
            else {
                cout << "recv() failed: " << WSAGetLastError() << endl;
                break;
            }
        }
    }//end while
    //서버 에러
    if (WSAGetLastError() == WSAECONNRESET) {
        cout << "The server has disconnected" << endl;
    }
    return 0;
}

int __cdecl main(int argc, char** argv)
{
    WSADATA wsaData;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    string sent_msg = "";
    client_type client = { INVALID_SOCKET, -1, "" };
    int iResult;
    string msg = "";

    cout << "Starting Client..." << endl;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    cout << "Connecting..." << endl;

    // Resolve the server address and port
    iResult = getaddrinfo(static_cast<LPCSTR>(IP_ADDRESS), DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

        // Create a SOCKET for connecting to server
        client.socket = socket(ptr->ai_family, ptr->ai_socktype,
            ptr->ai_protocol);
        if (client.socket == INVALID_SOCKET) {
            printf("socket failed with error: %ld\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        // 서버에 연결 요청
        iResult = connect(client.socket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(client.socket);
            client.socket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    //연결되지 못 하고 오류 발생
    if (client.socket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    //연결 성공
    cout << "Successfully Connected" << endl;

    //서버로부터 메세지를 받음
    //1. id를 받은 경우 (서버에 자리가 있다)
    //2. Server is full 받은 경우 (서버에 자리가 없다)
    recv(client.socket, client.received_msg, DEFAULT_BUFLEN, 0);
    msg = client.received_msg;
    if (msg != "Server is Full") {
        client.id = atoi(client.received_msg);
        //서버에서의 데이터 수신은 스레드한테 시킴
        thread my_thread = thread(process_client, ref(client));

        //채팅
        while (1) {
            getline(cin, sent_msg);
            iResult = send(client.socket, sent_msg.c_str(),
                strlen(sent_msg.c_str()), 0);

            if (iResult <= 0) {
                cout << "send() failed: " << WSAGetLastError() << endl;
                break;
            }
        }
        my_thread.detach();
    }//if
    else {
        cout << client.received_msg << endl;
        // shutdown the connection since no more data will be sent
        iResult = shutdown(client.socket, SD_SEND);
        if (iResult == SOCKET_ERROR) {
            printf("shutdown failed with error: %d\n", WSAGetLastError());
            closesocket(client.socket);
            WSACleanup();
            return 1;
        }
    }

    // cleanup
    closesocket(client.socket);
    WSACleanup();
    system("pause");
    return 0;
}