#include "Dice.h"
#include <cstdlib>
#include <ctime>



int Dice::rollDice(int amount, int sides)
{
    int result = 0;
    for (int i = 0; i < amount; i++)
    {
      //srand(time(0));
      //result = rand() % sides + 1;
      result = amount + sides;
    }
    return result;

}
