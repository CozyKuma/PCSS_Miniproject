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
        cout<< "You cast a spell shield, your defense go up" <<endl;
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
    int result = Dice::rollDice(1, 3);
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

string Wizard::getAbilityDesc(int ability, bool success, int &damage)
{
    string tempName = Character::getName();
    string tempString;
    if(ability == 1)
    {
        tempString = tempName + " cast fireball and dealt " + to_string(damage) + " points of damage to ";
    }
    else if (ability == 2)
    {
        tempString = tempName + " cast a spell shield. Your defense has gone up for the next round.";
    }
    else if (ability == 3)
    {
        if(success)
        {
            tempString = tempName + " cast lightning strike and dealt " + to_string(damage) + " points of damage to ";
        }
        else
        {
            tempString = tempName + " accidentally cast lightning strike on yourself and receive " + to_string(damage) + " damage and completely missing ";
            this->takeDamage(damage);
            damage = 0;
        }
    }
    return tempString;
}

int Wizard::getAbilityDamage(int ability, bool success)
{
    int tempDamage = 0;
    if(ability == 1)
    {
        tempDamage = Dice::rollDice(1,10);
    }
    else if (ability == 2)
    {
        cout << "This is a defensive ability" << endl;
    }
    else if (ability == 3)
    {
        if(success)
        {
            tempDamage = Dice::rollDice(3,10);
        }
        else
        {
            tempDamage = Dice::rollDice(3,10);
        }
    }
    return tempDamage;
}

string Wizard::getConditionChange(int ability, bool success) {
    string tempString;
    tempString = "none";
    return tempString;
}

bool Wizard::getAbilitySuccess(int ability) {
    bool tempBool;
    int roll = Dice::rollDice(1, 3);
    if(ability == 3) {
        if(roll == 1 || roll == 2) {
            tempBool = true;
        } else {
            tempBool = false;
        }
    }
    return tempBool;
}

string Wizard::getAbilityEffect(int ability, bool success) {
    string tempEffect;
    tempEffect = "none";
    return tempEffect;
}
