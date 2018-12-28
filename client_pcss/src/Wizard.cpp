#include "Wizard.h"

Wizard::Wizard(string newName)
: Character(newName)
{
}
Wizard::Wizard() : Character()
{

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
