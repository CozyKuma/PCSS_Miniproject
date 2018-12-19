#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <iostream>
#include "Dice.h"

using namespace std;

class Character
{
    private:
        string name;
        int maxHealth;
        int health;
        int strength;
        int dexterity;
        int intelligence;
        bool alive;
        int defense;
        bool defenseFlag;

    public:
        Character();
        Character(string newName);
        void setName(string n);
        string getName();
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
        bool getDefenseFlag();
        virtual void chooseAbility(int ability, Character& target, Character& self) {};
};

#endif // CHARACTER_H
