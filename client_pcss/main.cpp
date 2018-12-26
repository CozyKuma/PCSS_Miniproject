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
#include "Dice.h"

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

typedef Character* characPtr;

string characterCreation(Character &playerCharacter);
//string receiveAll(SOCKET s, char *buf, int *len);
string receiveAll(SOCKET s);
void sendAll(SOCKET s, string msg);

char recvbuf[DEFAULT_BUFLEN];
int recvbuflen = DEFAULT_BUFLEN;
char sendbuf[DEFAULT_BUFLEN];



int __cdecl main(int argc, char **argv)
{
    WSADATA wsaData;
    SOCKET ConnectSocket = INVALID_SOCKET;
    struct addrinfo *result = NULL,
                         *ptr = NULL,
                          hints;
    int iResult;
    //memset(recvbuf, '\0', DEFAULT_BUFLEN);
    //memset(sendbuf, '\0', DEFAULT_BUFLEN);

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


    //setsockopt(ConnectSocket, SOL_SOCKET, SO_RCVTIMEO,  recvbuf, recvbuflen);
    characPtr player;
    int playerOrder = 0;
    string classType;
    bool gameRuns = true;
    // Welcome message
    string myString = receiveAll(ConnectSocket);
    cout << myString << endl;


    // Receive order of players
    myString = receiveAll(ConnectSocket);
    playerOrder = atoi(myString.c_str());

    if(playerOrder == 1 || playerOrder == 2)
    {
        cout << "You are player #" << playerOrder << endl << endl;
    }
    else
    {
        cout << "Something went wrong. You are player ?? " << playerOrder << endl;
    }


    // Players choose characters.
    myString = receiveAll(ConnectSocket);
    cout << myString << endl;
    if(playerOrder == 1)
    {
        // classType = characterCreation(player);
        Wizard* w1 = new Wizard("WizardMan");
        player = w1;
        classType = "Wizard";
        sendAll(ConnectSocket, classType);
    }

    // Feedback from server
    myString = receiveAll(ConnectSocket);
    cout << myString << endl << endl;

    // Next character
    myString = receiveAll(ConnectSocket);
    cout << myString << endl;
    if(playerOrder == 2)
    {
        // classType = characterCreation(player);
        Fighter* f1 = new Fighter("FighterMan");
        player = f1;
        classType = "Fighter";
        sendAll(ConnectSocket, classType);
    }
    // Feedback from server
    myString = receiveAll(ConnectSocket);
    cout << myString << endl << endl;

    sendAll(ConnectSocket, player->getName());

    string abilityDesc;
    int abilityNumber;
    bool abilitySuccess;
    int abilityDamage;
    string abilityEffect;
    while(gameRuns)
    {
        // Turn #
        myString = receiveAll(ConnectSocket);
        cout << endl << "--------TURN " << myString <<"--------" << endl << endl;

        // Send/Receive Health Status
        sendAll(ConnectSocket, to_string(player->getHealth()));
        myString = receiveAll(ConnectSocket);
        cout << myString << endl;
        myString = receiveAll(ConnectSocket);
        cout << myString << endl << endl;

        for(int i = 0; i < 2; i++)
        {
            //Reset Ability Number
            abilityNumber = 0;
            abilitySuccess =  false;
            abilityDamage = 0;
            abilityDesc = "";
            abilityEffect = "none";
            if(playerOrder == i+1 && !player->isStunned())
            {
                cout << "Choose your ability by entering 1 (normal attack), 2 (defensive action) or 3 (high risk/high reward attack)" << endl;
                do
                {
                    cin >> abilityNumber;
                    if(abilityNumber == 1)
                    {
                        sendAll(ConnectSocket, "attack");

                        // get necessary attack data
                        abilitySuccess = player->getAbilitySuccess(abilityNumber);
                        abilityDamage = player->getAbilityDamage(abilityNumber, abilitySuccess);
                        abilityDesc = player->getAbilityDesc(abilityNumber, abilitySuccess, abilityDamage);

                        sendAll(ConnectSocket, abilityDesc);
                        sendAll(ConnectSocket, to_string(abilityDamage));
                    }
                    else if(abilityNumber == 2)
                    {
                        sendAll(ConnectSocket, "defend");

                        // get necessary attack data
                        abilityDesc = player->getAbilityDesc(abilityNumber, abilitySuccess, abilityDamage);

                        sendAll(ConnectSocket, abilityDesc);
                    }
                    else if(abilityNumber == 3)
                    {
                        sendAll(ConnectSocket, "risk");

                        abilitySuccess = player->getAbilitySuccess(abilityNumber);
                        abilityDamage = player->getAbilityDamage(abilityNumber, abilitySuccess);
                        abilityDesc = player->getAbilityDesc(abilityNumber, abilitySuccess, abilityDamage);
                        abilityEffect = player->getAbilityEffect(abilityNumber, abilitySuccess);

                        sendAll(ConnectSocket, abilityDesc);
                        sendAll(ConnectSocket, to_string(abilityDamage));
                        sendAll(ConnectSocket, abilityEffect);

                    }
                    else
                    {
                        cout << "You can't choose that - please try again (1, 2 or 3)." << endl;
                    }
                }
                while((abilityNumber < 1) && (abilityNumber < 3));
            }
            else if(playerOrder == i+1 && player->isStunned())
            {
                sendAll(ConnectSocket, "stunned");
                player->changeStunned();
            }

            // Take damage if you are the opponent
            if(playerOrder == 2 && i+1 == 1)
            {
                player->takeDamage(atoi(receiveAll(ConnectSocket).c_str()));
                myString = receiveAll(ConnectSocket);
                if(myString == "stun")
                {
                    player->changeStunned();
                }
            }
            else if(playerOrder == 1 && i+1 == 2)
            {
                player->takeDamage(atoi(receiveAll(ConnectSocket).c_str()));
                myString = receiveAll(ConnectSocket);
                if(myString == "stun")
                {
                    player->changeStunned();
                }
            }

            // Server sends what happened to both clients
            myString = receiveAll(ConnectSocket);
            cout << myString << endl << endl;
        }
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

string receiveAll(SOCKET s)
{
    memset(recvbuf, 0, DEFAULT_BUFLEN);
    string message;
    int tempIResult = recv(s, recvbuf, recvbuflen, 0);
    if (tempIResult != 0)
    {
        message = recvbuf;
        message = message.c_str();
        return message;
    }
}

void sendAll(SOCKET s, string msg)
{
    memset(sendbuf, 0, DEFAULT_BUFLEN);
    int tempIResult = send(s, msg.c_str(), strlen(msg.c_str()), 0);
    //cout << "Client: - " << msg << " - has been sent" << endl;
    if (tempIResult <= 0)
    {
        cout << "Send failed" << endl;
    }
}
