#include "Character.h"


Character::Character(string newName)
{
        string name = newName;
        int maxHealth = 100;
        int health = 100;
        int strength = 10;
        int dexterity = 10;
        int intelligence = 10;
        bool alive = true;
        int defense = 1;
        bool defenseFlag = false;
}
Character::Character(){

        string name = "bob";
        int maxHealth = 100;
        int health = 100;
        int strength = 10;
        int dexterity = 10;
        int intelligence = 10;
        bool alive = true;
        int defense = 1;
        bool defenseFlag = false;

}
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
            }
            else
            {
                defenseFlag = false;
            }
        }

        bool Character::getDefenseFlag()
        {
            return defenseFlag;

        }

