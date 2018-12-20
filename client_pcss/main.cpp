#undef UNICODE

#define _WIN32_WINNT 0x501

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include "Character.h"
#include "Wizard.h"
#include "Fighter.h"
#include "Ranger.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

typedef Character* characPtr;

string characterCreation(Character &playerCharacter);

int __cdecl main(int argc, char **argv)
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL,
                         *ptr = NULL,
                          hints;
    char *sendbuf = "this is a test";
    char recvbuf[DEFAULT_BUFLEN];
    int iResult;
    int recvbuflen = DEFAULT_BUFLEN;

    // Validate the parameters
    if (argc != 2)
    {
        printf("usage: %s server-name\n", argv[0]);
        return 1;
    }

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0)
    {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    // Resolve the server address and port
    iResult = getaddrinfo(argv[1], DEFAULT_PORT, &hints, &result);
    if ( iResult != 0 )
    {
        printf("getaddrinfo failed with error: %d\n", iResult);
        WSACleanup();
        return 1;
    }

    // Attempt to connect to an address until one succeeds
    for(ptr=result; ptr != NULL ; ptr=ptr->ai_next)
    {

        // Create a SOCKET for connecting to server
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype,
                               ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET)
        {
            printf("socket failed with error: %d\n", WSAGetLastError());
            WSACleanup();
            return 1;
        }

        // Connect to server.
        iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR)
        {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("Unable to connect to server!\n");
        WSACleanup();
        return 1;
    }

    // Send an initial buffer
    iResult = send( ConnectSocket, sendbuf, (int)strlen(sendbuf), 0 );
    if (iResult == SOCKET_ERROR)
    {
        printf("send failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    printf("Bytes Sent: %d\n", iResult);


    characPtr player;
    int playerOrder = 0;
    string classType;
    // Welcome and character select
    while(true)
    {
        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if(iResult > 0)
        {
            cout << recvbuf << endl;
            memset(recvbuf, 0, recvbuflen);
        } else {
            cout << "Receive failed with error " << WSAGetLastError() << endl;
        }
    }

    // Receive order of players
    iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
    //playerOrder = recvbuf;
    cout << "Received from server: " << recvbuf << endl;
    if(playerOrder == 1 || playerOrder == 2)
    {
        cout << endl << "You are player " << playerOrder << endl;
    }
    else
    {
        cout << "Something went wrong. You are player ?? " << playerOrder << endl;
    }

    recv(ConnectSocket, recvbuf, recvbuflen, 0);
    cout << recvbuf << endl;
    if(playerOrder == 1)
    {
        // classType = characterCreation(player);
        Wizard* w1 = new Wizard("WizardMan");
        player = w1;
        classType = "Wizard";
        send(ConnectSocket, classType.c_str(), strlen(classType.c_str()), 0);
    }
    else if (playerOrder == 2)
    {
        recv(ConnectSocket, recvbuf, recvbuflen, 0);
        cout << recvbuf << endl;
    }

    if(playerOrder == 2)
    {
        // classType = characterCreation(player);
        Fighter* f1 = new Fighter("FighterMan");
        player = f1;
        classType = "Fighter";
        send(ConnectSocket, classType.c_str(), strlen(classType.c_str()), 0);
    }
    else if (playerOrder == 1)
    {
        recv(ConnectSocket, recvbuf, recvbuflen, 0);
        cout << recvbuf << endl;
    }


    // Receive until the peer closes the connection
    do
    {

        iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
        if ( iResult > 0 )
            printf(recvbuf);
        else if ( iResult == 0 )
            printf("Connection closed\n");
        else
            printf("recv failed with error: %d\n", WSAGetLastError());

    }
    while( iResult > 0 );

    // shutdown the connection since no more data will be sent
    iResult = shutdown(ConnectSocket, SD_SEND);
    if (iResult == SOCKET_ERROR)
    {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }

    // cleanup
    closesocket(ConnectSocket);
    WSACleanup();

    return 0;
}

string characterCreation(Character &playerCharacter)
{
    int classChoice = 0;
    string nameChoice;
    cout << "What is your name?" << endl;
    cin >> nameChoice;
    while(classChoice != 1 || classChoice != 2 || classChoice != 3)
    {
        cout << "What is your class? 1 = Wizard, 2 = Fighter, 3 = Ranger" << endl;
        cin >> classChoice;
        if(classChoice == 1)
        {
            Wizard* w1 = new Wizard(nameChoice);
            playerCharacter = *w1;
            return "Wizard";
        }
        else if(classChoice == 2)
        {
            Fighter* f1 = new Fighter(nameChoice);
            playerCharacter = *f1;
            return "Fighter";
        }
        /*else if(classChoice == 3)
        {
            Ranger* r1 = new Ranger(nameChoice);
            playerCharacter = r1;
            return "Ranger";
        }*/
        else
        {
            cout << "Invalid number for class" << endl;
        }
    }
}
