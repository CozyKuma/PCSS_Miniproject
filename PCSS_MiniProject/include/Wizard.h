#ifndef WIZARD_H
#define WIZARD_H
#include "Character.h"



class Wizard : public Character
{
    public:
        Wizard();
        Wizard(string wizName);
        void fireball(Character target);
        void spellShield(Character self);
        void lightningStrike(Character target, Character self);
        void chooseAbility(int ability, Character target, Character self);

    private:
        //Character player;
};

#endif // WIZARD_H
