#include "Character.h"
#include "ClassType.h"

Character::Character(string newName)
{

        string name = newName;
        int maxHealth = 100;
        int health = 100;
        ClassType aClass;
        int strength = 10;
        int dexterity = 10;
        int intelligence = 10;
        bool alive = true;
        int defense = 10;
        bool defenseFlag = true;
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

        ClassType Character::getClass()
        {
            return aClass;
        }

        void Character::setClass(ClassType newClass)
        {
            aClass = newClass;
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
            health = health - dmg;
        }

        void Character::changeDefenseFlag()
        {
            if (defenseFlag == true)
            {
                defenseFlag = false;
            }
            else
            {
                defenseFlag = true;
            }
        }

