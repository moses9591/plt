#include "Engine.h"
#include "../engine.h"
#include <unistd.h>
#include "../state.h"
#include "../../../extern/jsoncpp-1.8.0/jsoncpp.cpp"

#include <iostream>
#include <fstream>

using namespace std;
using namespace engine;
using namespace state;


Engine::Engine (state::State state)
{
	
	this->currentState = std::move(state);
	changeRound = true;
	record["size"] = 0;
	record["tabCommand"][0] = "";
}

Engine::Engine ()
{

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
	Json::Value newCommand = ptr_cmd->serialize();
	record["tabCommand"][record["size"].asUInt()] = newCommand;
	record["size"] = record["size"].asUInt() + 1;

    currentCommands[priority] = move(ptr_cmd);
}

Json::Value Engine::getRecord()
{
	return record;
}


void Engine::replayCommands(std::string fileName){
	cout << "Replay is starting" << endl;

	// Opening the .txt file
	ifstream commandsFile(fileName);
	if (commandsFile){
		Json::Value root;
		Json::Reader reader;
		if(!reader.parse(commandsFile, root)){
			cout 	<< "Failed to parse commands\n" << reader.getFormattedErrorMessages();
		}
		// Closing the file in reading mode
		commandsFile.close();
						
		cout << "Size of the commands table of "<< fileName << " : " << root["tabCommand"].size() << endl;
						
		// Converting commands from Json to objects
		for (unsigned int i = 0; i < root["tabCommand"].size(); i++){
			// Move case
			

			// Attack case
			if(root["tabCommand"][i]["id"].asUInt() == 1){
				AttackCommand attackCommand(currentState.getPlayerList()[0]->getFighter(),currentState.getPlayerList()[1]->getFighter());				
				unique_ptr<Command> ptr_attack (new AttackCommand(attackCommand));
				addCommand(0, move(ptr_attack));

				// ChangeRound changeround(currentState.getPlayerList()[0]->getFighter());
				// unique_ptr<Command> ptr_endEntityRound (new ChangeRound(changeround));
				// addCommand(1, move(ptr_endEntityRound));

				update();

			}
			//Defense case 
			else if(root["tabCommand"][i]["id"].asUInt() == 2){
				DefenseCommand defenseCommand(currentState.getPlayerList()[0]
                                                        ->getFighter());
				unique_ptr<Command> ptr_defense (new DefenseCommand(defenseCommand));
				addCommand(0, move(ptr_defense));

				// ChangeRound changeround(currentState.getPlayerList()[0]->getFighter());
				// unique_ptr<Command> ptr_endEntityRound (new ChangeRound(changeround));
				// addCommand(1, move(ptr_endEntityRound));

				update();
			}
			//recharge case
			else if(root["tabCommand"][i]["id"].asUInt() == 3){
				RechargeCommand rechargeCommand(currentState.getPlayerList()[0]->getFighter());
				unique_ptr<Command> ptr_recharge (new RechargeCommand(rechargeCommand));
				addCommand(0, move(ptr_recharge));

				// ChangeRound changeround(currentState.getPlayerList()[0]->getFighter());
				// unique_ptr<Command> ptr_endEntityRound (new ChangeRound(changeround));
				// addCommand(1, move(ptr_endEntityRound));

				update();
			}
			// End entity round case
			else if(root["tabCommand"][i]["id"].asUInt() == 3){
				ChangeRound changeround(currentState.getPlayerList()[0]->getFighter());
					
				unique_ptr<Command> ptr_endEntityRound (new ChangeRound(changeround));
				addCommand(0, move(ptr_endEntityRound));
				update();

			}
			else{
				cout << "The command " << i << " is unknown" << endl;
			}
			usleep(500000);						
		}								
	}				
	else{
		cerr << "Unable to open the commands file (read)" << endl;
	}							
	cout << "The replay has ended" << endl;
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
	bool gameEnd = 1;

	// For each player
	for (unsigned int i = 0; i < currentState.getPlayerList().size(); i++){
		// For each Fighter belonging to each player	
			// As long as another player has his Fighter alive the game isn't finished
			if(currentState.getPlayerList()[i]->getFighter()->getStatus()!=DEAD){

				//cout<<"The player "<< currentState.getPlayerList()[i]->getPlayerName()<<" still alive!!!"<<endl;
				gameEnd=1;
			}
			if(currentState.getPlayerList()[0]->getFighter()->getHealthPoints() ==0
			 || currentState.getPlayerList()[1]->getFighter()->getHealthPoints() ==0 )
			{
				gameEnd = 0;
			}
	}
	return gameEnd;
}

void Engine::screenRefresh()
{
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

// std::shared_ptr<Engine> Engine::copy()
// {
// 	std::shared_ptr<Engine> engine = std::make_shared<Engine>();
// 	currentState= engine->getState().copy();
// 	//result->getStop() = stop;
// 	return engine;
// }
