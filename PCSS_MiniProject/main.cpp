#include <iostream>
#include "Character.h"
#include "Wizard.h"
#include <cstdlib>

using namespace std;

typedef Character* characPtr;

int main()
{
    characPtr player1;
    characPtr player2;
    Wizard* w1 = new Wizard("Bob");
    Wizard* w2 = new Wizard("Bobby");
    player1 = w1;
    player2 = w2;
    player1->chooseAbility(1, *player2, *player1);

    return 0;

}

/*void rollInitiative(Character c1, Character c2, Character cArray[]){

    int player1 = Dice::rollDice(1, 20);
    int player2 = Dice::rollDice(1, 20);

    if(player1 > player2){

        cArray[0] = c1;
        cArray[1] = c2;
    }
    else if(player2 > player1){

        cArray[0] = c2;
        cArray[1] = c1;

    }
    else{

        rollInitiative(c1, c2, cArray);

    }

}

void checkHealth(Character activePlayer, Character inactivePlayer){
    if (!activePlayer.isAlive){
        cout << inactivePlayer.getName() <<" has triumphed!" << endl;
        cout << "You have lost" << endl;

    }
    else if(!inactivePlayer.isAlive){
        cout << "You have won!" << endl;
    }

    else{return}

}

void restart(){
    string exitString;
    cout << "Do you want play again? (y/n)" << endl;
    cin >> exitString;
}

void startCombat(Character c1, Character c2){

    bool gameRuns = true;
    bool initiativeRolled = false;

    Character turnOrder[2];
    Character player1;
    Character player2;

    Character activePlayer;
    Character inactivePlayer;




    bool swapTurn = false;

    while(gameRuns){

        if(initiativeRolled == false){
            rollInitiative(player1, player2, turnOrder);
            player1 = turnOrder[0];
            player2 = turnOrder[1];
        }

        if(swapTurn == false){
            activePlayer = player1;
            inactivePlayer = player2;
            swapTurn = true;
        }
        else{
            activePlayer = player2;
            inactivePlayer = player1;
        }
        int abilityNumber;
        cout << "You currently have: " << activePlayer.getHealth() << " HP" << endl;
        cout << "Choose your ability by entering 1, 2 or 3" << endl;
        cin >> abilityNumber;

       // Character.chooseAbility(abilityNumber, inactivePlayer, activePlayer);

        //checkHealth(player1, player2)


    }
}
*/


