#ifndef FIGHTER_H
#define FIGHTER_H
#include "Character.h"



class Fighter : public Character
{
    public:
        Fighter(string newName);
        Fighter();
        string getAbilityDesc(int ability, bool success, int &damage);
        int getAbilityDamage(int ability, bool success);
        string getConditionChange(int ability, bool success);
        bool getAbilitySuccess(int ability);
        string getAbilityEffect(int ability, bool success);
    protected:

    private:
};

#endif // FIGHTER_H

