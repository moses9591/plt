#include "EnergyBar.h"
#include "TextureManager.h"

using namespace std;
using namespace render;
using namespace state;



void EnergyBar::draw (sf::RenderWindow& window, std::shared_ptr<state::Player> player,float x, float y)
{
    TextureManager *instance = TextureManager::getInstance();

    if(player->getFighter()->getMana()<0)
    {
        player->getFighter()->setMana(0);
    }

    TileSet *tileEnergyBar1 = instance->getEnergyBar(player->getFighter()->getMana());
   
   
    sf::Sprite energySprite;
    energySprite.setTexture(tileEnergyBar1->getTexture());
    energySprite.setPosition(x,y); //0 40 // 0 60
        
    window.draw(energySprite);  
}

