#include "ChangeRound.h"
#include <iostream>
#include <unistd.h>
#include <stdlib.h>

using namespace std;
using namespace engine;
using namespace state;


ChangeRound::ChangeRound(std::shared_ptr<Fighter> currentFighter):currentFighter(currentFighter)
{

}

void ChangeRound::execute(State& state)
{
    int waitingTime=40000;
    string fighterName = "";
    switch(currentFighter->getName()){
        case Thork: 
            fighterName = "Thork";
            break;
        case Flint:
            fighterName = "Flint";
            break;
        case Seku:
            fighterName = "Seku";
            break;
        case Kuro:
            fighterName = "Kuro";
            break;
    }
    
	if (currentFighter->getStatus()==WAITING && currentFighter->getStatus()!=DEAD){
		currentFighter->setStatus(WAITING);
		cout << fighterName << " finished his round.\n" << endl;
        usleep(waitingTime);
	}
    if(state.getCurrentPlayerID() == 1)
    {   
        cout<<"player 0 turn" <<endl;
        state.setCurrentPlayerID(0);
    }
    else if(state.getCurrentPlayerID() == 0)
    {
        cout<<"player 1 turn" <<endl;
        state.setCurrentPlayerID(1);
    }
}