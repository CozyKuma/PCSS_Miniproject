#include "Wizard.h"

Wizard::Wizard(string newName)
: Character(newName)
{
}
Wizard::Wizard() : Character()
{

}

void Wizard::fireball(Character& target)
{
    int damage = 0;
    damage = Dice::rollDice(1, 10);
    target.takeDamage(damage);
    cout << "You cast fireball and deal " << damage << " points of damage to " << target.getName() <<endl;
    damage = 0;
}

void Wizard::spellShield(Character& self)
{

    if (!self.getDefenseFlag())
    {
        self.setDefense(2);
        self.changeDefenseFlag();
        cout<< "You cast spell shield, your defense go up" <<endl;
    }
    else
    {
        cout<< "You try to cast spell shield, but a spell shield is already active." <<endl;
    }

}

void Wizard::lightningStrike(Character& target, Character& self)
{
    int damage = 0;
    damage = Dice::rollDice(3, 10);
    int result = Dice::rollDice(1, 1);
    if (result == 1 || result == 2)
    {
        target.takeDamage(damage);
        cout<< "You cast lightning strike and deal " << damage << " damage to " << target.Character::getName() <<endl;
    }
    else
    {
        self.takeDamage(damage);
        cout<< "You accidentally cast lightning strike on yourself and receive " << damage << " damage." <<endl;
    }
}

void Wizard::chooseAbility(int ability, Character& target, Character& self)
{
    switch (ability){
        case 1:
            fireball(target);
            break;
        case 2:
            spellShield(self);
            break;
        case 3:
            lightningStrike(target, self);
            break;
        default:
            cout << "choose ability default" << endl;
            break;
    }
}
