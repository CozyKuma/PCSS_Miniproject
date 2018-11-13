#include "Game.h"

Game::Game()
{
    //ctor
}

Game::~Game()
{
    //dtor
}

Character rollInitiative(Character c1, Character c2){

    int player1 = Dice::rollDice(1, 20);

    int player2 = Dice::rollDice(1, 20);

    if(player1 > player2){

        return c1;
    }
    else if(player2 > player1){

        return c2;
    }
    else{

        rollInitiative(c1, c2);

    }

}

void checkHealth(Character activePlayer, Character inactivePlayer){
    if (!activePlayer.isAlive()){
        cout << inactivePlayer.getName() <<" has triumphed!" << endl;
        cout << "You have lost" << endl;

    }
    else if(!inactivePlayer.isAlive()){
        cout << "You have won!" << endl;
    }
    else{
        cout << "No one died" << endl;
    }

}

void restart(){
    string exitString;
    cout << "Do you want play again? (y/n)" << endl;
    cin >> exitString;
}


void startCombat(){

    bool gameRuns = true;
    bool initiativeRolled = false;

    Character player1;
    Character player2;

    Character activePlayer;
    Character inactivePlayer;

    bool swapTurn = false;

    while(gameRuns){

        if(initiativeRolled == false){

            player1 = rollInitiative(player1, player2);
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

        activePlayer.chooseAbility(abilityNumber, inactivePlayer, activePlayer);

        checkHealth(player1, player2);


    }

}




