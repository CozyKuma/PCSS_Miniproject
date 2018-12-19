#include <iostream>
#include "Character.h"
#include "Archer.h"

#include "Wizard.h"
#include "Fighter.h"
#include "Ranger.h"



using namespace std;

typedef Character* characPtr;



void rollInitiative(Character* c1, Character* c2, Character* cArray[]){

    int player1 = Dice::rollDice(1, 20);
    int player2 = Dice::rollDice(1, 1);
    if(player1 > player2){

        cArray[0] = c1;
        cArray[1] = c2;
        return;
    }
    if(player2 > player1){

        cArray[0] = c2;
        cArray[1] = c1;
        return;
    }
    else{

        rollInitiative(c1, c2, cArray);

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
        cout << "Choose your ability by entering 1, 2 or 3" << endl;
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
    characPtr player1;
    characPtr player2;
    Wizard* w1 = new Wizard("WizardMan");
    Fighter* f2 = new Fighter("FighterMan");
  //  Ranger* r2 = new Ranger("RangerMan");
    player1 = w1;
    player2 = f2;
  //  player1->chooseAbility(1, *player2, *player1);
    startCombat(player1, player2);

    return 0;

}



