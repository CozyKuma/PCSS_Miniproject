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
        bool stunned;
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
        bool isStunned();
        void changeStunned();
        void setStunned(bool stun);
        void printStats();
        int getDefense();
        void setDefense(int def);
        void takeDamage(int dmg);
        void changeDefenseFlag();
        bool getDefenseFlag();
        virtual bool getAbilitySuccess(int ability) {};
        virtual string getConditionChange(int ability, bool success) {};
        virtual int getAbilityDamage(int ability, bool success) {};
        virtual string getAbilityDesc(int ability, bool success, int damage) {};
        virtual void chooseAbility(int ability, Character& target, Character& self) {};
        virtual string getAbilityEffect(int ability, bool success) {};
};

#endif // CHARACTER_H
