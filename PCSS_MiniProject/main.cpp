#include <iostream>

using namespace std;

int main(){



}



class CombatSystem{


    void startCombat(Character c1, Character c2){

        bool gameRuns = true;
        bool initiativeRolled = false;

        int player1 = 0;
        int player2 = 0;

        Character turnOrder[2];
        Character player1;
        Character player2;
        bool swapTurn = false,
        while(gameRuns){

            if(initiativeRolled == false){
                rollInitiative();
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

            cout << "You currently have: " << activePlayer.health << " HP" << endl;
            cout << "Choose your ability by entering 1, 2 or 3" << endl;
            cin >> abilityNumber;
            activePlayer.chooseAbility(abilityNumber);

            checkHealth(player1, player2)


        }

    void checkHealth(Character activePlayer, inactivePlayer){
        if (activePlayer.health <= 0){
            activePlayer.alive = false;
            cout << inactivePlayer.getName() <<" has triumphed!" << endl;
            cout << "You have lost" << endl;

        }
        else if(inactivePlayer.health <= 0){
            inactivePlayer.alive = false;
            cout << "You have won!" << endl;
        }
        else{return}

    }

    void restart(){
        string exitString;
        cout << "Do you want play again? (y/n)" << endl;
        cin >> exitString;
    }

    void combatRollInitiative(){

        player1 = c1.rollDice(1,20);
        player2 = c2.rollDice(1,20);

        if(player1 > player2){

            turnOrder[0] = c1;
            turnOrder[1] = c2;
        }
        else if(player2 > player1){

            turnOrder[0] = c2;
            turnOrder[1] = c1;

        }
        else{

            combatRollInitiative();

        }

    }

};
