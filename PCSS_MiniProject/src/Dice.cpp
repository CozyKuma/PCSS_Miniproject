#include "Dice.h"
#include <cstdlib>
#include <ctime>



int Dice::rollDice(int amount, int sides)
{
    srand(time(0));
    int result = 0;
    for (int i = 0; i < amount; i++)
    {
      result += rand() % sides + 1;
    }
    return result;


}
