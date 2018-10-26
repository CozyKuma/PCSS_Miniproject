#ifndef CHARACTER_H
#define CHARACTER_H
#include "ClassType.h"
#include <string>

using namespace std;

class Character
{
    private:
        string name;
        int maxHealth;
        ClassType Class;
        int strength;
        int dexterity;
        int intelligence;
        bool alive;

    public:
        Character(string name, ClassType aClass);
        int rollInit;
        string getName;
        int getHealth;
        int setHealth;
        bool isAlive;
};

#endif // CHARACTER_H
