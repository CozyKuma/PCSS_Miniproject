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
    cout<< "You use slam and deal " << damage << "points of damage to " << target.getName() <<endl;

}

/*void Fighter::reflect(Character& target, int damage){


    int result = rollDice(1, 3);
    if (result == 1 || result == 2)
    {
        target.takeDamage(damage);
        cout<< "You deal " << damage << "damage to " << target.getName() <<endl;
    }
    else if (result == 3)
    {
        self.takeDamage(damage);
        cout<< "You receive " << damage << "damage." <<endl;
    }

}*/
void Fighter::stunningLeap(Character& target){
    int damage = 0;
    int result = 0;
    damage = Dice::rollDice(1, 5);
    result = Dice::rollDice(1,1);
    if(result == 1 ||  result == 2){
        target.takeDamage(damage);
        target.setStunned(true);
        cout << "You leap into the air and deal a solid stunning blow and deal "<< damage << " points of damage to " << target.getName() <<endl;

    }
    else{
        target.takeDamage(damage);
        cout << "You leap into the air, however, your execution is sloppy and you fail to land a stunning blow, but still deal " << damage << " points of damage to " << target.getName() <<endl;
    }

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
            stunningLeap(target);
            break;
        default:
            cout << "choose ability default" << endl;
            break;
    }
}
