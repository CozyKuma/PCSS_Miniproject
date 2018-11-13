#include "Dice.h"



int Dice::rollDice(int amount, int sides)
{
    int result = 0;
    for (int i = 0; i < amount; i++)
    {
       // result = result + rand()% sides +1;
        result = amount + sides;
    }
    return result;

}
