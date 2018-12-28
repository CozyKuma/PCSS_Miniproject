#include "Fighter.h"

Fighter::Fighter(string newName)
    : Character(newName)
{
}

Fighter::Fighter() : Character()
{

}

string Fighter::getAbilityDesc(int ability, bool success, int &damage)
{
    string tempName = Character::getName();
    string tempString;
    if(ability == 1)
    {
        tempString = tempName + " use slam and dealt " + to_string(damage) + " points of damage to ";
    }
    else if (ability == 2)
    {
        tempString = tempName + " raise your shield to block incoming attacks. Your defense has gone up for the next round.";
    }
    else if (ability == 3)
    {
        if(success)
        {
            tempString = tempName + " leap into the air and dealt a solid stunning blow and dealt " + to_string(damage) + " points of damage to ";
        }
        else
        {
            tempString = tempName + " leap into the air, however, your execution is sloppy and you fail to land a stunning blow, but still dealt " + to_string(damage) + " points of damage to ";
        }
    }
    return tempString;
}

int Fighter::getAbilityDamage(int ability, bool success)
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
            tempDamage = Dice::rollDice(1,8);
        }
        else
        {
            tempDamage = Dice::rollDice(1,6);
        }
    }
    return tempDamage;
}

string Fighter::getConditionChange(int ability, bool success) {
    string tempString;
    if(ability == 3 && success) {
        tempString = "stun";
    } else {
        tempString = "none";
    }
    return tempString;
}

bool Fighter::getAbilitySuccess(int ability) {
    bool tempBool;
    int roll = Dice::rollDice(1, 3);
    if(ability == 3) {
        if(roll == 1) {
            tempBool = true;
        } else {
            tempBool = false;
        }
    }
    return tempBool;
}

string Fighter::getAbilityEffect(int ability, bool success) {
    string tempEffect;
    if(success && ability == 3) {
        tempEffect = "stun";
    } else {
        tempEffect = "none";
    }
    return tempEffect;
}

