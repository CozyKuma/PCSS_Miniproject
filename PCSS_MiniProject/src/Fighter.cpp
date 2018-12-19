#include "Fighter.h"

Fighter::Fighter(string newName)
: Character(newName)
{
}
Fighter::Fighter() : Character()
{

}

void Fighter::slam(Character& target){
    int damage = 0;
    damage = Dice::rollDice(1, 10);
    target.takeDamage(damage);
    cout<< "You use slam and dealt " << damage << "points of damage to " << target.getName() <<endl;

}

/*void Fighter::reflect(Character& target, int damage){


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

}*/
void Fighter::stunningLeap(Character& target){

}
void Fighter::chooseAbility(int ability, Character& target, Character& self)
{
    switch (ability){
        case 1:
            slam(target);
            break;
        case 2:
            //reflect(target);
            break;
        case 3:
//            stunningLeap():
            break;
        default:
            cout << "choose ability default" << endl;
            break;
    }
}
