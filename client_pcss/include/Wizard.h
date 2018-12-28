#ifndef WIZARD_H
#define WIZARD_H
#include "Character.h"



class Wizard : public Character
{
    public:
        Wizard();
        Wizard(string newName);
        string getAbilityDesc(int ability, bool success, int &damage);
        int getAbilityDamage(int ability, bool success);
        string getConditionChange(int ability, bool success);
        bool getAbilitySuccess(int ability);
        string getAbilityEffect(int ability, bool success);


    private:
        //Character player;
};

#endif // WIZARD_H
