#ifndef FIGHTER_H
#define FIGHTER_H
#include "Character.h"



class Fighter : public Character
{
    public:
        Fighter(string newName);
        Fighter();
        void slam(Character& target);
        void reflect(Character& target);
        void stunningLeap(Character& target);
        void chooseAbility(int ability, Character& target, Character& self);
    protected:

    private:
};

#endif // FIGHTER_H

