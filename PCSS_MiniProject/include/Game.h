#ifndef GAME_H
#define GAME_H
#include "Character.h"


class Game
{
    public:
        Game();
        virtual ~Game();
        void startCombat(Character c1, Character c2);
        void checkHealth(Character activePlayer, Character inactivePlayer);
        void restart();
        Character rollInitiative(Character c1, Character c2);

    protected:

    private:
};

#endif // GAME_H

