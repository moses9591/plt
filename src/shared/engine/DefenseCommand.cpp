#include "../engine.h"
#include "../state.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "DefenseCommand.h"

using namespace std;
using namespace engine;
using namespace state;

//Constructor

DefenseCommand::DefenseCommand(std::shared_ptr<Fighter> isDefending) : isDefending(isDefending)
{
    id = JSON_DEFENSE;
}
//Functions
void DefenseCommand::execute(state::State &state)
{
    int waitingTime = 4;
    if(isDefending->getStatus() != DEAD)
    {
        //cout << "Defense is coming!!" << endl;
        isDefending->defend();

        string defenderName = "";
        switch(isDefending->getName())
        {
            case Flint: 
                defenderName = "Flint";
                break;
            case Kuro:
                defenderName = "Kuro";
                break;
            case Thork:
                defenderName = "Thork";
                break;
            case Seku:
                defenderName = "Seku";
                break;   
        }


        string defenderStatus = "";
        switch(isDefending->getStatus())
        {
            case DEFENSE: 
                defenderStatus = "DEFENSE";
                break;
            case WAITING:
                defenderStatus = "WAITING";
                break;
            case DEAD:
                defenderStatus = "DEAD";
                break;
            case RECHARGE:
                defenderStatus = "RECHARGE";
            case ATTACK:
                defenderStatus = "ATTACK";
                break;   
            default:
                break;
        }

        cout << defenderName << " status is "<< defenderStatus << endl; 
    }
    else if(isDefending->getStatus()==DEAD){
        cout<<"Already dead!"<<endl;
    }
    usleep(waitingTime);
    
}

Json::Value DefenseCommand::serialize()
{
	Json::Value newCommand;	
	newCommand["id"] = id;
    newCommand["CommandTypeId"] = 2;
	
	return newCommand;
}