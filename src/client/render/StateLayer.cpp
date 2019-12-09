#include "StateLayer.h"
#include "../render.h"
#include <string>
#include <time.h>
#include "state.h"
#include <iostream>
#include "HealthBar.h"
#include "engine.h"


using namespace std;
using namespace render;
using namespace state;
using namespace engine;


StateLayer::StateLayer(sf::RenderWindow& window, const state::State& state): window(window)
{   
    this->state = state;
}

void StateLayer::draw()
{
    //cout << "enter in draw from statelayer" << endl;
    window.clear();

    background.draw(window, state);
    cout << "background ok" << endl;
    fighterRender1.draw(window,state.getPlayerList()[0]->getFighter()->getPosition()->getX(),state.getPlayerList()[0]->getFighter()->getPosition()->getY(),state.getPlayerList()[0]);// id = 0, 2
    cout << "fighterrenderok" << endl;          //  50,250
    fighterRender2.draw(window,state.getPlayerList()[1]->getFighter()->getPosition()->getX(), state.getPlayerList()[1]->getFighter()->getPosition()->getY(),state.getPlayerList()[1]);// id = 1, 3
    healthBar1.draw(window,state.getPlayerList()[0], 0.f, 40.f);
    cout << "hp 1" << endl; 
    healthBar2.draw(window,state.getPlayerList()[1], 440.f, 40.f);
     cout << "hp 2" << endl; 
   
                                // 500,250
    cout << "fighterrenderok 2" << endl; 
    //about the Font ...
    sf::Event event;
    sf::Font font;
    if(!font.loadFromFile("./res/Fonts/FontFile.ttf"))
    {
        std::cout << "Load Failed" << std::endl;
        system("Pause");
    }
    sf::Text text1;
    text1.setFont(font);
    FighterName name1 = state.getPlayerList()[0]->getFighter()->getName();
    string n;
    switch(name1)
    {
        case 0:
            n = "Kuro";
            break;
        case 1:
            n = "Flint";
            break;
        case 2:
            n = "Thork";
            break;
        case 3:
            n = "Seku";
            break;
    }
    
    text1.setString(n);
    text1.setCharacterSize(40);

    

    sf::Text text2;
    text2.setFont(font);
    FighterName name2 = state.getPlayerList()[1]->getFighter()->getName();
    string n1;
    switch(name2)
    {
        case 0:
            n1 = "Kuro";
            break;
        case 1:
            n1 = "Flint";
            break;
        case 2:
            n1 = "Thork";
            break;
        case 3:
            n1 = "Seku";
            break;
    }

    text2.setString(n1);
    text2.setCharacterSize(40);
    text2.setPosition(530.f,0.f);
   
    window.draw(text1);
    window.draw(text2);
   
    window.display();
}


void StateLayer::stateChanged(const state::StateEvent& stateEvent, const state::State &new_state)
{
    this->state = new_state;
    this->draw(); 
}
