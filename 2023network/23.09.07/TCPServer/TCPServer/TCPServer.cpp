//﻿#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "8081"

struct client_type {//클라이언트 정보 저장 구조체
    int id;
    SOCKET socket;
};

const int MAX_CLIENTS = 5;

int process_client(client_type& new_client, vector<client_type>& client_arry, thread& thread);
int main();

//스레드에게 시킬 일
//클라이언트 처리(recv, send)
int process_client(client_type& new_client, vector<client_type>& client_arry, thread& thread) {
    string msg = ""; //보낼 메세지
    char tempmsg[DEFAULT_BUFLEN] = "";//받는 버퍼

    while (1) {
        memset(tempmsg, 0, DEFAULT_BUFLEN);
        if (new_client.socket != 0) {
            int iResult = recv(new_client.socket, tempmsg, DEFAULT_BUFLEN, 0);
            if (iResult != SOCKET_ERROR) {
                if (strcmp("", tempmsg)) {
                    msg = "Client #" + to_string(new_client.id) + ": " + tempmsg;
                    cout << msg.c_str() << endl;

                    //브로드캐스트. 클라이언트가 보낸 메세지를 다른 클라한테 뿌림
                    for (int i = 0; i < MAX_CLIENTS; i++)
                    {   //접속이 되어있는 클라이언트 소켓
                        if (client_arry[i].socket != INVALID_SOCKET) {
                            if (new_client.id != i) { //메세지 보낸 클라이언트 제외
                                iResult = send(client_arry[i].socket, msg.c_str(), strlen(msg.c_str()), 0);
                            }
                        }
                    }
                }
            }
            else { //SOCKET_ERROR 해당 클라이언트 접속 끝. 
                msg = "Client #" + to_string(new_client.id) + " Disconnected";
                cout << msg << endl;

                //접속 끊기면 해당소켓 닫기
                closesocket(new_client.socket);
                client_arry[new_client.id].socket = INVALID_SOCKET;

                for (int i = 0; i < MAX_CLIENTS; i++)
                {   //접속이 되어있는 클라이언트 소켓
                    if (client_arry[i].socket != INVALID_SOCKET) {
                        iResult = send(client_arry[i].socket, msg.c_str(), strlen(msg.c_str()), 0);
                    }
                }
                break;
            }
        }
    } //end while

    thread.detach(); //할 일 다한 스레드 죽이기
    return 0;
}

int __cdecl main(void)
{
    WSADATA wsaData; //윈속 구조체
    int iResult;

    SOCKET ServerSocket = INVALID_SOCKET; //리스닝을 위한 소켓
    //SOCKET ClientSocket = INVALID_SOCKET; //클라이언트 데이터 주고 받는 소켓

    struct addrinfo* result = NULL;
    struct addrinfo hints;

    string msg = "";
    vector<client_type>client(MAX_CLIENTS);
    int num_clients = 0; //접속 중인 클라이언트 수
    int temp_id = -1;
    thread my_thread[MAX_CLIENTS]; //1클라 1스레드

    // Initialize Winsock
    // 윈속 초기화
    cout << "Initializing Winsock..." << endl;
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET; //IPv4
    hints.ai_socktype = SOCK_STREAM; //TCP(스트림) UDP(데이터그램)
    hints.ai_protocol = IPPROTO_TCP; //TCP 프로토콜
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    cout << "Setting up server..." << endl;
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0) {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Create a SOCKET for the server to listen for client connections.
    // 소켓 생성
    cout << "Creating Socket Server..." << endl;
    ServerSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ServerSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    //소켓 옵션 지정
    //비정상적인 종료로 아직 bind 정보를 유지하고 있을 때 오류 방지
    setsockopt(ServerSocket, SOL_SOCKET, SO_REUSEADDR, "1", sizeof(int));
    //불필요한 빈번한 전송(ACK 등)을 줄여서 좀 더 빠른 TCP 전송 세팅
    setsockopt(ServerSocket, IPPROTO_TCP, TCP_NODELAY, "1", sizeof(int));

    // Setup the TCP listening socket
    // 소켓에 주소 지정
    cout << "Binding Socket..." << endl;
    iResult = bind(ServerSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ServerSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    // 리스닝 소켓에 클라이언트가 연결 요청 가능하게 listen
    cout << "Listening..." << endl;
    iResult = listen(ServerSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ServerSocket);
        WSACleanup();
        return 1;
    }

    //클라이언트 구조체 초기화
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        client[i] = { -1, INVALID_SOCKET };
    }

    while (1) {
        SOCKET incoming = INVALID_SOCKET;
        incoming = accept(ServerSocket, NULL, NULL);
        if (incoming == INVALID_SOCKET) continue;

        num_clients = -1;
        temp_id = -1;

        //서버 빈 자리 찾기
        for (int i = 0; i < MAX_CLIENTS; i++)
        {   //빈자리가 있으면 소켓 받아주기
            if (client[i].socket == INVALID_SOCKET && temp_id == -1) {
                client[i].socket = incoming;
                client[i].id = i;
                temp_id = i;
            }
            if (client[i].socket != INVALID_SOCKET) {
                num_clients++;
            }
        }
        //서버에 잘 접속 되었으면
        if (temp_id != -1) {
            //아이디 번호와 함께 연결 허가 알림
            cout << "Client #" << client[temp_id].id << " Accepted" << endl;
            //클라이언트한테 처음 보내는 메세지(아이디)
            msg = to_string(client[temp_id].id);
            send(client[temp_id].socket, msg.c_str(), strlen(msg.c_str()), 0);
            //스레드에게 클라 넘기기
            my_thread[temp_id] = thread(process_client, ref(client[temp_id]),
                ref(client), ref(my_thread[temp_id]));
        }
        else {//자리가 없어요
            msg = "Server is Full";
            send(incoming, msg.c_str(), strlen(msg.c_str()), 0);
            cout << msg << endl;
        }
    }//end while

    closesocket(ServerSocket);
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        my_thread[i].detach();
        closesocket(client[i].socket);
    }
    WSACleanup();
    cout << "Program has ended." << endl;

    system("pause");
    return 0;
}