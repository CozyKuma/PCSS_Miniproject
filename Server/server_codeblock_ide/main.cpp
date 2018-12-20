#undef UNICODE

#define _WIN32_WINNT 0x501

#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 1024
#define DEFAULT_PORT "27015"

//Prototype Functions
void sendToAllClients(std::string message, SOCKET clientArray[]);

int __cdecl main(void)
{
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket1 = INVALID_SOCKET;
    SOCKET ClientSocket2 = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    struct addrinfo hints;

    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;

    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    // Resolve the server address and port
    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
    if (iResult != 0)
    {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    //creating socket for connecting to server
    // Create a SOCKET for connecting to server
    ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (ListenSocket == INVALID_SOCKET)
    {
        printf("socket failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    //TCP listening socket
    iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
    if (iResult == SOCKET_ERROR)
    {
        printf("bind error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }
    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR)
    {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    // Accept a client socket
    if(ClientSocket1 == INVALID_SOCKET)
    {
        ClientSocket1 = accept(ListenSocket, NULL, NULL);
        printf("Client 1 has connected.\n");
        if (ClientSocket1 == INVALID_SOCKET)
        {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }
    }

    if(ClientSocket1 != INVALID_SOCKET && ClientSocket2 == INVALID_SOCKET)
    {
        ClientSocket2 = accept(ListenSocket, NULL, NULL);
        printf("Client 2 has connected.\n");
        if (ClientSocket2 == INVALID_SOCKET)
        {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            return 1;
        }
    }

    // No longer need server socket
    closesocket(ListenSocket);

    // Array for clients
    SOCKET allClients[2] = {ClientSocket1, ClientSocket2};

    bool gameRuns = true;

    // Welcome Message and character selection for both clients
    std::string msg = "Welcome to the fight!";
    sendToAllClients(msg, allClients);
    std::cout << msg << std::endl;
    recv(ClientSocket1, recvbuf, sizeof(recvbuf), 0);
    std::cout << recvbuf << std::endl;
    recv(ClientSocket2, recvbuf, sizeof(recvbuf), 0);
    std::cout << recvbuf << std::endl;
    char* charVar1 = (char*)1;
    char* charVar2 = (char*)2;
    std::cout << charVar1 << std::endl;
    std::cout << charVar2 << std::endl;
    send(ClientSocket1, charVar1, sizeof(charVar1), 0);
    send(ClientSocket2, charVar2, sizeof(charVar2), 0);
    std::string player1Msg = "Please choose your character: ";
    std::string player2Msg = "Player 1 is choosing their character.";
    send(ClientSocket1, player1Msg.c_str(), strlen(player1Msg.c_str()), 0);
    send(ClientSocket2, player2Msg.c_str(), strlen(player2Msg.c_str()), 0);
    recv(ClientSocket1, recvbuf, recvbuflen, 0);
    msg = "Player 1 has chosen " + (std::string)recvbuf;
    sendToAllClients(msg, allClients);
    player2Msg = "Please choose your character now: ";
    player2Msg = "Player 2 is now choosing their character.";
    recv(ClientSocket2, recvbuf, recvbuflen, 0);
    msg = "Player 2 has chosen " + (std::string)recvbuf;
    sendToAllClients(msg,  allClients);
    while(gameRuns) {

    }

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket1, SD_SEND);
    if (iResult == SOCKET_ERROR)
    {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket1);
        WSACleanup();
        return 1;
    }

    iResult = shutdown(ClientSocket2, SD_SEND);
    if (iResult == SOCKET_ERROR)
    {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket2);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ClientSocket1);
    closesocket(ClientSocket2);
    WSACleanup();

    return 0;
}

void sendToAllClients(std::string message, SOCKET clientArray[]) {
    int myISendResult;
    char myInput[1024];
    strcpy(myInput, message.c_str());
    for(int i=0; i<2; i++) {
        myISendResult = send(clientArray[i], myInput, (int)sizeof(myInput), 0);
        if(myISendResult == SOCKET_ERROR) {
            std::cout << "send failed with error " << WSAGetLastError() << std::endl;
            closesocket(clientArray[i]);
            WSACleanup();
        }
    }
}
