#include "Wizard.h"


Wizard::Wizard()
{

}

void Wizard::fireball(Character target)
{
    int damage = 0;
    damage = rollDice(1, 10);
    target.takeDamage(damage)
    cout<< "You gave " << damage << "damage to " << target.getName() <<endl;
}

void Wizard::spellShield(Character self)
{
    if (defenseFlag == false)
    {
        self.setDefense(2);
        self.changeDefenseFlag();
        cout<< "Your defense went up" <<endl;
    }
    else
    {
        cout<< "Spell shield is already active." <<endl;
    }

}

void Wizard::lightningStrike(Character target, Character self)
{
    int damage = 0
    damage = rollDice(3, 10);
    int result = rollDice(1, 3);
    if (result == 1 || result == 2)
    {
        target.takeDamage(damage);
        cout<< "You gave " << damage << "damage to " << target.getName() <<endl;
    }
    else if (result == 3)
    {
        self.takeDamage(damage);
        cout<< "You received " << damage << "damage." <<endl;
    }
}

void Wizard::chooseAbility(int ability, Character target, Character self)
{
    switch (ability)
        case 1:
            fireball(target)
            break;
        case 2:
            spellShield(self)
            break;
        case 3:
            lightningStrike(target, self)
            break;
        default:
            break;
}
