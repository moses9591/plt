#include "HandleInputs.h"
#include "../../shared/ai.h"
#include "../../shared/engine.h"

#include <unistd.h>


#include <fstream>
#include <iostream>
#include <sstream>


using namespace std;
using namespace client;
using namespace state;
using namespace engine;
using namespace ai;

bool ia= false;

HandleInputs::HandleInputs()
{
    
}

void HandleInputs::setIaTurn(bool iaTurn)
{
    this->iaTurn = iaTurn;
}

bool HandleInputs::getIaTurn()
{
    return iaTurn;
}

void HandleInputs::handleInputsClient(std::shared_ptr<Engine> engine, sf::RenderWindow &window)
{
    sf::Event event{};
    
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::T)
                {
                    std::cout << "the T key was pressed, next player!" << std::endl;
                    ChangeRound changeRound(engine->getState().getPlayerList()[0]->getFighter());
                    unique_ptr<Command> ptr_change (new ChangeRound(changeRound));
                    engine->addCommand(0, move(ptr_change));
                    engine->update();
                    ia = true;
                }
                if(event.key.code == sf::Keyboard::A )
                {
                    if(engine->getState().getCurrentPlayerID()== 0)
                    {
                        std::cout << "Attack is coming for player 0" << std::endl;
                        AttackCommand attackCommand(engine->getState().getPlayerList()[0]->getFighter(), 
                                                    engine->getState().getPlayerList()[1]->getFighter());
                        unique_ptr<Command> ptr_attack (new AttackCommand(attackCommand));
                        engine->addCommand(0, move(ptr_attack));
                        engine->update();
                    }else if (engine->getState().getCurrentPlayerID()== 1)
                    {
                        std::cout << "Attack is coming for player 1" << std::endl;
                        AttackCommand attackCommand(engine->getState().getPlayerList()[1]->getFighter(), 
                                                    engine->getState().getPlayerList()[0]->getFighter());
                        unique_ptr<Command> ptr_attack (new AttackCommand(attackCommand));
                        engine->addCommand(0, move(ptr_attack));

                        engine->update();
                    }
                }
                if(event.key.code == sf::Keyboard::R)
                {
                    if(engine->getState().getCurrentPlayerID()== 0)
                    {
                        std::cout << "recharging is coming for player 0" << std::endl;
                        RechargeCommand rechargeCommand(engine->getState().getPlayerList()[engine->getState().getCurrentPlayerID()]
                                                        ->getFighter());
                        unique_ptr<Command> ptr_recharge (new RechargeCommand(rechargeCommand));
                        engine->addCommand(0, move(ptr_recharge));

                        engine->update();
                    }else if (engine->getState().getCurrentPlayerID()== 1)
                    {
                       std::cout << "recharging is coming for player 1" << std::endl;
                        RechargeCommand rechargeCommand(engine->getState().getPlayerList()[engine->getState().getCurrentPlayerID()]
                                                        ->getFighter());
                        unique_ptr<Command> ptr_recharge (new RechargeCommand(rechargeCommand));
                        engine->addCommand(0, move(ptr_recharge));

                        engine->update();
                    
                    }
                }
                if(event.key.code == sf::Keyboard::D)
                {
                    if(engine->getState().getCurrentPlayerID()== 0)
                    {
                        std::cout << "Defense is coming for player 0" << std::endl;
                        DefenseCommand defenseCommand(engine->getState().getPlayerList()[engine->getState().getCurrentPlayerID()]
                                                        ->getFighter());
                        unique_ptr<Command> ptr_defense (new DefenseCommand(defenseCommand));
                        engine->addCommand(0, move(ptr_defense));

                        engine->update();
                    }else if (engine->getState().getCurrentPlayerID()== 1)
                    {
                        std::cout << "Defense is coming for player 1 " << std::endl;
                        DefenseCommand defenseCommand(engine->getState().getPlayerList()[engine->getState().getCurrentPlayerID()]
                                                        ->getFighter());
                        unique_ptr<Command> ptr_defense (new DefenseCommand(defenseCommand));
                        engine->addCommand(0, move(ptr_defense));

                        engine->update();
                    }       
                }
                if(event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right)
                {
                    if(engine->getState().getCurrentPlayerID()== 0)
                    {
                        // cout << "lancement commande movement" <<endl;
                        // State state = engine->getState();
                        // shared_ptr<Fighter> fighter = state.getPlayerList()[0]->getFighter();
                        // fighter->setX(400);
                        // fighter->setY(100); 
                        // vector<shared_ptr<Player>> playerList = state.getPlayerList();
                        // Player player = *state.getPlayerList()[0].get();
                        // player.setFighter(fighter);
                        // playerList[0] = make_shared<Player>(player);
                        // state.setPlayerList(playerList);
                        // engine->setCurrentState(state);
                        // StateEvent stateEvent(FIGHTERCHANGED);
                        // engine->getState().notifyObservers(stateEvent, engine->getState());

                        std::cout << "Movement is coming for player 0" << std::endl;
                        MoveCommand moveCommand(engine->getState().getPlayerList()[0]->getFighter(),
                                                engine->getState().getPlayerList()[0]->getFighter()->getPosition());
                        unique_ptr<Command> ptr_move (new MoveCommand(moveCommand));
                        engine->addCommand(0, move(ptr_move));

                        engine->update();
                    }else if (engine->getState().getCurrentPlayerID()== 1)
                    {

                        // cout << "lancement commande movement" <<endl;
                        // State state = engine->getState();
                        // shared_ptr<Fighter> fighter = state.getPlayerList()[0]->getFighter();
                        // //fighter->setPosition();
                        // fighter->setX(400);
                        // fighter->setY(100); 
                        // vector<shared_ptr<Player>> playerList = state.getPlayerList();
                        // Player player = *state.getPlayerList()[0].get();
                        // player.setFighter(fighter);
                        // playerList[0] = make_shared<Player>(player);
                        // state.setPlayerList(playerList);
                        // engine->setCurrentState(state);
                        // StateEvent stateEvent(FIGHTERCHANGED);
                        // engine->getState().notifyObservers(stateEvent, engine->getState());

                        std::cout << "Movement is coming for player 1" << std::endl;
                        MoveCommand moveCommand(engine->getState().getPlayerList()[0]->getFighter(),
                                                engine->getState().getPlayerList()[0]->getFighter()->getPosition());
                        unique_ptr<Command> ptr_move (new MoveCommand(moveCommand));
                        engine->addCommand(0, move(ptr_move));

                        engine->update();
                    }
                    
                }
            case sf::Event::MouseMoved:
                break;
            default:
                engine->getState().notifyObservers({StateEventID::ALLCHANGED}, engine->getState());
                break;            
        }
    }
}
