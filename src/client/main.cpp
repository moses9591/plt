#include "state.h"
#include "render.h"
#include "engine.h"
#include "unistd.h"
#include "ai.h"
#include "client.h"


#include "string.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <iostream>
#include <thread>
#include <mutex>


using namespace std;
using namespace state;
using namespace render;
using namespace engine;
using namespace ai;
using namespace client;



// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne


void handleInputs(sf::RenderWindow &window,  std::shared_ptr<Engine> engine);
bool iaTurn = false;


int main(int argc, char *argv[])
{

    if (argc > 1)
    {
        if (strcmp(argv[1], "hello") == 0)
        {
            cout << "Bonjour " << ((argv[2]) ? argv[2] : "tout le monde") << endl;
        }
        if (strcmp(argv[1], "testSFML") == 0)
        {
            cout << "this is the test lab" <<endl;
            sf::Texture arena;
            sf::Sprite arenaSprite;
            // int frame = 0;
            // int row = 1;
           // int frameCounter = 0;

            //float deltaTime = 0.0f;
            sf::Clock clock;
            cout << "test sfml" << endl;

            if (!arena.loadFromFile("./res/Terrains/seku_terrain.png"))
            {
                std::cout << "Load Failed" << std::endl;
                system("Pause");
            }
            
            arenaSprite.setTexture(arena);

            //display fighter1
            sf::Texture spriteSheet;
            
            if (!spriteSheet.loadFromFile("./res/Fighters/Kuro.png")) //,rectSourceSprite));
            {
                std::cout << "Load Failed" << std::endl;
                system("Pause");
            }
            sf::Sprite playerSprite;
            playerSprite.setTexture(spriteSheet);
            // put fighter on the right of the arena
            playerSprite.setPosition(sf::Vector2f(50.f, 250.f));

            //display fighter2
            sf::Texture spriteSheet2;
            sf::IntRect rectSourceSprite1(0, 0, 100, 100);
            if (!spriteSheet2.loadFromFile("./res/Fighters/Flint.png", rectSourceSprite1))
            {
                std::cout << "Load Failed" << std::endl;
                system("Pause");
            }
            sf::Sprite grid[3][1];
            grid[0][1].setTexture(spriteSheet);
            // float x;
            // float y;
            
            // grid[0][1].setPosition(x, y);
            grid[0][1].setTextureRect(sf::IntRect(0,0, 100,100));
            
            grid[1][1].setTexture(spriteSheet2);
            grid[1][1].setPosition(sf::Vector2f(500.f, 250.f));
            grid[1][1].setTextureRect(sf::IntRect(0,0, 100,100));
            

            sf::Sprite playerSprite2;
            
            playerSprite2.setTexture(spriteSheet2);
            // // put fighter on the left of the arena
            playerSprite2.setPosition(sf::Vector2f(500.f, 250.f));

            
            //size of image as input of VideoMode
            sf::VideoMode resolution;

            sf::RenderWindow window(sf::VideoMode(640, 384), "SFML works!", sf::Style::Default);

            while (window.isOpen())
            {
               // deltaTime = clock.restart().asSeconds();

                sf::Event event;
                sf::Font font;
                if (!font.loadFromFile("./res/Fonts/FontFile.ttf"))
                {
                    return false;
                }
                sf::Text text1;
                text1.setFont(font);
                text1.setString("Health Points");
                text1.setCharacterSize(40);

                sf::Text text2;
                text2.setFont(font);
                text2.setString("Health Points");
                text2.setCharacterSize(40);
                text2.setPosition(530.f, 0.f);

                sf::Texture hpBarTexture;
                if (!hpBarTexture.loadFromFile("./res/redBg.jpg", sf::IntRect(0, 0, 100, 10)))
                {
                    return false;
                }

                State state;
                sf::Sprite hpBarP1;
                hpBarP1.setTexture(hpBarTexture);
                hpBarP1.setPosition(0.f, 40.f);

                sf::Sprite hpBarP2;
                hpBarP2.setTexture(hpBarTexture);
                hpBarP2.setPosition(530.f, 40.f);
                bool attackPress = false;
                
                while (window.pollEvent(event))
                {
                    switch (event.type)
                    {
                    case sf::Event::Closed:
                        window.close();
                        break;
                    case sf::Event::KeyPressed:
                        switch (event.key.code)
                        {
                        case sf::Keyboard::A:
                            cout << " touche A ENCLENCHE" << endl;
                            attackPress = true;
                            break;
                        default:
                            state.notifyObservers(StateEventID::ALLCHANGED, state);
                            break;
                        }
                        break;
                    case sf::Event::MouseMoved:
                        break;
                    default:
                        state.notifyObservers({StateEventID::ALLCHANGED}, state);
                        break;
                    }
                }

                if(attackPress)
                {

                    grid[0][1].move(385,0);
                    grid[0][1].move(50,0);

                }


                sf::Clock clock;

                window.clear();

                window.draw(arenaSprite);
                window.draw(text1);
                window.draw(text2);
                window.draw(hpBarP1);
                window.draw(hpBarP2);
                // window.draw(playerSprite);
                // window.draw(playerSprite2);
                cout << "ok" << endl;
                //for(int i = 1; i < 3; i++)
                window.draw(grid[0][1]);
                window.draw(grid[1][1]);
                // window.draw(grid[5][1]);

                window.display();
            }

            // Fin test SFML
        }
        else if (strcmp(argv[1], "render") == 0)
        {
            RenderClient renderClient;
            renderClient.runRender();
        }
    
        else if (strcmp(argv[1], "engine") == 0)
        {
            EngineClient engineClient;
            engineClient.runEngine();
            
        }
        else if (strcmp(argv[1], "random_ai") == 0)
        {    
            cout << "--------------------random ai-------------------" << endl;
            sf::RenderWindow window(sf::VideoMode(640, 384), "Fighter Zone");


            std::shared_ptr<Engine> engine = make_shared<Engine>();

            engine->getState().setTerrain(SekuTerrain);
            engine->getState().initPlayers(); //getting the state by using engine
            engine->getState().setRound(1);

            
            //Client Side (Render)
            StateLayer stateLayer(window, engine->getState());
            engine->getState().registerObserver(&stateLayer);
            
            TextureManager *textureManager = textureManager->getInstance();
            if (textureManager->load())
            {
                cout << "texuture manager ok!\n" << endl;
            }
            else
            {
                cout << "texuture manager loading failed!" << endl;
                return EXIT_FAILURE;
            }
            stateLayer.draw();         
           
            while (window.isOpen()) {
                if(!iaTurn){
                    // Manage user inputs
                    handleInputs(window,engine);
                    if(engine->checkGameEnd()==0){
                        window.close();
                        cout<<"Game Over"<<endl;
                        break;
                    }
                    
                } else {
                    cout << "run ai" << endl;
                    RandomAI randomAi(0); //AiID == 0
                    randomAi.run(engine);
                    iaTurn =false;
                }
            }
            
        }else if(strcmp(argv[1], "heuristic_ai") == 0)
        {
            cout << "--------------------heuristic_ai-------------------" << endl;
            sf::RenderWindow window(sf::VideoMode(640, 384), "Fighter Zone");


            std::shared_ptr<Engine> engine = make_shared<Engine>();

            
            engine->getState().setTerrain(SekuTerrain);
            engine->getState().initPlayers(); //getting the state by using engine
            engine->getState().setRound(1);

            
            //Client Side (Render)
            StateLayer stateLayer(window, engine->getState());
            engine->getState().registerObserver(&stateLayer);
            
            TextureManager *textureManager = textureManager->getInstance();
            if (textureManager->load())
            {
                cout << "texuture manager ok!\n" << endl;
            }
            else
            {
                cout << "texuture manager loading failed!" << endl;
                return EXIT_FAILURE;
            }
            stateLayer.draw();
           
           
            while (window.isOpen()) {
                if(!iaTurn){
                    // Manage user inputs
                    handleInputs(window,engine);
                    if(engine->checkGameEnd()==0){
                        window.close();
                        cout<<"Game Over"<<endl;
                        break;
                    }
                    
                } else {
                    cout << "run ai" << endl;
                    HeuristicAI heuristicAi(0); //AiID == 0
                    heuristicAi.run(engine);
                    iaTurn =false;
                }
            }
        } else if(strcmp(argv[1], "deep_ai") == 0)
        {
            cout << "--------------------deep_ai-------------------" << endl;
            sf::RenderWindow window(sf::VideoMode(640, 384), "Fighter Zone");


            std::shared_ptr<Engine> engine = make_shared<Engine>();

            engine->getState().setTerrain(KuroTerrain);
            engine->getState().initPlayers(); //getting the state by using engine
            engine->getState().setRound(1);

            
            //Client Side (Render)
            StateLayer stateLayer(window, engine->getState());
            engine->getState().registerObserver(&stateLayer);
            
            TextureManager *textureManager = textureManager->getInstance();
            if (textureManager->load())
            {
                cout << "texuture manager ok!\n" << endl;
            }
            else
            {
                cout << "texuture manager loading failed!" << endl;
                return EXIT_FAILURE;
            }
            stateLayer.draw();

            cout << " User plays first" << endl;
            cout << "Use the following rules to play." << endl;
            cout << "A : Attack, R: Recharge mana, D: Defend" << endl;
            cout << "Press T : Turn Over, IA plays" << endl;
           
           
            while (window.isOpen()) {
                if(!iaTurn){
                    // Manage user inputs
                    handleInputs(window,engine);
                    if(engine->checkGameEnd()==0){
                        window.close();
                        cout<<"Game Over"<<endl;
                        break;
                    }
                    
                } else {
                    cout << "run ai" << endl;
                    DeepAI deepAI(0); //AiID == 0
                    deepAI.run(engine);
                    iaTurn =false;
                }
            }
        }else if(strcmp(argv[1], "demo") == 0)
        {
            cout << "------------------demo_ai-------------------" << endl;
            sf::RenderWindow window(sf::VideoMode(640, 384), "Fighter Zone");


            std::shared_ptr<Engine> engine = make_shared<Engine>();

            engine->getState().setTerrain(KuroTerrain);
            engine->getState().initPlayers(); //getting the state by using engine
            engine->getState().setRound(1);

            
            //Client Side (Render)
            StateLayer stateLayer(window, engine->getState());
            engine->getState().registerObserver(&stateLayer);
            
            TextureManager *textureManager = textureManager->getInstance();
            if (textureManager->load( ))
            {
                cout << "texuture manager ok!\n" << endl;
            }
            else
            {
                cout << "texuture manager loading failed!" << endl;
                return EXIT_FAILURE;
            }
            stateLayer.draw();

            cout << " Random_ai vs Heurestic_ai" << endl;
            
            //bool randomTurn = false;
            while (window.isOpen()) {
                if(!iaTurn){
                    // Manage user inputs
                    cout << "------------random ai turn------------" << endl;
                    RandomAI randomAI(1); 
                    randomAI.run(engine);
                    iaTurn = true;
                    if(engine->checkGameEnd()==0){
                        window.close();
                        cout<<"Game Over"<<endl;
                        break;
                    }
                } else {
                    cout << "-------heuristic ai turn------------ " << endl;
                    HeuristicAI heuristicAI(0);
                    heuristicAI.run(engine);
                    iaTurn = false;
                    if(engine->checkGameEnd()==0){
                        window.close();
                        cout<<"Game Over"<<endl;
                        break;
                    }
                }
            }
        }else if(strcmp(argv[1], "thread") == 0)
        {
            Modularisation modularisation;
            modularisation.run();
        }else if(strcmp(argv[1], "record") == 0)
        {
            Modularisation modularisation;
            modularisation.record();
        }else if(strcmp(argv[1], "play") == 0)
        {
            Modularisation modularisation;
            modularisation.play();
        }
    }
}

void handleInputs(sf::RenderWindow &window,  std::shared_ptr<Engine> engine){
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
                    iaTurn = true;
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