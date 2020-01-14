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
                cout << fighter->getX() <<endl;
                fighter->setX(destination->getX()-50);
                //fighter->setY(100); 
                vector<shared_ptr<Player>> playerList = state.getPlayerList();
                Player player = *state.getPlayerList()[0].get();
                player.setFighter(fighter);
                playerList[0] = make_shared<Player>(player);
                state.setPlayerList(playerList);
            }
        }
}

Json::Value MoveCommand::serialize()
{
	Json::Value newCommand;	
	newCommand["idPlayer"] = id;
    newCommand["CommandTypeId"] = 5;
    newCommand["Destination"] = destination->getX();
	
	return newCommand;
}












