#include "Dice.h"
#include <cstdlib>


int Dice::rollDice(int amount, int sides)
{
    srand (time(NULL));
    int result = 0;
    for (int i = 0; i < amount; i++)
    {
       // result = result + rand()% sides +1;
        result = result + (rand() % sides) + 1;
    }
    return result;

}
