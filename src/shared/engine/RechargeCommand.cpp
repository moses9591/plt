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
    id = JSON_RECHARGE;
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
        
        cout << entityNameRecharging << " is recharging " << endl;

        cout<<entityNameRecharging << " had " << oldMana <<" mana points"<<endl;
        cout<<entityNameRecharging << " has now "<<fighter->getMana()<<" mana points."<<endl;

        fighter->setHealthPoints(fighter->getHealthPoints());

    }
    else if(fighter->getStatus()==DEAD){
        cout<<"Already dead!"<<endl;
    }
}

Json::Value RechargeCommand::serialize()
{
	Json::Value newCommand;	
	newCommand["id"] = fighter->getPlayerID();
    newCommand["CommandTypeId"] = 3;
	
	return newCommand;
}
