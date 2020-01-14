#include "../engine.h"
#include "../state.h"
#include <iostream> 
#include <unistd.h>
#include <stdlib.h>
#include "AttackCommand.h"

using namespace engine;
using namespace state;
using namespace std;


//Contructor
AttackCommand::AttackCommand (std::shared_ptr<Fighter> attacker, std::shared_ptr<Fighter> target):attacker(attacker),target(target)
{
    id = JSON_ATTACK;
}

//Functions

void AttackCommand::execute (state::State& state){
    //cout << "execution is coming" << endl;

  
    int waitingTime = 5;
    
    if(attacker->getStatus()!=DEAD){
        float oldTargetHealth=target->getHealthPoints();
       
       
        //Fighting
        attacker->fight(target, COUPDEPOING);
        
      
        
        string attackerName = "";
        string targetName = "";

        switch(attacker->getName()){
            case Flint: 
                attackerName = "Flint";
            break;
            case Kuro:
                attackerName = "Kuro";
            break;
            case Thork:
                attackerName = "Thork";
            break;
            case Seku:
                attackerName = "Seku";
            break;       
        }

        switch(target->getName()){
            case Flint: 
                targetName = "Flint";
            break;
            case Kuro:
                targetName = "Kuro";
            break;
            case Thork:
                targetName = "Thork";
            break;
            case Seku:
                targetName = "Seku";
            break;       
        }

        cout << attackerName << " is attacking " << targetName << "." << endl;
        cout<< targetName << " had "<<oldTargetHealth<<" health points."<<endl;
        if(target->getHealthPoints()<=0){
            target->setStatus(DEAD);
            target->setHealthPoints(0);
            // animation dead
            cout<< targetName<< " has " << target->getHealthPoints() <<" now health points."<<endl;
            cout << "The opponent is dead. You win! " << endl;
            sleep(2);
            
            
        }
        
        cout<< targetName<< " has " << target->getHealthPoints() <<" health points now."<<endl;

        //target->setHealthPoints(target->getHealthPoints());
  
    }
    else if(attacker->getStatus()==DEAD){
        cout<<"Already dead!"<<endl;
    }else if(attacker->getStatus()==WAITING){
        string attackerName = "";
        switch(attacker->getName()){
            case Flint: 
                attackerName = "Flint";
            break;
            case Kuro:
                attackerName = "Kuro";
            break;
            case Thork:
                attackerName = "Thork";
            break;
            case Seku:
                attackerName = "Seku";
            break;       
        }
        cout<< attackerName << " cannot attack because his turn already ended.\n" << endl;
        usleep(waitingTime);
    }
   
}

Json::Value AttackCommand::serialize()
{
	Json::Value newCommand;
	newCommand["idPlayer"] = attacker->getPlayerID();
    newCommand["CommandTypeId"] = 1;   
	
	return newCommand;
}
