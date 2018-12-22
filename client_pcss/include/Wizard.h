#ifndef WIZARD_H
#define WIZARD_H
#include "Character.h"



class Wizard : public Character
{
    public:
        Wizard();
        Wizard(string newName);
        void fireball(Character& target);
        void spellShield(Character& self);
        void lightningStrike(Character& target, Character& self);
        void chooseAbility(int ability, Character& target, Character& self);
        string getAbilityDesc(int ability, bool success, int damage);
        int getAbilityDamage(int ability, bool success);
        string getConditionChange(int ability, bool success);
        bool getAbilitySuccess(int ability);

    private:
        //Character player;
};

#endif // WIZARD_H
