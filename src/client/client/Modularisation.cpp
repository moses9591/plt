#include "Modularisation.h"
#include "../render.h"
#include "../client.h"
#include "ai.h"
#include "engine.h"
#include "state.h"

#include <unistd.h>
#include <thread>
#include <mutex>


#include <fstream>
#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>

using namespace std;
using namespace client;
using namespace state;
using namespace render;
using namespace engine;
using namespace ai;


bool iaTurn1 = false;
void handleInputs1(sf::RenderWindow &window,  std::shared_ptr<Engine> engine);

//Constructor
Modularisation::Modularisation(){
    State state;
    state.setTerrain(SekuTerrain);
    state.initPlayers();
    state.setRound(1);
    engine = make_shared<Engine>(state);
}

/**run for the thread test
 * 
 * 
 */
void Modularisation::run(){
    cout<<"---- THREAD TEST ----"<<endl;

    //Launch engine in another thread
    
    std::thread t1(&Modularisation::clientThread,this);
    //cout << "t1 ok " << endl;
    std::thread t2(&Modularisation::engineThread,this);
    //cout << "t2 ok " << endl;
    t1.join();
    //cout << "t1 join " << endl;
    t2.join();
    //cout << "t2 join " << endl;
}

/**
 * 
 * 
 */
void Modularisation::engineThread(){
    
    engine->getState().initPlayers();
    //cout << "players ok" << endl;
}

/**
 * 
 * 
 */
void Modularisation::clientThread()
{
    cout<<"--- Moteur du jeu ---"<<endl;

    //Initialize the window
    sf::RenderWindow window(sf::VideoMode(640, 384), "Fighter Zone!");

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
    
    StateLayer stateLayer(window, engine->getState());
    engine->getState().registerObserver(&stateLayer);

    stateLayer.draw();
    // bool iaTurn = false;
    while (window.isOpen()) {
        if(!iaTurn1){
            // Manage user inputs
            handleInputs1(window, engine);
            
            // cout << "------------random ai turn------------" << endl;
            // RandomAI randomAI(1); 
            // randomAI.run(engine);
            // iaTurn = true;
            if(engine->checkGameEnd()==0){
                window.close();
                cout<<"Game Over"<<endl;
                break;
            }
        } else {
            cout << "-------heuristic ai turn------------ " << endl;
            HeuristicAI heuristicAI(0);
            heuristicAI.run(engine);
            iaTurn1 = false;
            if(engine->checkGameEnd()==0){
                window.close();
                cout<<"Game Over"<<endl;
                break;
            }
        }
    }
    
}

//Run for the record test
void Modularisation::record(){
    cout<<"---- recording----"<<endl;

    //Launch engine in another thread
    std::thread t1(&Modularisation::engineThread,this);
    std::thread t2(&Modularisation::clientThread,this);

    t1.join();
    t2.join();

    Json::FastWriter fastWriter;
    std::string output = fastWriter.write(engine->getRecord());
    cout << "fastWriter ok" << endl;
    ofstream recordFile("record.txt");
    if(recordFile){
        cout<<"Recording file opened with success"<<endl;
        recordFile<<output<<endl;
    }else{
        cout<<"Recording file opening failed"<<endl;
    }
}

//Run to play the .txt file
void Modularisation::play(){
    cout << "---- PLAY TEST ----\n" << endl;

	std::string commandsFile = "record.txt";
								
    //Initialize the window
    sf::RenderWindow window(sf::VideoMode(640, 384), "Fighter Zone");
    //Engine Thread
    std::thread t1(&Modularisation::engineThread,this);
    t1.join();

    //Client Side (Render)
    engine->getState().setTerrain(SekuTerrain);
    cout << "terrain ok" << endl;
   
    engine->getState().setRound(1);
    
    //registering statelayer to observer
    StateLayer stateLayer(window, engine->getState());
    engine->getState().registerObserver(&stateLayer);

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

    stateLayer.draw();

    while (window.isOpen()){
        while (1)
        {
            engine->replayCommands(commandsFile);
        }
    }		
}



void handleInputs1(sf::RenderWindow &window,  std::shared_ptr<Engine> engine){
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
                    iaTurn1 = true;
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




