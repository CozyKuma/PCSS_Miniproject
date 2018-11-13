#include <iostream>
#include <string>
#include <time.h>


#include <CombatSystem.h>
#include <Character.h>

// Races for the Character
#include <Human.h>
#include <Wombat.h>
#include <Elf.h>

// Classes the Character can pick
#include <Wizard.h>
#include <Fighter.h>
#include <Ranger.h>


using namespace std;

int main()
{
    cout << "Welcome to the jungle" << endl;
    cout << "Please enter the name of your character:";
    cin >> name;
    Character player = Character(name);


    return 0;
}
