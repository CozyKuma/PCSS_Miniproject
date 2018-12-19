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
    cout<< "You use slam and deal " << damage << " points of damage to " << target.getName() <<endl;

}

void Fighter::block(Character& self){


    if (!self.getDefenseFlag())
    {
        self.setDefense(2);
        self.changeDefenseFlag();
        cout<< "You raise your shield to block incoming attacks. Your defense has gone up" <<endl;
    }
    else
    {
        cout<< "You fail in covering your vital areas and your defense remain unchanged." <<endl;
    }

}
void Fighter::stunningLeap(Character& target){
    int damage = 0;
    int result = 0;
    damage = Dice::rollDice(1, 8);
    result = Dice::rollDice(1,3);
    if(result == 1){
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
            block(self);
            break;
        case 3:
            stunningLeap(target);
            break;
        default:
            cout << "choose ability default" << endl;
            break;
    }
}
