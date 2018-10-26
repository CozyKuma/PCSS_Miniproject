#include "Character.h"
#include "ClassType.h"

Character::Character(string n, ClassType aC)
{

        string name;
        int maxHealth = 100;
        int health = 100;
        ClassType aClass;
        int strength = 10;
        int dexterity = 10;
        int intelligence = 10;
        bool alive = true;
        name = n;
        aClass = aC;



        int rollInit(){}

        string getName()
        {
            return name;
        }

        int getHealth()
        {
            return health;
        }

        int setHealth(int h)
        {
            health = h;
        }

        bool isAlive(int health)
        {

            if (health > 0)
            {
                return true;
            } else
            {
                return false;
            }
        }

        cout<< name << endl;

}

Character::~Character()
{
    //dtor
}
