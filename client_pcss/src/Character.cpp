#include "Character.h"

using namespace std;

Character::Character(string newName):
    name(newName),
    defense(1),
    health(100),
    maxHealth(100),
    strength(10),
    dexterity(10),
    intelligence(10),
    alive(true),
    stunned(false),
    defenseFlag(false){}

Character::Character():
    name("Bob"),
    defense(1),
    health(100),
    maxHealth(100),
    strength(10),
    dexterity(10),
    intelligence(10),
    alive(true),
    stunned(false),
    defenseFlag(false){}


        void Character::setName(string n)
        {
            name = n;
        }
        string Character::getName()
        {
            return name;
        }

        int Character::getHealth()
        {
            return health;
        }

        void Character::setHealth(int h)
        {
            health = h;
        }

        bool Character::isAlive()
        {
            return alive;
        }

        void Character::changeAlive()
        {
            if (alive == true && health <= 0)
            {
                alive = false;
            }
            else
            {
                alive = true;
            }
        }

        bool Character::isStunned()
        {
            return stunned;
        }

        void Character::changeStunned()
        {
            if (stunned == true){

                stunned = false;
            }
            else{
                stunned = true;
            }
        }

        void Character::setStunned(bool stun){

            stunned = stun;
        }

        int Character::getMaxHealth()
        {
            return maxHealth;
        }

        void Character::setMaxHealth(int MHP)
        {
            maxHealth = MHP;
        }

        void Character::printStats()
        {
            cout<< "Strength: " + strength << endl;
            cout<< "dexterity: " + dexterity <<endl;
            cout<< "intelligence: " + intelligence <<endl;
        }

        int Character::getDefense()
        {
            return defense;
        }

        void Character::setDefense(int def)
        {
            defense = def;
        }

        void Character::takeDamage(int dmg)
        {
            dmg = dmg/defense;
            health = health - dmg;
        }

        void Character::changeDefenseFlag()
        {
            if (defenseFlag == false)
            {
                defenseFlag = true;
                setDefense(2);
            }
            else
            {
                defenseFlag = false;
                setDefense(1);
            }
        }

        bool Character::getDefenseFlag()
        {
            return defenseFlag;

        }

