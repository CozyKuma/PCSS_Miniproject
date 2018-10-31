#include <iostream>
#include "character.h"
#include <random>

using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}

int rollDice(int amount, int sides)
{
    int result = 0;
    for (int i = 0; i < amount; i++)
    {
        result = result + rand()% sides +1;
    }

}
