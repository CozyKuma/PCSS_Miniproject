#include <iostream>
#include "character.h"
#include <random>
#include <cstdlib>
#include <ctime>


using namespace std;

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}

public static int rollDice(int amount, int sides)
{
    srand((unsigned)time(0));
    int result = 0;
    for (int i = 0; i < amount; i++)
    {
        result = result + rand()% sides +1;
    }

}
