/*#include "Fighter.h"

Fighter::Fighter()
{
    //ctor
}

Fighter::~Fighter()
{
    //dtor
}

void Fighter:slam(Character target){
    int damage = 0;
    damage = rollDice(1, 10);
    target.takeDamage(damage);
    cout<< "You dealt " << damage << "points of damage to " << target.getName() <<endl;

}

void Fighter::reflect(Character target, int damage){


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
