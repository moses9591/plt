#include "MoveCommand.h"
#include "../engine.h"
#include "../state.h"
#include <iostream> 
#include <unistd.h>
#include <stdlib.h>


using namespace engine;
using namespace state;
using namespace std;


MoveCommand:: MoveCommand (std::shared_ptr<state::Fighter> fighter, std::shared_ptr<state::Position> destination):fighter(fighter),destination(destination)
{
    id = JSON_MOVE;
}

void MoveCommand::execute (state::State& state)
{
    bool moveFeasible = true;
    
        if(fighter->getStatus() != DEAD)
        {
            if(moveFeasible){
                fighter->setX(destination->getX());
                fighter->setY(destination->getY()); 
            }
        }
}

Json::Value MoveCommand::serialize()
{
	Json::Value newCommand;	
	newCommand["id"] = id;
	
	return newCommand;
}












