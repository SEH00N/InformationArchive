#undef UNICODE
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include <thread>

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

int process_client(client_type& new_client) {
    while (1) {
        memset(new_client.received_msg, 0, DEFAULT_BUFLEN);
        if (new_client.socket != 0) {
            int result = recv(new_client.socket, new_client.received_msg, DEFAULT_BUFLEN, 0);

            if (result != SOCKET_ERROR) {
                std::cout << new_client.received_msg << '\n';
            } else {
                std::cout << "recv() failed : " << WSAGetLastError() << '\n';
                break;
            }

        }
    }

	if (WSAGetLastError() == WSAECONNRESET) {
		std::cout << "The server has disconnected";
	}

    return 0;
}

int __cdecl main(int argc, char** argv)
{
    WSADATA wsaData;
    struct addrinfo* result = NULL,
        * ptr = NULL,
        hints;
    
    std::string sent_msg = "";
    client_type client = { INVALID_SOCKET, -1, "" };
    int iResult = 0;
    std::string msg;

    std::cout << "Starting Client...\n";

    // Validate the parameters
    if (argc != 2) {
        printf("usage: %s server-name\n", argv[0]);
        return 1;
    }

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

    // Resolve the server address and port
    iResult = getaddrinfo(static_cast<PCSTR>(IP_ADDRESS), DEFAULT_PORT, &hints, &result);
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
        iResult = connect(client.socket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(client.socket);
            client.socket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (client.socket == INVALID_SOCKET) {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }
    
    std::cout << "Successfully Connected\n";

    recv(client.socket, client.received_msg, DEFAULT_BUFLEN, 0);
    msg = client.received_msg;

    if (msg != "Server is full")
    {
        client.id = atoi(client.received_msg);
        std::thread my_thread = std::thread(process_client, std::ref(client));

        while (true) {
            std::getline(std::cin, sent_msg);
            iResult = send(client.socket, sent_msg.c_str(), strlen(sent_msg.c_str()), 0);

            if (iResult <= 0) {
                std::cout << "send() failed : " << WSAGetLastError() << '\n';
                break;
            }
        }

        my_thread.detach();
    }
    else
    {
        std::cout << client.received_msg << '\n';
        std::cout << "Shutting down socket...\n";
        iResult = shutdown(client.socket, SD_SEND);
        if (iResult == SOCKET_ERROR)
        {
            std::cout << "shutdown() failed with error : " << WSAGetLastError() << '\n';
            closesocket(client.socket);
            WSACleanup();
            system("pause");
            return 1;
        }
    }

    while (true) {

    }

    // cleanup
    closesocket(client.socket);
    WSACleanup();

    return 0;
}