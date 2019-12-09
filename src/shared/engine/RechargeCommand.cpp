#include "../engine.h"
#include "../state.h"
#include <iostream> 
#include <unistd.h>
#include <stdlib.h>
#include "RechargeCommand.h"

using namespace engine;
using namespace state;
using namespace std;

//Constructor

RechargeCommand::RechargeCommand (std::shared_ptr<Fighter> fighter):fighter(fighter)
{

}
//Functions
void RechargeCommand::execute (state::State& state){
    float oldMana=fighter->getMana();
    
    
    if(fighter->getStatus()!=DEAD){
  
        //cout<<"Recharge is coming!!"<<endl;
    
		string entityNameRecharging = "";
		switch(fighter->getName()){
			case Flint: 
				entityNameRecharging = "Flint";
            break;
			case Kuro:
				entityNameRecharging = "Kuro";
            break;
			case Thork:
				entityNameRecharging = "Thork";
            break;
			case Seku:
				entityNameRecharging = "Seku";
            break;       
        }
        fighter->recharge();
        
        cout << "This fighter " << entityNameRecharging << " is recharging " << endl;

        cout<<"This fighter had "<<oldMana <<" mana points"<<endl;
        cout<<"this fighter has now "<<fighter->getMana()<<" mana points."<<endl;

        fighter->setHealthPoints(fighter->getMana());
        //fighter->setStatus(WAITING);

    }
    else if(fighter->getStatus()==DEAD){
        cout<<"Already dead!"<<endl;
    }
}
