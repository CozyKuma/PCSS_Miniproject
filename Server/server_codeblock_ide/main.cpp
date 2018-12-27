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

    msg = receiveAll(ClientSocket1);

    msg = "Player 1 has chosen " + msg;
    sendToAllClients(msg, allClients);

    // Player 2 chooses a character
    printf("Server: Now to player 2\n");
    player2Msg = "Please choose your character now: ";
    player1Msg = "Player 2 is now choosing their character.";
    sendAll(ClientSocket1, player1Msg);
    sendAll(ClientSocket2, player2Msg);

    msg = receiveAll(ClientSocket2);

    msg = "Player 2 has chosen " + msg;
    sendToAllClients(msg,  allClients);

    // Player Names
    std::string player1Name;
    std::string player2Name;

    player1Name = receiveAll(ClientSocket1);
    std::cout << "Player 1 is named: " << player1Name << std::endl;

    sendToAllClients("Player 1 is named: " + player1Name, allClients);

    player2Name = receiveAll(ClientSocket2);
    std::cout << "Player 2 is named: " << player2Name << std::endl;

    sendToAllClients("Player 2 is named: " + player2Name, allClients);

    std::string nameArray[2] = {player1Name, player2Name};

    // Combat and Game Logic runs in the following loop until a winner is determined.
    int turnCounter = 1;
    std::string turnString;
    int damage;
    std::string damageString;
    std::string effect;
    std::string opponent;
    int player1Health;
    int player2Health;
    while(gameRuns)
    {
        // Turn #
        turnString = std::to_string(turnCounter);
        sendToAllClients(turnString, allClients);

        // Health Status
        msg = receiveAll(ClientSocket1);
        sendToAllClients( player1Name + " has " + msg + " health left.", allClients);
        msg = receiveAll(ClientSocket2);
        sendToAllClients( player2Name + " has " + msg + " health left.", allClients);

        // Action Status - Both players
        for(int i = 0; i < 2; i++)
        {
            damage = 0; // reset damage.
            if(i == 0)
            {
                opponent = player2Name;
            }
            else if (i == 1)
            {
                opponent = player1Name;
            }
            msg = receiveAll(allClients[i]);
            if(msg == "stunned")
            {
                msg = nameArray[i] + " is currently stunned.";
                if(i+1 == 1)
                {
                    sendAll(allClients[1], std::to_string(0));
                    sendAll(allClients[1], "none");
                }
                else if(i+1 == 2)
                {
                    sendAll(allClients[0], std::to_string(0));
                    sendAll(allClients[0], "none");
                }
            }
            else if(msg == "attack")
            {
                if(i == 0) {
                    std::cout << player1Name << " attacks" << std::endl << std::endl;
                } else if(i == 1) {
                    std::cout << player2Name << " attacks" << std::endl << std::endl;
                }
                msg = receiveAll(allClients[i]);
                sendAll(allClients[i], "confirm");
                msg = msg + opponent;
                //std::cout << msg << std::endl;
                damageString = receiveAll(allClients[i]);
                damage = atoi(damageString.c_str());
                //std::cout << "Damage Received" << std::endl;
                if(i+1 == 1)
                {
                    sendAll(allClients[1], std::to_string(damage));
                    sendAll(allClients[1], "none");
                }
                else if(i+1 == 2)
                {
                    sendAll(allClients[0], std::to_string(damage));
                    sendAll(allClients[0], "none");
                }
                //std::cout << "Damage sent" << std::endl;
            }
            else if(msg == "defend")
            {
                if(i == 0) {
                    std::cout << player1Name << " defends" << std::endl << std::endl;
                } else if(i == 1) {
                    std::cout << player2Name << " defends" << std::endl << std::endl;
                }
                msg = receiveAll(allClients[i]);
                if(i+1 == 1)
                {
                    sendAll(allClients[1], std::to_string(0));
                    sendAll(allClients[1], "none");
                }
                else if(i+1 == 2)
                {
                    sendAll(allClients[0], std::to_string(0));
                    sendAll(allClients[0], "none");
                }
            }
            else if(msg == "risk")
            {
                if(i == 0) {
                    std::cout << player1Name << " risks it" << std::endl;
                } else if(i == 1) {
                    std::cout << player2Name << " risks it" << std::endl;
                }
                msg = receiveAll(allClients[i]);
                sendAll(allClients[i], "confirm");
                msg = msg + opponent;
                damageString = receiveAll(allClients[i]);
                damage = atoi(damageString.c_str());
                effect = receiveAll(allClients[i]);
                if(i+1 == 1)
                {
                    sendAll(allClients[1], std::to_string(damage));
                    sendAll(allClients[1], effect);
                }
                else if(i+1 == 2)
                {
                    sendAll(allClients[0], std::to_string(damage));
                    sendAll(allClients[0], effect);
                }
            }
            //std::cout << "Just before Ability Desc." << std::endl;
            sendToAllClients(msg, allClients);
            //std::cout << "Ability Desc send to both players." << std::endl;

            // check if any players died
            player1Health = atoi(receiveAll(allClients[0]).c_str());
            player2Health = atoi(receiveAll(allClients[1]).c_str());
            if(player1Health <= 0 && player2Health <= 0) {
                sendToAllClients("It's a draw! Both players are down!", allClients);
                gameRuns = false;
            } else if(player1Health <= 0) {
                msg = player2Name + " wins!";
                sendToAllClients(msg, allClients);
                gameRuns = false;
            } else if(player2Health <= 0) {
                msg = player1Name + " wins!";
                sendToAllClients(msg, allClients);
                gameRuns = false;
            } else {
                sendToAllClients("no casualties", allClients);
            }
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
void sendToAllClients(std::string msg, SOCKET clientArray[])
{
    memset(sendbuf, 0, DEFAULT_BUFLEN);
    msg = msg + "\0";
    int tempIResult;
    for(int i=0; i<2; i++)
    {
        tempIResult = send(clientArray[i], msg.c_str(), strlen(msg.c_str())+1, 0);
        if(tempIResult == SOCKET_ERROR)
        {
            std::cout << "send failed with error " << WSAGetLastError() << std::endl;
            closesocket(clientArray[i]);
            WSACleanup();
        }
    }
}

// Send all information to a Socket
void sendAll(SOCKET s, std::string msg)
{
    memset(sendbuf, 0, DEFAULT_BUFLEN);
    msg = msg + "\0";
    int tempIResult = send(s, msg.c_str(), strlen(msg.c_str())+1, 0);
    if (tempIResult <= 0)
    {
        std::cout << "Send failed" << std::endl;
    }
}

// Receive all information from a Socket
std::string receiveAll(SOCKET s)
{
    memset(recvbuf, 0, DEFAULT_BUFLEN);
    int tempResult = 1, total = 0, found = 0;

    while(!found) {
        tempResult = recv(s, &recvbuf[total], recvbuflen - total - 1, 0);
        if(tempResult == -1) {
            std::cout << "Error receiving" << std::endl;
            break;
        }
        total += tempResult;
        //temp[total] = '\0';
        found = (strchr(recvbuf, '\0') != 0);

    }
    std::cout << recvbuf << std::endl;
    return recvbuf;

    /*memset(recvbuf, 0, DEFAULT_BUFLEN);
    std::string message;
    int tempIResult = recv(s, recvbuf, recvbuflen, 0);
    if (tempIResult != 0)
    {
        message = recvbuf;
        message = message.c_str();
        return message;
    }*/
}
