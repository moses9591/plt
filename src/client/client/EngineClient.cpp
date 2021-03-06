#include "../client.h"
#include "../render.h"
#include "../../shared/engine.h"

#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sstream>


using namespace std;
using namespace client;
using namespace state;
using namespace render;
using namespace engine;


void handleInputsClient(sf::RenderWindow &window,  std::shared_ptr<Engine> engine);
bool iaTurnClient;

EngineClient::EngineClient()
{

}

void EngineClient::runEngine()
{
    cout<<"--- Moteur du jeu ---"<<endl;
            
    State state;
    sf::RenderWindow window(sf::VideoMode(640, 384), "Fighter Zone");


    TextureManager *textureManager = textureManager->getInstance();
    if (textureManager->load())
    {
        cout << "texuture manager ok!" << endl;
    }
    else
    {
        cout << "texuture manager loading failed!" << endl;
        //return EXIT_FAILURE;
    }

    // //registering statelayer to observer
    
    state.setTerrain(SekuTerrain);
    state.initPlayers();
    state.setRound(1);
    std::shared_ptr<Engine> engine = make_shared<Engine>(state);
    
    StateLayer stateLayer(window, engine->getState());
    engine->getState().registerObserver(&stateLayer);

    stateLayer.draw();
    while (window.isOpen()){
        handleInputsClient(window,engine);
        //cout << engine->checkGameEnd() << endl;
    
        if(engine->checkGameEnd()==0){
            window.close();
            cout<<"Game Over"<<endl;
            break;
        }
    }

}

void handleInputsClient(sf::RenderWindow &window,  std::shared_ptr<Engine> engine){
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
                    iaTurnClient = true;
                }
                if(event.key.code == sf::Keyboard::A )
                {
                    if(engine->getState().getCurrentPlayerID()== 0)
                    {
                        std::cout << "-----------------Attack for player 1----------------" << std::endl;
                        AttackCommand attackCommand(engine->getState().getPlayerList()[0]->getFighter(), 
                                                    engine->getState().getPlayerList()[1]->getFighter());
                        unique_ptr<Command> ptr_attack (new AttackCommand(attackCommand));
                        engine->addCommand(0, move(ptr_attack));
                        engine->update();
                    }else if (engine->getState().getCurrentPlayerID()== 1)
                    {
                        std::cout << "-----------------Attack for player 2----------------"<< std::endl;
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
                        std::cout << "-----------------Recharge for player 1----------------"<< std::endl;
                        RechargeCommand rechargeCommand(engine->getState().getPlayerList()[engine->getState().getCurrentPlayerID()]
                                                        ->getFighter());
                        unique_ptr<Command> ptr_recharge (new RechargeCommand(rechargeCommand));
                        engine->addCommand(0, move(ptr_recharge));

                        engine->update();
                    }else if (engine->getState().getCurrentPlayerID()== 1)
                    {
                        std::cout << "-----------------Recharge for player 2----------------"<< std::endl;
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
                        std::cout << "-----------------Defense for player 1----------------"<< std::endl;
                        DefenseCommand defenseCommand(engine->getState().getPlayerList()[engine->getState().getCurrentPlayerID()]
                                                        ->getFighter());
                        unique_ptr<Command> ptr_defense (new DefenseCommand(defenseCommand));
                        engine->addCommand(0, move(ptr_defense));

                        engine->update();
                    }else if (engine->getState().getCurrentPlayerID()== 1)
                    {
                        std::cout << "-----------------Defense for player 2----------------"<< std::endl;
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
                        std::cout << "Move for player 0" << std::endl;
                        MoveCommand moveCommand(engine->getState().getPlayerList()[0]->getFighter(),
                                                engine->getState().getPlayerList()[0]->getFighter()->getPosition());
                        unique_ptr<Command> ptr_move (new MoveCommand(moveCommand));
                        engine->addCommand(0, move(ptr_move));

                        engine->update();
                    }else if (engine->getState().getCurrentPlayerID()== 1)
                    {
                        std::cout << "Move for player 0" << std::endl;
          
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