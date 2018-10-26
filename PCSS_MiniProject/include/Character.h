#ifndef CHARACTER_H
#define CHARACTER_H
#include classType_


class Character
{
    public:
        Character();
        virtual ~Character();
        string name;
        int maxHealth;
        classType Class;
        int strength;
        int dexterity;
        int intelligence;
        bool alive;

    private:
        int rollInit;
        string getName;
        int getHealth;
        void int setHealth;
        bool isAlive;
};

#endif // CHARACTER_H
