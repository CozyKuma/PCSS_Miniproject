#include "Character.h"

Character::Character()
{
       public:
        Character();
        virtual ~Character();
        string name;
        int maxHealth;
        ClassType aClass;
        int strength;
        int dexterity;
        int intelligence;
        bool alive;

    private:
        int rollInit()

        string getName()
        {
            return name;
        }

        int getHealth()
        {
            return maxHealth;
        }

        void int setHealth(int health)
        {
            health = maxHealth;
        }

        bool isAlive(health)
        {

            if (maxHealth > 0)
            {
                return true;
            } else
            {
                return false;
            }
        }


}

Character::~Character()
{
    //dtor
}
