#include "Engine.h"
#include "../engine.h"
#include <iostream>
#include <unistd.h>
#include "../state.h"

using namespace std;
using namespace engine;
using namespace state;


Engine::Engine () : currentState(){
	changeRound = true;
}



Engine::~Engine()
{
   
}

State& Engine::getState()
{
    return currentState;
}

void Engine::addCommand(int priority, std::unique_ptr<Command> ptr_cmd)
{
    currentCommands[priority] = move(ptr_cmd);
}

void Engine::update()
{
	//cout << "in update" <<endl;
    StateEvent stateEvent(FIGHTERCHANGED);
    //cout << "stateEvent ok"<< endl;

	map<int, std::unique_ptr<Command>>::iterator it;
	//cout << "command ok" << endl;
    // Execute each command of the currentCommandss table
	for(size_t i=0; i<currentCommands.size(); i++){
		//cout << "inside loop" << endl;
		currentCommands[i]->execute(currentState);
		//cout << "execution done" << endl;
		currentState.notifyObservers(stateEvent, currentState); // Notify the state which will notify render
		//cout << "notify ok!" <<endl;
		sleep(2);
		
	}

    // Erase all the commands which were executed
	currentCommands.clear();
	//cout << "command are empty" <<endl;

}

bool Engine::checkGameEnd(){
	bool gameEnd = true;

	// For each player
	for (unsigned int i = 0; i < currentState.getPlayerList().size(); i++){
		// For each Fighter belonging to each player	
			// As long as another player has his Fighter alive the game isn't finished
			if(currentState.getPlayerList()[i]->getFighter()->getStatus()==DEAD){

				cout<<"The player "<< currentState.getPlayerList()[i]->getPlayerName()<<" lost the game!!!"<<endl;
				gameEnd=false;
			}
	}
	return gameEnd;
}

void Engine::screenRefresh(){
	StateEvent stateEvent(PLAYERCHANGED);
	currentState.notifyObservers(stateEvent, currentState); // Notify the state which will notify render
}

bool Engine::checkRoundEnd(){
	bool playerChange = true;
	bool roundChange = true;
	bool gameEnd = true;
	int currentPlayerID;

	if(playerChange && roundChange)
	{
		currentPlayerID=currentState.getCurrentPlayerID();
		currentState.setCurrentPlayerID(currentPlayerID);
		cout << "The player 0   " << currentPlayerID << " playing."<< endl;
		playerChange = false;
		roundChange = false;
		gameEnd = false;
		
	}
	else if(playerChange && !roundChange){
		currentPlayerID=currentState.getCurrentPlayerID();
		currentState.setCurrentPlayerID(!currentPlayerID);
		cout << "The player   " << currentPlayerID << " playing."<< endl;

	}
	if(gameEnd){
		cout << "End of the game !" << endl;
		for (unsigned int i = 0; i < currentState.getPlayerList().size(); i++){
			if (currentState.getPlayerList()[i]->getFighter()->getHealthPoints() == 0){
				cout<<"The player "<< currentState.getPlayerList()[i]->getPlayerName()<<" lost the game!!!"<<endl;
			}
		}
	}
	
	return roundChange;
}

void Engine::checkRoundStart(){
	if (changeRound == true){
	
		// Change the current player
		currentState.setCurrentPlayerID(0);//Reset player ID to "0"=> first player
		cout << "\t\t--- Round " << currentState.getRound() << " ---\n" << endl;
		
		// For each player
		for (unsigned int i = 0; i < currentState.getPlayerList().size(); i++){
				// For all Fighter which do not belong to the currentPlayer and which are not DEAD
				if (currentState.getPlayerList()[i]->getFighter()->getStatus()!= DEAD ){
					// Reset Status to Available
					currentState.getPlayerList()[i]->getFighter()->setStatus(WAITING);
	
			}
		}
		changeRound = !changeRound;
	}
}

bool Engine::getChangeRound (){
	return changeRound;
}

bool Engine::getStop (){
	return stop;
}

void Engine::setCurrentState (state::State state){
	cout << "currentState" << endl;
	state.setCurrentPlayerID(this->currentState.getCurrentPlayerID());
	// state.
	// this->currentState.getPlayerList() = state.getPlayerList();
	// this->currentState.getPlayerList()[0]->getFighter() = state.getPlayerList()[0]->getFighter();
	// this->currentState.getPlayerList()[1]->getFighter() = state.getPlayerList()[1]->getFighter();
	
	cout << "currentState ok" << endl;
}

void Engine::setCurrentCommands (std::map<int,std::unique_ptr<Command>> currentCommands){
	this->currentCommands=move(currentCommands);
}

void Engine::setChangeRound (bool changeRound){
	this->changeRound=changeRound;
}

void Engine::setStop (bool stop){
	this->stop=stop;
}

std::map<int, std::unique_ptr<Command>>&  Engine::getCurrentCommands ()
{
	return currentCommands;
}

std::shared_ptr<Engine> Engine::copy()
{
	std::shared_ptr<Engine> engine = std::make_shared<Engine>();
	currentState= engine->getState().copy();
	//result->getStop() = stop;
	return engine;
}
