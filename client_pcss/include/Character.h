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
        int defense;
        int health;
        bool alive;
        bool stunned;
        bool defenseFlag;

    public:
        Character();
        Character(string newName);
        void setName(string n);
        string getName();
        int getHealth();
        void setHealth(int h);
        bool isAlive();
        void changeAlive();
        bool isStunned();
        void changeStunned();
        void setStunned(bool stun);
        int getDefense();
        void setDefense(int def);
        void takeDamage(int dmg);
        void changeDefenseFlag();
        bool getDefenseFlag();
        virtual bool getAbilitySuccess(int ability) {return false;};
        virtual string getConditionChange(int ability, bool success) {return "";};
        virtual int getAbilityDamage(int ability, bool success) {return 0;};
        virtual string getAbilityDesc(int ability, bool success, int &damage) {return "";};
        virtual void chooseAbility(int ability, Character& target, Character& self) {};
        virtual string getAbilityEffect(int ability, bool success) {return "";};
};

#endif // CHARACTER_H
