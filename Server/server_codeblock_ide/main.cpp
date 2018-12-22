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

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

//Prototype Functions
void sendToAllClients(std::string msg, SOCKET clientArray[]);
void sendAll(SOCKET s, std::string msg);
std::string receiveAll(SOCKET s);

char recvbuf[DEFAULT_BUFLEN];
int recvbuflen = DEFAULT_BUFLEN;
char sendbuf[DEFAULT_BUFLEN];

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

    // Order of players
    char* charVar1 = "1";
    char* charVar2 = "2";
    sendAll(ClientSocket1, charVar1);
    sendAll(ClientSocket2, charVar2);

    // Player 1 chooses a character
    printf("Server: Now to player 1\n");
    std::string player1Msg = "Please choose your character:";
    std::string player2Msg = "Player 1 is choosing their character.";
    sendAll(ClientSocket1, player1Msg);
    sendAll(ClientSocket2, player2Msg);

    receiveAll(ClientSocket1);

    msg = "Player 1 has chosen " + (std::string)recvbuf;
    sendToAllClients(msg, allClients);

    // Player 2 chooses a character
    printf("Server: Now to player 2\n");
    player2Msg = "Please choose your character now: ";
    player1Msg = "Player 2 is now choosing their character.";
    sendAll(ClientSocket1, player1Msg);
    sendAll(ClientSocket2, player2Msg);

    receiveAll(ClientSocket2);
    msg = "Player 2 has chosen " + (std::string)recvbuf;
    sendToAllClients(msg,  allClients);

    // Player Names
    std::string player1Name;
    std::string player2Name;

    player1Name = receiveAll(ClientSocket1);
    player2Name = receiveAll(ClientSocket2);

    std::string nameArray[2] = {player1Name, player2Name};

    // Combat and Game Logic runs in the following loop until a winner is determined.
    int turnCounter = 1;
    std::string turnString;
    int damage;
    std::string opponent;
    while(gameRuns) {
        // Turn #
        turnString = std::to_string(turnCounter);
        sendToAllClients(turnString, allClients);

        // Health Status
        msg = receiveAll(ClientSocket1);
        sendToAllClients("Player 1 has " + msg + " health left.", allClients);
        msg = receiveAll(ClientSocket2);
        sendToAllClients("Player 2 has " + msg + " health left.", allClients);

        // Action Status - Both players
        for(int i = 0; i < 2; i++) {
            damage = 0; // reset damage.
            if(i == 0) {
                opponent = player2Name;
            } else if (i == 1) {
                opponent = player1Name;
            }
            msg = receiveAll(allClients[i]);
            if(msg == "stunned") {
                sendToAllClients( nameArray[i] + std::to_string(i+1) + " is currently stunned.", allClients);
            } else if(msg == "attack") {
                msg = receiveAll(allClients[i]);
                msg = msg + opponent;
                damage = std::stoi(receiveAll(allClients[i]));
                if(i+1 == 1) {
                    sendAll(allClients[1], std::to_string(damage));
                } else if(i+1 == 2) {
                    sendAll(allClients[0], std::to_string(damage));
                }
            } else if(msg == "defense") {

            }
            sendToAllClients(msg, allClients);
        }
        turnCounter += 1;
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

// Send all information to all connected Sockets
void sendToAllClients(std::string msg, SOCKET clientArray[]) {
    memset(sendbuf, 0, DEFAULT_BUFLEN);
    int tempIResult;
    for(int i=0; i<2; i++) {
        tempIResult = send(clientArray[i], msg.c_str(), strlen(msg.c_str()), 0);
        if(tempIResult == SOCKET_ERROR) {
            std::cout << "send failed with error " << WSAGetLastError() << std::endl;
            closesocket(clientArray[i]);
            WSACleanup();
        }
    }
}

// Send all information to a Socket
void sendAll(SOCKET s, std::string msg) {
    memset(sendbuf, 0, DEFAULT_BUFLEN);
    int tempIResult = send(s, msg.c_str(), strlen(msg.c_str()), 0);
    if (tempIResult <= 0) {
        std::cout << "Send failed" << std::endl;
    }
}

// Receive all information from a Socket
std::string receiveAll(SOCKET s) {
    memset(recvbuf, 0, DEFAULT_BUFLEN);
    std::string message;
    int tempIResult = recv(s, recvbuf, recvbuflen, 0);
    if (tempIResult != 0) {
        message = recvbuf;
        message = message.c_str();
        return message;
    }
}
