#include "State.h"
#include "memory.h"
#include <memory>
#include <iostream>
#include "Fighter.h"
#include "MoveArray.h"

using namespace std;
using namespace state;




State::State(){
    level = 1;
    round = 1;
    currentPlayerID = 1;
    std::shared_ptr<MoveArray> mapArray;
    moveArray = mapArray;
    endFight=false;
}

Terrain State::getTerrain()
{
    return terrain;
}

void State::setTerrain(Terrain terrain)
{
    this-> terrain = terrain;
}

int State::getRound(){
    return round;
}

void State::setRound(int round){
    this->round = round;
}

int State::getLevel(){
    return level;
}

void State::setLevel(int level){
    this->level = level;
}

bool State::initPlayers(){

    //Associate a fighter to a player
    //pointers are life!!!  <3 :) 03/12/2019
    //Player 1
    
    shared_ptr<Player> ptrPlayer1(new Player(0));
    shared_ptr<Fighter> ptrFighter1(new Fighter(Thork, ptrPlayer1->getID(), AVAILABLE,100, 100, 50,0, COUPDEPOING,100));
    ptrPlayer1->setFighter(ptrFighter1);

    shared_ptr<Position> position1(new Position(50.f,250.f));
    ptrPlayer1->getFighter()->setPosition(position1);

    playerList.push_back(ptrPlayer1);


    shared_ptr<Player> ptrPlayer2(new Player(1));
    shared_ptr<Fighter> ptrFighter2(new Fighter(Flint, ptrPlayer2->getID(), AVAILABLE,100, 100, 50,0, COUPDEPOING,100));
    ptrPlayer2->setFighter(ptrFighter2);

    shared_ptr<Position> position2(new Position(500.f,250.f));
    ptrPlayer2->getFighter()->setPosition(position2);


    playerList.push_back(ptrPlayer2);
   
    return true;
}

std::vector<std::shared_ptr<Player>> State::getPlayerList () //tableau de ref vers les players
{
    return playerList;
}

bool State::getEndFight()
{
    return endFight;
}

void State::setCurrentPlayerID(int currentPlayerID)
{
    this->currentPlayerID = currentPlayerID;
}

int State::getCurrentPlayerID()
{
    return currentPlayerID;
}


std::shared_ptr<MoveArray> State::getMoveArray()
{
    return moveArray;
}

State State::copy()
{
    State result = State(*this);
    for (auto& p : playerList)
    {
        result.playerList.push_back(p->copy());
    }

    return result;
}

State::~State(){
    
}

