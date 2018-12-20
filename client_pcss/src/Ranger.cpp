/*#include "Ranger.h"

Ranger::Ranger(string newName)
: Character(newName)
{

}

Ranger::Ranger() : Character()
{

}

void Ranger::aimedShot(Character& target){
    int damage = 0;
    damage = rollDice(1, 10);
    target.takeDamage(damage);
    cout<< "You dealt " << damage << "points of damage to " << target.getName() <<endl;
}

void Ranger::bandage(Character& self){
    int heal = 0;
    heal = -1*rollDice(1, 8);
    self.takeDamage(heal);
    cout<< "You healed " << heal << "HP"<<endl;
}

void Ranger::bearTrap(){
    trapPlaced = true;
}
void chooseAbility(int ability, Character& target, Character& self){

    switch (ability){
        case 1:
            aimedShot(target);
            break;
        case 2:
            bandage(self);
            break;
        case 3:
            bearTrap();
            break;
        default:
            cout << "choose ability default" << endl;
            break;
    }

}
*/
