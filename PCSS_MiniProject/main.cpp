#include <iostream>
#include <string>
#include <time.h>


#include <CombatSystem.h>
#include <Character.h>

// Races for the Character
#include <Human.h>
#include <Wombat.h>
#include <Elf.h>

// Classes the Character can pick
#include <Wizard.h>
#include <Fighter.h>
#include <Ranger.h>
=======
#include "Ranger.h"


>>>>>>> No-branch


using namespace std;

typedef Character* characPtr;


//Method for deciding who goes first in the beginning.
void rollInitiative(Character* c1, Character* c2, Character* cArray[]){

    int result = Dice::rollDice(1, 20);

    if(result > 10){

        cArray[0] = c1;
        cArray[1] = c2;
        return;
    }else{
        cArray[0] = c2;
        cArray[1] = c1;
        return;
    }

}
bool restartGame(Character* activePlayer, Character* inactivePlayer){
    int exit;
    cout << "Do you want to play again? Yes/no? (1/2)" << endl;
    cin >> exit;
    if (exit == 1)
    {
        return true;
    }
    else{
        return false;
    }
}

bool checkHealth(Character* activePlayer, Character* inactivePlayer){
    if (activePlayer->getHealth() <= 0){
        cout << inactivePlayer->getName() <<" has triumphed!" << endl;
        cout << "You have lost" << endl;
        //restartGame(activePlayer, inactivePlayer);
        return false;
    }
    else if(inactivePlayer->getHealth()<= 0){
        cout << "You have won!" << endl;
       // restartGame(activePlayer, inactivePlayer);
        return false;
    }
    return true;
}



/*void characterCreation(){
    int classChoice = 0;
    Character* players[2] = {};
    static int playerAmount = 0;
    string nameChoice;
    cout << "What is your class? 1 = Wizard, 2 = Fighter, 3 = Ranger" << endl;
    cin >> classChoice;
    cout << "What is your name?" << endl;
    cin >> nameChoice;
    switch (classChoice){
        case 1:
            Wizard* players[playerAmount] = new Wizard(nameChoice);
            playerAmount += 1;
            break;
        case 2:
            Fighter* players[playerAmount] = new Fighter(nameChoice);
            playerAmount += 1;
            break;
        case 3:
            Ranger* players[playerAmount] = new Ranger(nameChoice);
            playerAmount += 1;
            break;
        default:
            cout << "Invalid number for class" << endl;
            break;
    }


}*/

void startCombat(Character* c1, Character* c2){

    bool gameRuns = true;
    bool initiativeRolled = false;
    int turnCounter = 1;

    Character* turnOrder[2];
    Character* player1;
    Character* player2;

    Character* activePlayer;
    Character* inactivePlayer;




    bool swapTurn = false;

    while(gameRuns){

        if(!initiativeRolled){

            rollInitiative(c1, c2, turnOrder);
            player1 = turnOrder[0];
            player2 = turnOrder[1];
            initiativeRolled = true;
        }

        if(swapTurn == false){
            activePlayer = player1;
            inactivePlayer = player2;
            swapTurn = true;

        }
        else{
            activePlayer = player2;
            inactivePlayer = player1;
            swapTurn = false;
        }
        cout << "--------TURN " << turnCounter <<"--------" << endl;
        int abilityNumber;
        cout << "You currently have: " << activePlayer->getHealth() << " HP" << endl;
        cout << inactivePlayer->getName()<<" currently has: " << inactivePlayer->getHealth() << " HP" << endl;
        if(activePlayer->isStunned()){
            cout << "You are stunned and your turn has been skipped" << endl;
            activePlayer->changeStunned();
        }
        else{
        cout << "Choose your ability by entering 1 (normal attack), 2 (defensive action) or 3 (high risk/high reward attack)" << endl;
        cin >> abilityNumber;
        activePlayer->chooseAbility(abilityNumber, *inactivePlayer, *activePlayer);
        }
        gameRuns = checkHealth(activePlayer, inactivePlayer);
        turnCounter += 1;

        if(!gameRuns){
            gameRuns = restartGame(activePlayer, inactivePlayer);
            activePlayer->setHealth(100);
            inactivePlayer->setHealth(100);
            activePlayer->setStunned(false);
            inactivePlayer->setStunned(false);
            turnCounter = 1;
        }
    }
}
int main()
{
    cout << "Welcome to the jungle" << endl;
    cout << "Please enter the name of your character:";
    cin >> name;
    Character player = Character(name);

=======
>>>>>>> No-branch

    return 0;

}
