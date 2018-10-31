#ifndef WIZARD_H
#define WIZARD_H
#include <ClassType.h>
#include <Character.h>

class Wizard : public ClassType
{
    public:
        Wizard();
        void fireball(Character target);
        void spellShield(Character self);
        void lightningStrike(Character target, Character self);
        int chooseAbility(int ability, Character target, Character self);

    private:
};

#endif // WIZARD_H
