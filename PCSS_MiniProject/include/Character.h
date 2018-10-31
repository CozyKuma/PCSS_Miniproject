#ifndef CHARACTER_H
#define CHARACTER_H
#include "ClassType.h"
#include <string>
#include <iostream>

using namespace std;

class Character
{
    private:
        string name;
        int maxHealth;
        int health;
        ClassType aClass;
        int strength;
        int dexterity;
        int intelligence;
        bool alive;
        int defense;
        bool defenseFlag;

    public:
        Character(string newName);
        string getName();
        ClassType getClass();
        void setClass(ClassType newClass);
        int getHealth();
        void setHealth(int h);
        int getMaxHealth();
        void setMaxHealth(int MHP);
        bool isAlive();
        void changeAlive();
        void printStats();
        int getDefense();
        void setDefense(int def);
        void takeDamage(int dmg);
        void changeDefenseFlag();
};

#endif // CHARACTER_H
