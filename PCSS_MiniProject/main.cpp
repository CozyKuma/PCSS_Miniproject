#include <iostream>

using namespace std;

int main(){



}



class CombatSystem{


    void startCombat(Character c1, Character c2){

        bool gameRuns = true;

        int player1 = 0;
        int player2 = 0;

        Character turnOrder[2];


        while(gameRuns){

            rollInitiative(); //skal kun gøres en gang

            Character activePlayer;
            for(int i = 0; i < 2; i++){

                activePlayer = turnOrder[i];


            }



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
